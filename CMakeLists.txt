cmake_minimum_required(VERSION 3.7)
project(Shell)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES
        command_parser.c
        command_parser.h
        commands.c
        commands.h
        environment.c
        environment.h
        file_processing.c
        file_processing.h
        main.c
        variables.c
        variables.h custom_types.h utils.c utils.h map.c map.h)

add_executable(Shell ${SOURCE_FILES})