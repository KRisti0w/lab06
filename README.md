[![CI](https://github.com/KRisti0w/lab06/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/KRisti0w/lab06/actions/workflows/ci.yml)
## Отчёт к lab06
В рамках выполнения данной лабораторной работы мною были выполнены команды из tutorial с некоторыми изменениями:
1) Скопирован репозиторий из lab04:
```bash
$ git clone https://github.com/${GITHUB_USERNAME}/lab04 projects/lab06
Клонирование в «projects/lab06»...
remote: Enumerating objects: 46, done.
remote: Counting objects: 100% (46/46), done.
remote: Compressing objects: 100% (31/31), done.
remote: Total 46 (delta 12), reused 38 (delta 8), pack-reused 0 (from 0)
Получение объектов: 100% (46/46), 12.03 КиБ | 684.00 КиБ/с, готово.
Определение изменений: 100% (12/12), готово.
$ cd projects/lab06
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab06
```
2) Установлен и закоммичен gtest более актуальной версии, чем предложено в tutorial:
```bash
$ git submodule add https://github.com/google/googletest third-party/gtest
Клонирование в «/home/kristina/KRisti0w/workspace/projects/lab06/third-party/gtest»...
remote: Enumerating objects: 28627, done.
remote: Counting objects: 100% (64/64), done.
remote: Compressing objects: 100% (48/48), done.
remote: Total 28627 (delta 32), reused 16 (delta 16), pack-reused 28563 (from 2)
Получение объектов: 100% (28627/28627), 13.78 МиБ | 8.76 МиБ/с, готово.
Определение изменений: 100% (21268/21268), готово.

$ cd third-party/gtest && git checkout release-1.15.2 && cd ../..
$ git add third-party/gtest
$ git commit -m"added gtest framework v1.15.2"
[main a01e205] added gtest framework v1.15.2
 2 files changed, 4 insertions(+)
 create mode 100644 .gitmodules
 create mode 160000 third-party/gtest
```

3) К Cmake.txt добавлен фрагмент кода:
```cmake
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB \${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(check \${\${PROJECT_NAME}_TEST_SOURCES})
  target_link_libraries(check \${PROJECT_NAME} gtest_main)
  add_test(NAME check COMMAND check)
endif()
```
4) Написан тест:
```cpp
#include <print.hpp>

#include <gtest/gtest.h>

TEST(Print, InFileStream)
{
  std::string filepath = "file.txt";
  std::string text = "hello";
  std::ofstream out{filepath};

  print(text, out);
  out.close();

  std::string result;
  std::ifstream in{filepath};
  in >> result;

  EXPECT_EQ(result, text);
}
```
5) Произведена сборка и запущены тесты (с менее и более подробным выводом):
```bash
$ cmake -H. -B_build -DBUILD_TESTS=ON
CMake Deprecation Warning at CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- The C compiler identification is GNU 14.2.0
-- The CXX compiler identification is GNU 14.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Configuring done (2.6s)
-- Generating done (0.0s)
-- Build files have been written to: /home/danila/Wartheree/workspace/projects/lab06/_build
```
```bash
$ cmake --build _build
[  8%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 16%] Linking CXX static library libprint.a
[ 16%] Built target print
[ 25%] Building CXX object third-party/gtest/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
[ 33%] Linking CXX static library ../../../lib/libgtest.a
[ 33%] Built target gtest
[ 41%] Building CXX object third-party/gtest/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
[ 50%] Linking CXX static library ../../../lib/libgtest_main.a
[ 50%] Built target gtest_main
[ 58%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[ 66%] Linking CXX executable check
[ 66%] Built target check
[ 75%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
[ 83%] Linking CXX static library ../../../lib/libgmock.a
[ 83%] Built target gmock
[ 91%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
[100%] Linking CXX static library ../../../lib/libgmock_main.a
[100%] Built target gmock_main
```
```bash
$ cmake --build _build --target test
Running tests...
Test project /home/danila/Wartheree/workspace/projects/lab06/_build
    Start 1: check
1/1 Test #1: check ............................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.03 sec
```
```bash
$ _build/check
Running main() from /home/danila/Wartheree/workspace/projects/lab06/third-party/gtest/googletest/src/gtest_main.cc
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from Print
[ RUN      ] Print.InFileStream
[       OK ] Print.InFileStream (0 ms)
[----------] 1 test from Print (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
```
```bash
$ cmake --build _build --target test -- ARGS=--verbose
Running tests...
UpdateCTestConfiguration  from :/home/danila/Wartheree/workspace/projects/lab06/_build/DartConfiguration.tcl
UpdateCTestConfiguration  from :/home/danila/Wartheree/workspace/projects/lab06/_build/DartConfiguration.tcl
Test project /home/danila/Wartheree/workspace/projects/lab06/_build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: check

1: Test command: /home/danila/Wartheree/workspace/projects/lab06/_build/check
1: Working Directory: /home/danila/Wartheree/workspace/projects/lab06/_build
1: Test timeout computed to be: 10000000
1: Running main() from /home/danila/Wartheree/workspace/projects/lab06/third-party/gtest/googletest/src/gtest_main.cc
1: [==========] Running 1 test from 1 test suite.
1: [----------] Global test environment set-up.
1: [----------] 1 test from Print
1: [ RUN      ] Print.InFileStream
1: [       OK ] Print.InFileStream (1 ms)
1: [----------] 1 test from Print (1 ms total)
1:
1: [----------] Global test environment tear-down
1: [==========] 1 test from 1 test suite ran. (5 ms total)
1: [  PASSED  ] 1 test.
1/1 Test #1: check ............................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.02 sec
```
6) В файл ci.yml дописана часть кода:
```yml
$ cat .github/workflows/ci.yml
name: CMake CI

on:
  push:
    branches: [ master, main ]
  pull_request:
    branches: [ master, main ]

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
    - name: Checkout code
      uses: actions/checkout@v4
      with:
        submodules: true

    - name: Install CMake
      run: |
        sudo apt-get update
        sudo apt-get install -y cmake cmake-data

    - name: Configure CMake
      run: cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install -DBUILD_TESTS=ON

    - name: Build
      run: cmake --build _build

    - name: Install
      run: cmake --build _build --target install

    - name: Run tests
      run: cmake --build _build --target test -- ARGS=--verbose
```
7) Все изменения закоммичены и запушены.
8) Репозиторий прошёл все тесты (бейдж об этом в начале отчёта).

## Homework06
1) Были скопированы файлы solver из lab03:
```bash
$  cd ~/KRisti0w/workspace/projects/lab06
$ cp -r ../lab03/formatter_lib .
$ cp -r ../lab03/formatter_ex_lib .
$ cp -r ../lab03/solver_lib .
$ cp -r ../lab03/solver_application .
```
2) Создала DESCRIPTION_SOLVER-текстовый файл с описанием пакета, который попадает в установочный пакет:
```bash
$ cat > DESCRIPTION_SOLVER << 'EOF'
> Solver for quadratic equations.

Usage: solver
Enter coefficients a, b, c (space-separated)
Example: 1 -3 2

The program solves ax² + bx + c = 0 and outputs x1 and x2.
> EOF
```
3) Изменила CMakeLists.txt, добавив Solver и CPack:
```bash
$ cat >> CMakeLists.txt << 'EOF'
> cmake_minimum_required(VERSION 3.10)
project(print)

set(PRINT_VERSION_MAJOR 0)
set(PRINT_VERSION_MINOR 1)
set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_TWEAK 0)
set(PRINT_VERSION ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wno-unused-variable -Wno-maybe-uninitialized -Wno-error)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" OFF)

add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)

target_include_directories(print PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if(BUILD_EXAMPLES)
  file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
  foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} print)
    install(TARGETS ${EXAMPLE_NAME}
      RUNTIME DESTINATION bin
    )
  endforeach()
endif()

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  target_compile_options(gtest PRIVATE -Wno-error)
  target_compile_options(gtest_main PRIVATE -Wno-error)
  file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
  target_link_libraries(check ${PROJECT_NAME} gtest_main)
  add_test(NAME check COMMAND check)
endif()

install(TARGETS print
    EXPORT print-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
install(EXPORT print-config DESTINATION cmake)


add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)

add_executable(solver solver_application/solver.cpp)
target_link_libraries(solver formatter_ex solver_lib)

install(TARGETS solver RUNTIME DESTINATION bin)
set(CPACK_PACKAGE_NAME "solver")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Quadratic equation solver")
set(CPACK_PACKAGE_CONTACT "KRisti0w@example.com")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION_SOLVER")

if(APPLE)
  set(CPACK_GENERATOR "DragNDrop;TGZ")
elseif(WIN32)
  set(CPACK_GENERATOR "ZIP")
else()
  set(CPACK_GENERATOR "TGZ;DEB;RPM")
endif()

include(CPack)
> EOF
```
4) Изменён файл с добавлением permissions: contents: write и правильной командой cmake -S . -B_build, также были удалены RunTests, из-за возникновения ошибок:
```bash
$ cat > .github/workflows/main.yml << 'EOF'
> name: CI

on:
  push:
    branches: [ main, master ]
    tags: [ 'v*' ]
  pull_request:
    branches: [ main, master ]

permissions:
  contents: write

jobs:
  linux-gcc:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      
      - name: Install dependencies
        run: sudo apt-get update && sudo apt-get install -y cmake g++ rpm
      
      - name: Configure
        run: cmake -S . -B_build -DCMAKE_CXX_STANDARD=11
      
      - name: Build
        run: cmake --build _build
      
      - name: Create packages (only for tags)
        if: startsWith(github.ref, 'refs/tags/')
        run: |
          cd _build
          cpack -G "TGZ"
          cpack -G "DEB"
          cpack -G "RPM"
          cd ..
      
      - name: Upload Release Assets
        if: startsWith(github.ref, 'refs/tags/')
        uses: softprops/action-gh-release@v1
        with:
          files: |
            _build/*.tar.gz
            _build/*.deb
            _build/*.rpm
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}

  linux-clang:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      
      - name: Install dependencies
        run: |
          sudo apt-get update
          sudo apt-get install -y cmake clang rpm
      
      - name: Configure
        run: cmake -S . -B_build -DCMAKE_CXX_STANDARD=11 -DCMAKE_CXX_COMPILER=clang++
      
      - name: Build
        run: cmake --build _build
      
      - name: Create packages (only for tags)
        if: startsWith(github.ref, 'refs/tags/')
        run: |
          cd _build
          cpack -G "TGZ"
          cpack -G "DEB"
          cpack -G "RPM"
          cd ..
      
      - name: Upload Release Assets
        if: startsWith(github.ref, 'refs/tags/')
        uses: softprops/action-gh-release@v1
        with:
          files: |
            _build/*.tar.gz
            _build/*.deb
            _build/*.rpm
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}

  windows:
    runs-on: windows-latest
    steps:
      - uses: actions/checkout@v4
      
      - name: Configure
        run: cmake -S . -B_build -DCMAKE_CXX_STANDARD=11
      
      - name: Build
        run: cmake --build _build --config Release
      
      - name: Create packages (only for tags)
        if: startsWith(github.ref, 'refs/tags/')
        run: |
          cd _build
          cpack -G "ZIP"
          cd ..
      
      - name: Upload Release Assets
        if: startsWith(github.ref, 'refs/tags/')
        uses: softprops/action-gh-release@v1
        with:
          files: |
            _build/*.zip
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
> EOF
```
5)  Создание тега для автоматической сборки пакетов:
```bash
$ git tag v2.4.0
$ git push origin v2.4.0
Total 0 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/shirmanovak410-ops/lab06
 * [new tag]         v2.4.0 -> v2.4.0
```
