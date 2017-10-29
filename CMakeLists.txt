cmake_minimum_required(VERSION 3.8)
project(sem1_c_mini_project)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c login.c login.h global.c global.h add_train.c add_train.h reservation_menu.c reservation_menu.h book_train.c book_train.h train_function_common.h)
add_executable(sem1_c_mini_project ${SOURCE_FILES})