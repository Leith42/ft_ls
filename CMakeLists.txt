cmake_minimum_required(VERSION 3.7)
set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        main.c
        args_parsing.c
        freedom.c
        error.c
        file_sort.c
        struct_manager.c
        printer.c
        size.c
        directories.c
        files.c
        printer2.c
        recursive.c
        list_sort.c
        print_attribs.c
        )

add_executable(ft_ls ${SOURCE_FILES})

include_directories(ft_ls
        ${CMAKE_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/libft/include/)

target_link_libraries(ft_ls
        ${CMAKE_SOURCE_DIR}/libft/libft.a)