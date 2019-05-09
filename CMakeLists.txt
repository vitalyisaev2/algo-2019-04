cmake_minimum_required(VERSION 3.0)
project(algo-2019-04)
enable_testing()

# составляет список подпапок 
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${curdir}/${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

# глобальные настройки компилятора 
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused") 

# зависимости
find_package(Catch2 REQUIRED)

# сборка бинарника с тестами
file(GLOB_RECURSE tests_src "*test.cpp")
SUBDIRLIST(tests_include "${PROJECT_SOURCE_DIR}")
add_executable(tests "${tests_src}")
target_include_directories(tests PRIVATE "${tests_include}")
target_link_libraries(tests Catch2::Catch2)
#target_compile_options(tests PRIVATE -fsanitize=address)

# запуск тестов
include(CTest)
include(Catch)
catch_discover_tests(tests)

# запуск тестов с проверкой памяти
find_program(VALGRIND "valgrind")
add_test(
    tests_valgrind
    "${VALGRIND}" --error-exitcode=1 --tool=memcheck --leak-check=yes --run-libc-freeres=no "${CMAKE_CURRENT_BINARY_DIR}/tests")