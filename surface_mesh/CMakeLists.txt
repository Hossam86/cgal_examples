cmake_minimum_required(VERSION 3.3)
project(surface_mesh)
find_package(CGAL)
include_directories(${CMAKE_SOURCE_DIR}/eigen)
#include_directories(${Boost_INCLUDE_DIRS})
include(${CGAL_USE_FILE})
message(STATUS ${CGAL_USE_FILE})
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

add_executable(sm_derivation sm_derivation.cpp)
target_link_libraries(sm_derivation CGAL::CGAL)

# add_executable(versionTest versionTest.cpp)
# target_link_libraries(versionTest CGAL::CGAL)

# add_executable(holeFill holeFill.cpp)
# target_link_libraries(holeFill CGAL::CGAL)

add_executable(sm_do_intersection sm_do_intersect.cpp)
target_link_libraries(sm_do_intersection CGAL::CGAL)

add_executable(sm_join sm_join.cpp)
target_link_libraries(sm_join CGAL::CGAL)

add_executable(sm_bgl sm_bgl.cpp)
target_link_libraries(sm_bgl CGAL::CGAL)
