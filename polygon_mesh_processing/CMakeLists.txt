cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W")

project(Polygon_Mesh_Processing)


find_package(CGAL)
include(${CGAL_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/eigen)

add_executable(refine_fair refine_fair.cpp)
target_link_libraries(refine_fair CGAL::CGAL)

add_executable(triangulate_faces triangulate_faces.cpp)
target_link_libraries(triangulate_faces CGAL::CGAL)

add_executable(Isotropic_remeshing Isotropic_remeshing.cpp)
target_link_libraries(Isotropic_remeshing CGAL::CGAL)

add_executable(test test.cpp)
target_link_libraries(test CGAL::CGAL)

add_executable(versionTest versionTest.cpp)
target_link_libraries(versionTest CGAL::CGAL)

add_executable(holeFill_polyLine holeFill_polyLine.cpp)
target_link_libraries(holeFill_polyLine ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})

add_executable(poisson poisson_recons.cpp)
target_link_libraries(poisson CGAL::CGAL)

add_executable(detectFeature detectFeatures.cpp)
target_link_libraries(detectFeature ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})
