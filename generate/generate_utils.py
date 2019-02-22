#!/usr/bin/python
# -*- coding: UTF-8 -*-

import sys
import os
import xml.etree.ElementTree as ET

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

header_template_path = r"./TableGenerateTemplate_Header.xml"

comment_tag = "comment"
include_tag = "include"
class_head_tag = "classhead"
class_end_tag = "classend"
property_tag = "property"

newline_str = "${NewLine}"
filename_str = "${FileName}"
idbody_str = "${IdBody}"
reference_str = "${Reference}"
type_str = "${Type}"
valname_str = "${VariableName}"


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
    class_head = class_head.replace(newline_str, "\n")

    return comment + include + class_head


def generate_class_body(root, name_list, type_list):
    ret = ""
    for i in range(0, len(type_list)):
        typestr = type_list[i]
        node = root.find(property_tag)
        property_str = node.text
        type_content = ""
        variable_name = name_list[i]
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


def generate_parse_file(f):
    line_index = 0
    file_name = real_file_name(f.name)
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
    tree = ET.parse(header_template_path)
    root = tree.getroot()

    output = ""
    output = output + generate_class_header(root, file_name, name_list)
    output = output + generate_class_body(root, name_list, type_list)
    output = output + generate_class_end(root)

    print (output)


def generate_header(input_files):
    for i in range(0, len(input_files)):
        path = input_files[i]
        try:
            f = open(path, "rb")
            generate_parse_file(f)
        except Exception as e:
            print (e)
            sys.exit(2)
