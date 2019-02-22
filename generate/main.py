#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
import sys
import getopt
import generate_utils

# input and output define

input_dir = ""
input_files = []

output_dir = ""
output_files = []



def init_file_lists(file_dir, file_list):
    try:
        lists = os.listdir(file_dir)
    except Exception as e:
        print(e)
        sys.exit(2) 

    for idx in range(0, len(lists)):
        path = os.path.join(file_dir, lists[idx])
        if os.path.isfile(path):
            file_list.append(path)             


def main(argv):

    # try:
    #    opts, args = getopt.getopt(argv,"hi:o:",["ifile=","ofile="])
    # except getopt.GetoptError:
    #    print ("test.py -i <inputfile> -o <outputfile>")
    #    sys.exit(2)

    input_dir = r"D:\Table2Code\tables"
    output_dir = r"C:\Users\Administrator\Desktop"

    # for opt, arg in opts:
    #    if opt in ("-i"):
    #       input_dir = arg
    #       init_file_lists(input_dir, input_files)
    #    elif opt in ("-o"):
    #       output_dir = arg
    #

    init_file_lists(input_dir, input_files)
    generate_utils.generate_header(input_files)


if __name__ == "__main__":
    main(sys.argv[1:])

# main.py -i D:\Table2Code\tables -o C:\Users\Administrator\Desktop   