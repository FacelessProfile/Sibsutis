cmake_minimum_required(VERSION 3.10)
include_directories("../pipes/")
set(LIB back.c)
add_library(LIBR STATIC ${LIB})
