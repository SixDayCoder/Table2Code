CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
PROJECT(Table2Code)
ADD_DEFINITIONS(-std=c++11)
SET(CMAKE_C_STANDARD 99)
INCLUDE_DIRECTORIES(
        src
        src/table
        src/utils
)

SET(SRC_FILES
        src/main.cpp
        src/table/table_file.cpp
        src/table/table_impl.cpp
        src/utils/utils.cpp
        )

ADD_EXECUTABLE(Table2Code ${SRC_FILES})