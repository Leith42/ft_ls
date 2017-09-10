cmake_minimum_required(VERSION 3.7)
set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        src/args_parsing.c
        src/comparison.c
        src/directories.c
        src/error.c
        src/files.c
        src/freedom.c
        src/list_sort.c
        src/main.c
        src/print_attribs.c
        src/printer.c
        src/printer2.c
        src/recursive.c
        src/size.c
        src/sorting.c
        src/struct_manager.c
        )

add_executable(ft_ls ${SOURCE_FILES})

include_directories(ft_ls
        ${CMAKE_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/libft/include/)

target_link_libraries(ft_ls
        ${CMAKE_SOURCE_DIR}/libft/libft.a)