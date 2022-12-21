#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/remesh.h>
#include <CGAL/Polygon_mesh_processing/border.h>
#include <CGAL/Timer.h>
#include <boost/function_output_iterator.hpp>
#include <fstream>
#include <vector>
#include<CGAL/IO/STL_reader.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Surface_mesh<K::Point_3> Mesh;
typedef boost::graph_traits<Mesh>::halfedge_descriptor halfedge_descriptor;
typedef boost::graph_traits<Mesh>::edge_descriptor edge_descriptor;

namespace PMP = CGAL::Polygon_mesh_processing;

typedef K::Point_3 Point_3;
typedef K::Vector_3 Vector_3;


struct halfedge2edge {
    halfedge2edge(const Mesh &m, std::vector<edge_descriptor> &edges) : msh(m), msh_edgs(edges) {}

    void operator()(const halfedge_descriptor &h) const {
        msh_edgs.push_back(edge(h, msh));
    }

    const Mesh &msh;
    std::vector<edge_descriptor> &msh_edgs;
};

void mesh_from_file(const char *fileName, Mesh &mesh) {
    std::ifstream input(fileName);
    std::vector<K::Point_3> points;
    std::vector<std::array<int, 3>> stl_faces;
    CGAL::read_STL(input, points, stl_faces);

    if (!CGAL::Polygon_mesh_processing::orient_polygon_soup(points, stl_faces)) {
        std::cerr << fileName << ("File does not describe a polygon mesh.\n");
    }
    CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(points, stl_faces, mesh);
}

int main(int argc, char **argv) {
    const char *fileName = (argc > 1 ? argv[1] : "D:/DATA_PUBLIC/3D.stl");
    std::ifstream input(fileName);
    Mesh mesh;
//    if (!input || !(input >> mesh) || mesh.is_empty()) {
//        std::cerr << " Not a vaild input file " << std::endl;
//        return 1;
//    }
    mesh_from_file(fileName, mesh);

    CGAL::Timer timer;
    double target_edge_length = 0.5;
    unsigned int nb_iter = 3;
    std::cout << "#Split border..." << std::endl;
    timer.start();
    std::vector<edge_descriptor> border;
    PMP::border_halfedges(faces(mesh),
                          mesh,
                          boost::make_function_output_iterator(halfedge2edge(mesh, border)));
    timer.stop();
    std::cout << "#done in " << timer.time() << " sec" << std::endl;
    timer.reset();
    timer.start();
    std::cout << "#Split long edges  " << std::endl;
    PMP::split_long_edges(border, target_edge_length, mesh);
    timer.stop();
    std::cout << "#done in .. " << timer.time() << " sec" << std::endl;
    timer.reset();
    timer.start();
    std::cout << "#Start remeshing of " << fileName
              << " (" << num_faces(mesh) << " faces)..." << std::endl;
    PMP::isotropic_remeshing(faces(mesh), target_edge_length, mesh,
                             PMP::parameters::number_of_iterations(nb_iter).protect_constraints(
                                     true) //i.e. protect border, here
    );
    timer.stop();
    std::cout << "#Remeshing done. in " << timer.time() << " sec" << std::endl;
    std::cout << "#writing mesh file" << std::endl;
    const char *outfilename = "D:\\DATA_PRIVATE\\temp\\extruded_mesh_cgal.off";
    std::ofstream outmesh(outfilename);
    outmesh << mesh;
    return 0;
}


