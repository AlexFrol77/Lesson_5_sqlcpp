cmake_minimum_required(VERSION 3.20)

project(Lesson_5_Task_1)

set(PostgreSQL_ADDITIONAL_VERSIONS "14")

add_subdirectory("C:/PQXX_project/libpqxx-7.7.5" libpqxx-build)

add_executable(Lesson_5_Task_1 main.cpp, 
C:\Users\drbo1\OneDrive\Рабочий стол\HomeWork\HomeWork_sqlcpp\Lessson_4_sqlcpp\Task_1\build\ClientBase.h,
C:\Users\drbo1\OneDrive\Рабочий стол\HomeWork\HomeWork_sqlcpp\Lessson_4_sqlcpp\Task_1\build\ClientBase.cpp)

target_compile_features(Lesson_5_Task_1 PRIVATE cxx_std_17)
target_link_libraries(Lesson_5_Task_1 pqxx)