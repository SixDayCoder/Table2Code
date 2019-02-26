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
manager_impl_template_path = r"./TableGenerateTemplate_ManagerImpl.xml"

impl_output_file_name = "table_impl.cpp"
impl_line_template = r"tableFile.Read({0}, nLineIndex, (int32_t){1});"

manager_impl_output_file_name = "table_manager.cpp"
manager_impl_map_template = r"std::map<std::string, TableInstancePtr> TableManager::gTableMap;"
manager_impl_inlcude_template = r'#include "table/table_{0}.h"' + "\n\t\t"

# constant for xml replace

comment_tag = "comment"
include_tag = "include"
class_head_tag = "classhead"
class_end_tag = "classend"
property_tag = "property"
body_impl_tag = "bodyimpl"
map_impl_tag = "mapimpl"
load_line_tag = "loadline"
load_body_tag = "loadbody"

newline_str = "${NewLine}"
filename_str = "${FileName}"
classname_str = "${ClassName}"
idbody_str = "${IdBody}"
reference_str = "${Reference}"
type_str = "${Type}"
valname_str = "${VariableName}"
bodyimpl_str = "${BodyImpl}"
abs_file_path_str = "${AbsFilePath}"
include_name_str = "${IncludeName}"
include_body_str = "${IncludeBody}"
map_impl_body_str = "${MapImplBody}"
load_body_str = "${LoadBody}"


# global variable in this script

input_dir = ""
input_file_path_lists = []

output_dir = ""
impl_output_file_path = ""
impl_output_file = None

manager_impl_output_file_path = ""
manager_impl_output_file = None
manager_impl_include_list = []


def init_file():
    # input_file_paths
    global input_file_path_lists
    lists = os.listdir(input_dir)
    for idx in range(0, len(lists)):
        path = os.path.join(input_dir, lists[idx])
        if os.path.isfile(path):
            input_file_path_lists.append(path)

    # output_file_path
    if not os.path.isdir(output_dir):
        print ("output_dir" + output_dir + "is not a directory")
        sys.exit(2)
    global impl_output_file_path
    impl_output_file_path = os.path.join(output_dir, impl_output_file_name)

    # manager_impl_output_file_path
    global manager_impl_output_file_path
    manager_impl_output_file_path = os.path.join(output_dir, manager_impl_output_file_name)

    # impl_output_file
    global impl_output_file
    impl_output_file = open(impl_output_file_path, "wb+")

    # manager_impl_output_file
    global  manager_impl_output_file
    manager_impl_output_file = open(manager_impl_output_file_path, "wb+")


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
    comment = node.text

    node = root.find(include_tag)
    include = node.text

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


def generate_class_end(root, file_name):
    node = root.find(class_end_tag)
    return node.text.replace(filename_str, file_name)


def generate_parse_header(path, name_list, type_list):
    file_name = real_file_name(path)
    class_name = "table_" + file_name.lower()

    tree = ET.parse(header_template_path)
    root = tree.getroot()
    output = ""
    output = output + generate_class_header(root, file_name, name_list)
    output = output + generate_class_body(root, name_list, type_list)
    output = output + generate_class_end(root, file_name)
    global manager_impl_include_list
    include = manager_impl_inlcude_template.format(file_name).lower()
    manager_impl_include_list.append(include)
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
        line = impl_line_template.format(name, idenum) + "\n\t\t\t"
        content = content + line

    file_name = real_file_name(path)
    include_name = file_name.lower()
    abs_file_path = os.path.abspath(path)
    abs_file_path = abs_file_path.replace("\\", "/")

    node = root.find(body_impl_tag)
    text = node.text.replace(bodyimpl_str, content)
    text = text.replace(filename_str, file_name)
    text = text.replace(reference_str, "&")
    text = text.replace(include_name_str, include_name)
    text = text.replace(abs_file_path_str, abs_file_path)
    impl_output_file.writelines(text)


def generate_parse_manager_impl_header():
    tree = ET.parse(manager_impl_template_path)
    root = tree.getroot()

    node = root.find(comment_tag)
    manager_impl_output_file.writelines(node.text)

    node = root.find(map_impl_tag)
    text = node.text.replace(map_impl_body_str, manager_impl_map_template)
    manager_impl_output_file.writelines(text)


def generate_parse_manager_impl_body(path):
    tree = ET.parse(manager_impl_template_path)
    root = tree.getroot()
    file_name = real_file_name(path)
    class_name = "Table_" + file_name

    node = root.find(load_line_tag)
    text = node.text.replace(classname_str, class_name)
    text = text.replace(reference_str, "&")
    return text


def generate_parse_manager_impl_write(content):

    tree = ET.parse(manager_impl_template_path)
    root = tree.getroot()

    node = root.find(comment_tag)
    manager_impl_output_file.writelines(node.text)

    include = ""
    for i in range(0, len(manager_impl_include_list)):
        include = include + manager_impl_include_list[i]
    node = root.find(include_tag)
    text = node.text.replace(include_body_str, include)
    manager_impl_output_file.writelines(text)

    node = root.find(map_impl_tag)
    text = node.text.replace(map_impl_body_str, manager_impl_map_template)
    manager_impl_output_file.writelines(text)

    node = root.find(load_body_tag)
    text = node.text.replace(load_body_str, content)
    manager_impl_output_file.writelines(text)
    # close file
    manager_impl_output_file.close()


def generate(arg_input_dir, arg_output_dir):
    # init files
    global input_dir
    global output_dir
    input_dir = arg_input_dir
    output_dir = arg_output_dir
    init_file()

    # parse
    manager_impl_content = ""
    for i in range(0, len(input_file_path_lists)):
        path = input_file_path_lists[i]
        input_f = open(path, "rb")
        name_list, type_list = parse_name_and_type(input_f)
        generate_parse_header(path, name_list, type_list)
        generate_parse_impl(path, name_list, type_list)
        manager_impl_content = manager_impl_content + generate_parse_manager_impl_body(path)
        input_f.close()
    generate_parse_manager_impl_write(manager_impl_content)