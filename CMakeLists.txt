cmake_minimum_required(VERSION 3.16)
project(FiguresProject VERSION 1.0 LANGUAGES CXX)

# Установка стандарта C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Включение каталога с заголовочными файлами
include_directories(include)

# Основная программа
add_executable(FiguresProject main.cpp)

# Установка свойств компиляции
target_compile_features(FiguresProject PRIVATE cxx_std_20)

# Для отладки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(FiguresProject PRIVATE -g -O0)
else()
    target_compile_options(FiguresProject PRIVATE -O2)
endif()

# Простая проверка на существование тестов
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_figures.cpp)
    # Создаем тестовый исполняемый файл
    add_executable(FiguresTests tests/test_figures.cpp)
    target_include_directories(FiguresTests PRIVATE ${CMAKE_SOURCE_DIR}/include)
    
    # Пытаемся найти и линковать GTest
    find_package(GTest QUIET)
    if(GTest_FOUND)
        target_link_libraries(FiguresTests GTest::gtest GTest::gtest_main)
        message(STATUS "GoogleTest found - tests will be built")
        
        include(GoogleTest)
        gtest_discover_tests(FiguresTests)
    else()
        # Если GTest не найден, просто компилируем тесты как обычную программу
        message(STATUS "GoogleTest not found - compiling tests without GoogleTest")
    endif()
endif()

# Установка выходной директории
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)