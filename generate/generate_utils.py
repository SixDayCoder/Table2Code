#!/usr/bin/python
# -*- coding: UTF-8 -*-

import sys
import os
import xml.etree.ElementTree as ET

# constant for name and type parse

int32_t = "int32_t"
int64_t = "int64_t"
string_t = "std::string"
float_t = "float"


int32_type = "INT32"
int64_type = "INT64"
string_type = "STRING"
float_type = "FLOAT"


LINE_INDEX_NAME = 0
LINE_INDEX_TYPE = 1

desc_str = "Desc"

# constant for generate template

header_template_path = r"./TableGenerateTemplate_Header.xml"
impl_template_path = r"./TableGenerateTemplate_Impl.xml"

impl_output_file_name = "Table_Impl.cpp"
impl_line_template = r"tableFile.Read({0}, nLineIndex, (int32_t){1});"

# constant for xml replace

comment_tag = "comment"
include_tag = "include"
class_head_tag = "classhead"
class_end_tag = "classend"
property_tag = "property"
body_impl_tag = "bodyimpl"

newline_str = "${NewLine}"
filename_str = "${FileName}"
idbody_str = "${IdBody}"
reference_str = "${Reference}"
type_str = "${Type}"
valname_str = "${VariableName}"
bodyimpl_str = "${BodyImpl}"


# global variable in this script

input_dir = ""
input_file_path_lists = []

output_dir = ""
impl_output_file_path = ""
impl_output_file = None


def init_file():
    # input_file_paths
    global input_file_path_lists
    lists = os.listdir(input_dir)
    for idx in range(0, len(lists)):
        path = os.path.join(input_dir, lists[idx])
        if os.path.isfile(path):
            input_file_path_lists.append(path)

    # output_file_path
    global impl_output_file_path
    if not os.path.isdir(output_dir):
        print ("output_dir" + output_dir + "is not a directory")
        sys.exit(2)
    impl_output_file_path = os.path.join(output_dir, impl_output_file_name)

    # impl_output_file
    global impl_output_file
    impl_output_file = open(impl_output_file_path, "wb+")


def parse_name_and_type(f):
    line_index = 0
    name_list = []
    type_list = []
    for line in f:
        if line_index == LINE_INDEX_NAME:
            record = line.strip()
            name_list = record.split('\t')
            line_index = line_index + 1
            continue
        if line_index == LINE_INDEX_TYPE:
            record = line.strip()
            type_list = record.split('\t')
            break
    assert (len(name_list) == len(type_list))
    return name_list, type_list


def real_file_name(filepath):
    try:
        filepath, tmp_file_name = os.path.split(filepath)
        filename, extension = os.path.splitext(tmp_file_name)
        return filename
    except Exception as e:
        print (e)
        sys.exit(2)


def header_idbody(name_list):
    ret = ""
    index = 0
    for i in range(0, len(name_list)):
        ret = ret + "ID_" + name_list[i].upper() + " = " + str(index) + "," + "\n\t\t\t\t\t"
        index = index + 1
    return ret


def add_new_file_to(newfile_name, newfile_content):
    if not os.path.isdir(output_dir):
        print ("output_dir" + output_dir + "is not a directory")
        sys.exit(2)
    abs_new_file_path = os.path.join(output_dir, newfile_name)
    try:
        f = open(abs_new_file_path, "wb+")
        f.write(newfile_content)
        f.close()
    except Exception as e:
        print (e)
        sys.exit(2)


def generate_class_header(root, file_name, name_list):
    node = root.find(comment_tag)
    comment = node.text.replace(newline_str, "\n")

    node = root.find(include_tag)
    include = node.text.replace(newline_str, "\n")

    node = root.find(class_head_tag)
    idbody_content = header_idbody(name_list)
    class_head = node.text.replace(filename_str, file_name)
    class_head = class_head.replace(idbody_str, idbody_content)
    class_head = class_head.replace(reference_str, "&")
    return comment + include + class_head


def generate_class_body(root, name_list, type_list):
    ret = ""
    for i in range(0, len(type_list)):
        typestr = type_list[i]
        node = root.find(property_tag)
        property_str = node.text
        type_content = ""
        variable_name = name_list[i]
        if variable_name == desc_str:
            continue
        if typestr == int32_type:
            type_content = int32_t
        elif typestr == int64_type:
            type_content = int64_t
        elif typestr == float_type:
            type_content = float_t
        elif typestr == string_type:
            type_content = string_t
        property_str = property_str.replace(type_str, type_content)
        property_str = property_str.replace(valname_str, variable_name)
        ret = ret + property_str
    return ret


def generate_class_end(root):
    node = root.find(class_end_tag)
    return node.text.replace(newline_str, "\n")


def generate_parse_header(path, name_list, type_list):
    file_name = real_file_name(path)
    class_name = "Table_" + file_name

    tree = ET.parse(header_template_path)
    root = tree.getroot()
    output = ""
    output = output + generate_class_header(root, file_name, name_list)
    output = output + generate_class_body(root, name_list, type_list)
    output = output + generate_class_end(root)
    add_new_file_to(class_name + ".h", output)


def generate_parse_impl(path, name_list, type_list):
    tree = ET.parse(impl_template_path)
    root = tree.getroot()
    content = ""
    for i in range(0, len(name_list)):
        if name_list[i] == desc_str:
            continue
        name = "m_" + name_list[i]
        idenum = "ID_" + name_list[i].upper()
        line = impl_line_template.format(name, idenum) + "\n\t\t"
        content = content + line

    file_name = real_file_name(path)
    node = root.find(body_impl_tag)
    text = node.text.replace(bodyimpl_str, content)
    text = text.replace(filename_str, file_name)
    text = text.replace(reference_str, "&")
    impl_output_file.writelines(text)


def generate(arg_input_dir, arg_output_dir):
    # init files
    global input_dir
    global output_dir
    input_dir = arg_input_dir
    output_dir = arg_output_dir
    init_file()

    # parse
    impl_output_f = open(impl_output_file_path, "wb")
    for i in range(0, len(input_file_path_lists)):
        path = input_file_path_lists[i]
        input_f = open(path, "rb")
        name_list, type_list = parse_name_and_type(input_f)
        generate_parse_header(path, name_list, type_list)
        generate_parse_impl(path, name_list, type_list)
        input_f.close()
    impl_output_f.close()