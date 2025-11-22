cmake_minimum_required(VERSION 3.20)

project(
  Liboom
  VERSION 1.0.0
  LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(LIBOOM_SOURCES src/liboom.c)

add_library(liboom_shared SHARED ${LIBOOM_SOURCES})
set_target_properties(liboom_shared PROPERTIES VERSION ${PROJECT_VERSION}
                                               SOVERSION 1)
add_library(liboom_static STATIC ${LIBOOM_SOURCES})

foreach(target liboom_shared liboom_static)
  set_target_properties(${target} PROPERTIES OUTPUT_NAME oom
                                             POSITION_INDEPENDENT_CODE ON)
  target_include_directories(
    ${target} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                     $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
endforeach()

add_library(Liboom::shared ALIAS liboom_shared)
add_library(Liboom::static ALIAS liboom_static)

include(GNUInstallDirs)
install(
  TARGETS liboom_shared liboom_static
  EXPORT LiboomTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
  DIRECTORY src/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING
  PATTERN "*.h")

install(
  EXPORT LiboomTargets
  FILE LiboomTargets.cmake
  NAMESPACE Liboom::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Liboom)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/LiboomConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  cmake/LiboomConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/LiboomConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Liboom)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/LiboomConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/LiboomConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Liboom)

find_program(VALGRIND_EXECUTABLE valgrind REQUIRED)
set(MEMORYCHECK_COMMAND ${VALGRIND_EXECUTABLE})
set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --error-exitcode=1")

enable_testing()
include(CTest)
add_subdirectory(tests)

find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/docs)
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_GENERATE_TREEVIEW YES)
  set(DOXYGEN_HTML_DYNAMIC_SECTIONS YES)
  set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
  set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})
  set(DOXYGEN_PROJECT_NUMBER ${PROJECT_VERSION})
  set(DOXYGEN_PROJECT_BRIEF "Simple library for text menus")
  set(DOXYGEN_STRIP_FROM_PATH ${CMAKE_SOURCE_DIR}/src)
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${CMAKE_SOURCE_DIR}/README.md)
  doxygen_add_docs(docs src/liboom.h README.md ALL)
endif()
