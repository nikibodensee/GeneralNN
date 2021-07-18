cmake_minimum_required(VERSION 3.19)
project(GeneralNN_v1_0 C)

include_directories(.)

add_executable(GeneralNN_GUI_1_0
        "0.0. main.c"
        "1.0. weightinit.c"
        "1.1. readweights.c"
        "1.2. saveweights.c"
        "2.0. readinp.c"
        "3.0. query_inputlayer.c"
        "3.1. query_layerX.c"
        "3.2. query_outputlayer.c"
        "4.0. teach.c"
        "4.1. pattern_missmatch.c"
        main.h)