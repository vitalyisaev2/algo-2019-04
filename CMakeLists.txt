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
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wswitch-default -Wundef -Werror -Wno-unused") 

# зависимости
find_package(Catch2 2.7 REQUIRED)
find_package(benchmark REQUIRED)

# сборка бинарника с тестами
file(GLOB_RECURSE test_full_src 
  ${PROJECT_SOURCE_DIR}/test/*.cpp
  ${PROJECT_SOURCE_DIR}/02_data_structures/*.cpp
  ${PROJECT_SOURCE_DIR}/04_algebraic/*.cpp
  ${PROJECT_SOURCE_DIR}/05_sort/*.cpp
  ${PROJECT_SOURCE_DIR}/06_sort/*.cpp
)
SUBDIRLIST(test_include "${PROJECT_SOURCE_DIR}" )
list(APPEND test_include "${PROJECT_SOURCE_DIR}/utils")
add_executable(tests "${test_full_src}")
target_include_directories(tests PRIVATE "${test_include}")
target_link_libraries(tests Catch2::Catch2)

# сборка бинарника с бенчмарками
file(GLOB_RECURSE bench_full_src 
  ${PROJECT_SOURCE_DIR}/bench/*.cpp
  ${PROJECT_SOURCE_DIR}/02_data_structures/*.cpp
  ${PROJECT_SOURCE_DIR}/04_algebraic/*.cpp
  ${PROJECT_SOURCE_DIR}/05_sort/*.cpp
  ${PROJECT_SOURCE_DIR}/06_sort/*.cpp
)
SUBDIRLIST(bench_include "${PROJECT_SOURCE_DIR}")
list(APPEND bench_include "${PROJECT_SOURCE_DIR}/utils")
add_executable(bench "${bench_full_src}")
target_include_directories(bench PRIVATE "${bench_include}")
target_link_libraries(bench benchmark::benchmark)

# запуск тестов
include(CTest)
include(Catch)
catch_discover_tests(tests)

# запуск тестов с проверкой памяти
find_program(VALGRIND "valgrind")
add_test(
    test_valgrind
    "${VALGRIND}" --error-exitcode=1 --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --run-libc-freeres=no "${CMAKE_CURRENT_BINARY_DIR}/tests")
