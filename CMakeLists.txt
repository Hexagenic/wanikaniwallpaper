cmake_minimum_required(VERSION 2.8)

project(wanikaniwallpaper)

add_compile_options(-std=c++11)

find_package(Freetype REQUIRED)
find_package(PNG REQUIRED)
find_package(CURL REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

find_package(PkgConfig REQUIRED)

pkg_check_modules(JSONCPP jsoncpp)

include_directories(
  src
  ${FREETYPE_INCLUDE_DIRS}
  ${PNG_INCLUDE_DIRS}
  ${CURL_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${JSONCPP_INCLUDE_DIRS})

set(SRC
  src/main.cpp
  src/api.hpp
  src/api.cpp
  src/color.hpp
  src/color.cpp
  src/grid.hpp
  src/grid.cpp
  src/kanji.hpp
  src/kanji.cpp
  src/options.hpp
  src/options.cpp
  src/order.hpp
  src/order.cpp
  src/order-data.hpp
  ${CMAKE_CURRENT_BINARY_DIR}/src/order-data.cpp
  src/heisig-data.hpp
  ${CMAKE_CURRENT_BINARY_DIR}/src/heisig-data.cpp
  src/renderer.hpp
  src/renderer.cpp)

file(READ ${CMAKE_SOURCE_DIR}/order ORDER)
file(READ ${CMAKE_SOURCE_DIR}/heisig HEISIG)

configure_file("src/order-data.cpp.in" "src/order-data.cpp")
configure_file("src/heisig-data.cpp.in" "src/heisig-data.cpp")

add_executable(wanikaniwallpaper ${SRC})

target_link_libraries(wanikaniwallpaper
  ${FREETYPE_LIBRARIES}
  ${PNG_LIBRARIES}
  ${CURL_LIBRARIES}
  ${Boost_LIBRARIES}
  ${JSONCPP_LIBRARIES})

