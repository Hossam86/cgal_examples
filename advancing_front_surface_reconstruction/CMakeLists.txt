cmake_minimum_required(VERSION 3.10)
project(Advancing_front_surface_reconstruction)
find_package(CGAL)

add_executable(sm_reconstruct reconstruction_surface_mesh.cpp)
target_link_libraries(sm_reconstruct CGAL::CGAL)

