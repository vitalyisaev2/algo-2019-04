cmake_minimum_required(VERSION 3.0)
project(algo-2019-04)
enable_testing()

# составляет список подпапок с исходниками в проекте
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      IF(${child} MATCHES "[0-9]+.*")
        LIST(APPEND dirlist ${curdir}/${child})
      ENDIF()
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

# глобальные настройки компилятора 
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wswitch-default -Wundef -Werror -Wno-unused") 

# зависимости
find_package(Catch2 2.7 REQUIRED)
find_package(benchmark REQUIRED)

# сборка бинарника с тестами
file(GLOB tests_main_src "*.cpp")
file(GLOB_RECURSE tests_full_src 
  ${PROJECT_SOURCE_DIR}/02_data_structures/*.cpp
  ${PROJECT_SOURCE_DIR}/03_chess/*.cpp
)
list(APPEND tests_full_src ${tests_main_src})
list(FILTER tests_full_src EXCLUDE REGEX ".*bench.cpp$")
SUBDIRLIST(tests_include "${PROJECT_SOURCE_DIR}")
add_executable(tests "${tests_full_src}")
target_include_directories(tests PRIVATE "${tests_include}")
target_link_libraries(tests Catch2::Catch2)

# сборка бинарника с бенчмарками
file(GLOB_RECURSE benchmarks_src "*bench.cpp")
SUBDIRLIST(benchmarks_include "${PROJECT_SOURCE_DIR}")
add_executable(benchmarks "${benchmarks_src}")
target_include_directories(benchmarks PRIVATE "${benchmarks_include}")
target_link_libraries(benchmarks benchmark::benchmark)

# запуск тестов
include(CTest)
include(Catch)
catch_discover_tests(tests)

# запуск тестов с проверкой памяти
find_program(VALGRIND "valgrind")
add_test(
    tests_valgrind
    "${VALGRIND}" --error-exitcode=1 --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --run-libc-freeres=no "${CMAKE_CURRENT_BINARY_DIR}/tests")