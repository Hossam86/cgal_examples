cmake_minimum_required(VERSION 3.16)
project(cgal_examples VERSION 0.0 LANGUAGES C CXX DESCRIPTION "CGAL Examples")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")

add_subdirectory(surface_mesh)
add_subdirectory(polygon_mesh_processing)
