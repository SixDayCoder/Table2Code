#!/usr/bin/python
# -*- coding: UTF-8 -*-

import sys
import os
import xml.etree.ElementTree as ET

# constant for name and type parse
type_map = {"INT32": "int32_t", "INT64": "int64_t", "STRING": "std::string", "FLOAT": "float"}
default_val_map = {"INT32": "-1", "INT64": "-1", "STRING": "", "FLOAT": "0.0"}
LINE_INDEX_NAME = 0
LINE_INDEX_TYPE = 1


# constant for generate template

header_template_path = r"./TableGenerateTemplate_Header.xml"
impl_template_path = r"./TableGenerateTemplate_Impl.xml"
manager_impl_template_path = r"./TableGenerateTemplate_ManagerImpl.xml"

impl_output_file_name = "table_impl.cpp"
impl_line_single_template = r"tableFile.Read(m_{0}, nLineIndex, (int32_t){1});"
impl_line_array_template = r"tableFile.Read(m_{0}[{1}], nLineIndex, (int32_t){2});"

manager_impl_output_file_name = "table_manager.cpp"
manager_impl_map_template = r"std::map<std::string, TableInstancePtr> TableManager::gTableMap;"
manager_impl_inlcude_template = r'#include "table/table_{0}.h"' + "\n\t\t"


# xml tag
comment_tag = "comment"
include_tag = "include"
class_head_tag = "classhead"
class_end_tag = "classend"
property_tag = "property"
body_impl_tag = "bodyimpl"
map_impl_tag = "mapimpl"
load_line_tag = "loadline"
load_body_tag = "loadbody"
array_tag = "array"

# xml replace string
newline_str = "${NewLine}"
left_brackets_str = "${LeftBrackets}"
right_brackets_str = "${RightBrackets}"

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
count_str = "${Count}"
default_val_str = "${DefaultVal}"


# global variable in this script

input_dir = ""
input_file_path_lists = []

output_dir = ""
impl_output_file_path = ""
impl_output_file = None

manager_impl_output_file_path = ""
manager_impl_output_file = None
manager_impl_include_list = []


# special for generate array
class ArrayNameObj:

    def __init__(self, array_name_dic):
        self.array_variable_name = ""
        self.array_variable_type = ""
        self.array_variable_enum_list = []
        for k in array_name_dic:
            self.array_variable_name = k[:-1]
            self.array_variable_type = array_name_dic[k]
            self.array_variable_enum_list.append("ID_" + k.upper())
        self.array_variable_enum_list.sort()


# utils
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


def array_name(name_list, type_list):
    array_name_set = set()
    array_name_obj_list = []
    for i in range(0, len(name_list) - 1):
        array_name_dic = {}
        for j in range(i + 1, len(name_list)):
            if name_list[j][:-1] == name_list[i][:-1] and name_list[i][:-1] not in array_name_set:
                array_name_dic[name_list[i]] = type_list[i]
                array_name_dic[name_list[j]] = type_list[j]
        if len(array_name_dic) > 0:
            array_name_object = ArrayNameObj(array_name_dic)
            array_name_set.add(name_list[i][:-1])
            array_name_obj_list.append(array_name_object)
    return array_name_obj_list, array_name_set


# parse header funtion
def generate_parse_header_body_single(root, name, type):
    node = root.find(property_tag)
    val = type_map.get(type, None)
    if val is None:
        print ("get type according to type error : " + "type is : " + type)
        sys.exit(2)
    text = node.text.replace(type_str, val)
    text = text.replace(valname_str, name)
    return text


def generate_parse_header_body_array(root, array_name_obj, array_name_set):
    valname = array_name_obj.array_variable_name
    valtype = array_name_obj.array_variable_type
    count = str(len(array_name_obj.array_variable_enum_list))

    node = root.find(array_tag)
    text = node.text.replace(type_str, type_map[valtype])
    text = text.replace(valname_str, valname)
    text = text.replace(count_str, count)
    text = text.replace(left_brackets_str, "<")
    text = text.replace(right_brackets_str, ">")
    text = text.replace(default_val_str, default_val_map[valtype])
    return text


def generate_parse_header_begin(root, file_name, name_list):
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


def generate_parse_header_body(root, name_list, type_list):
    # check array name
    array_name_obj_list, array_name_set = array_name(name_list, type_list)
    # generate
    ret = ""
    curr_idx = 0
    for i in range(0, len(type_list)):
        if name_list[i] == "Desc":
            continue
        typestr = type_list[i]
        namestr = name_list[i]
        # generate array
        if namestr[:-1] in array_name_set:
            if curr_idx >= 0 and curr_idx < len(array_name_obj_list):
                ret = ret + generate_parse_header_body_array(root, array_name_obj_list[curr_idx], array_name_set)
                curr_idx = curr_idx + 1
        # generate single
        else:
            ret = ret + generate_parse_header_body_single(root, namestr, typestr)
    return ret


def generate_parse_header_end(root, file_name):
    node = root.find(class_end_tag)
    return node.text.replace(filename_str, file_name)


def generate_header(path, name_list, type_list):
    file_name = real_file_name(path)
    class_name = "table_" + file_name.lower()
    # parse xml
    tree = ET.parse(header_template_path)
    root = tree.getroot()
    output = ""
    output = output + generate_parse_header_begin(root, file_name, name_list)
    output = output + generate_parse_header_body(root, name_list, type_list)
    output = output + generate_parse_header_end(root, file_name)
    # ready data for adding new file
    global manager_impl_include_list
    include = manager_impl_inlcude_template.format(file_name).lower()
    manager_impl_include_list.append(include)
    add_new_file_to(class_name + ".h", output)


# generate impl

def generate_impl(path, name_list, type_list):
    # check array name
    array_name_obj_list, array_name_set = array_name(name_list, type_list)
    content = ""
    cur_idx = 0
    for i in range(0, len(name_list)):
        if name_list[i] == "Desc":
            continue
        # impl line array
        if name_list[i][:-1] in array_name_set:
            if cur_idx >= 0 and cur_idx < len(array_name_obj_list):
                array_name_obj = array_name_obj_list[cur_idx]
                if array_name_obj is not None:
                    name = array_name_obj.array_variable_name
                    for j in range(0, len(array_name_obj.array_variable_enum_list)):
                        line = impl_line_array_template.format(name, j, array_name_obj.array_variable_enum_list[j]) + "\n\t\t\t"
                        content = content + line
                cur_idx = cur_idx + 1
        # impl line single
        else:
            name = name_list[i]
            idenum = "ID_" + name_list[i].upper()
            line = impl_line_single_template.format(name, idenum) + "\n\t\t\t"
            content = content + line

    # replace content
    file_name = real_file_name(path)
    include_name = file_name.lower()
    abs_file_path = os.path.abspath(path).replace("\\", "/")

    tree = ET.parse(impl_template_path)
    root = tree.getroot()
    node = root.find(body_impl_tag)
    text = node.text.replace(bodyimpl_str, content)
    text = text.replace(filename_str, file_name)
    text = text.replace(reference_str, "&")
    text = text.replace(include_name_str, include_name)
    text = text.replace(abs_file_path_str, abs_file_path)
    impl_output_file.writelines(text)


# generate manager impl

def generate_manager_impl(path):
    tree = ET.parse(manager_impl_template_path)
    root = tree.getroot()
    file_name = real_file_name(path)
    class_name = "Table_" + file_name

    node = root.find(load_line_tag)
    text = node.text.replace(classname_str, class_name)
    text = text.replace(reference_str, "&")
    return text


def generate_manager_impl_write(content):
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
        generate_header(path, name_list, type_list)
        generate_impl(path, name_list, type_list)
        manager_impl_content = manager_impl_content + generate_manager_impl(path)
        input_f.close()
    generate_manager_impl_write(manager_impl_content)