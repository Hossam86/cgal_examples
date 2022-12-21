#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Simple_cartesian.h>

#include <CGAL/Polygon_mesh_processing/refine.h>
#include <CGAL/Polygon_mesh_processing/fair.h>


#include <fstream>
#include <map>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef  CGAL::Surface_mesh<Kernel::Point_3> surfaceMesh;
typedef Polyhedron::Vertex_handle vertex_handle;
typedef surfaceMesh::vertex_index vertex_descriptor;
typedef surfaceMesh::face_index face_descriptor;

//extract vertices which are most k (inclusive)
//far from vertex v in the graph of edges

void extract_k_ring(vertex_handle v, int k, std::vector<vertex_handle> &qv)
{
    std::map<vertex_handle, int> D;
    qv.push_back(v);
    D[v] = 0;
    std::size_t current_index = 0;
    int dist_v;
    while (current_index < qv.size() && (dist_v = D[qv[current_index]]) < k)
    {
        v = qv[current_index++];
        Polyhedron::Halfedge_around_vertex_circulator e(v->vertex_begin());
        Polyhedron::Halfedge_around_vertex_circulator e_end(e);
        do
        {
            vertex_handle new_v = e->opposite()->vertex();
            if (D.insert(std::make_pair(new_v, dist_v + 1)).second)
            {
                qv.push_back(new_v);
            }
        } while (++e != e_end);
    }
}


void PolygedronTest()
{
  const char *filename = "D:/CGAL_Practice/PolygonMeshProcessing/data/blobby.off";
    std::ifstream input(filename);
    Polyhedron poly;
    if (!input || !(input >> poly) || poly.empty() || !CGAL::is_triangle_mesh(poly))
    {
        std::cerr << "Not a Vaild input file." << std::endl;
        return ;
    }

    std::vector<Polyhedron::Facet_handle> new_facets;
    std::vector<vertex_handle> new_vertices;

    CGAL::Polygon_mesh_processing::refine(poly,
                                          faces(poly),
                                          std::back_inserter(new_facets),
                                          std::back_inserter(new_vertices),
                                          CGAL::Polygon_mesh_processing::parameters::density_control_factor(20.0));

    std::ofstream refined_off("refined.off");
    refined_off << poly;
    refined_off.close();
    std::cout << "Refinement added " << new_vertices.size() << " vertices." << std::endl;

    /*fair*/
    Polyhedron::Vertex_iterator v = poly.vertices_begin();
    std::advance(v, 82); /*e.g*/
    std::vector<vertex_handle> region;
    extract_k_ring(v, 12 /*e.g.*/, region);
    bool sucess = CGAL::Polygon_mesh_processing::fair(poly, region);
    std::cout << "Fairing_off" << (sucess ? "succeded" : "failed") << std::endl;
    std::ofstream faired_off("faired.off");
    faired_off << poly;
    faired_off.close();
    return ;
}

void surfaceMeshTest()
{
    const char *filename = "D:/CGAL_Practice/PolygonMeshProcessing/data/blobby.off";
    std::ifstream input(filename);
    surfaceMesh smesh;
    if (!input || !(input >> smesh) || smesh.is_empty() || !CGAL::is_triangle_mesh(smesh))
    {
        std::cerr << "Not a Vaild input file." << std::endl;
        return ;
    }
    std::vector<face_descriptor> new_facets;
    std::vector<vertex_descriptor> new_vertices;
    CGAL::Polygon_mesh_processing::refine(smesh,
                                          faces(smesh),
                                          std::back_inserter(new_facets),
                                          std::back_inserter(new_vertices),
                                          CGAL::Polygon_mesh_processing::parameters::density_control_factor(20.0));
    std::ofstream refined_off("refined.off");
    refined_off << smesh;
    refined_off.close();
    std::cout << "Refinement added " << new_vertices.size() << " vertices." << std::endl;



}
int main(int argc, char const *argv[])
{
//    PolygedronTest();
    surfaceMeshTest();
    return 0;

}
