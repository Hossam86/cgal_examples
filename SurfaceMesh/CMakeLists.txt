cmake_minimum_required(VERSION 3.3)
project(surface_mesh)
find_package(CGAL)
include_directories(${CMAKE_SOURCE_DIR}/eigen)

add_executable(sm_iterators sm_iterators.cpp)
target_link_libraries(sm_iterators CGAL::CGAL)

add_executable(sm_properties sm_properties.cpp)
target_link_libraries(sm_properties CGAL::CGAL)

add_executable(sm_circulators sm_circulators.cpp)
target_link_libraries(sm_circulators CGAL::CGAL)

add_executable(sm_aabbtree sm_aabbtree.cpp)
target_link_libraries(sm_aabbtree CGAL::CGAL)

add_executable(sm_memory sm_memory.cpp)
target_link_libraries(sm_memory CGAL::CGAL)

#add_executable(sm_derivation sm_derivation.cpp)
#target_link_libraries(sm_derivation CGAL::CGAL)

# add_executable(versionTest versionTest.cpp)
# target_link_libraries(versionTest CGAL::CGAL)

# add_executable(holeFill holeFill.cpp)
# target_link_libraries(holeFill CGAL::CGAL)
