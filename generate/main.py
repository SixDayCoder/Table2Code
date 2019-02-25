#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
import sys
import getopt
import generate_utils

def main(argv):

    # try:
    #    opts, args = getopt.getopt(argv,"hi:o:",["ifile=","ofile="])
    # except getopt.GetoptError:
    #    print ("test.py -i <inputfile> -o <outputfile>")
    #    sys.exit(2)

    input_dir = r"..\tables"
    output_dir = r"..\tables\generate"

    # for opt, arg in opts:
    #    if opt in ("-i"):
    #       input_dir = arg
    #       init_file_lists(input_dir, input_files)
    #    elif opt in ("-o"):
    #       output_dir = arg
    #

    generate_utils.generate(input_dir, output_dir)


if __name__ == "__main__":
    main(sys.argv[1:])