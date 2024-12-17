cmake_minimum_required(VERSION 3.10)
set (LIB read_pipe.c write_pipe.c)
add_library(LIBRARY STATIC ${LIB})
