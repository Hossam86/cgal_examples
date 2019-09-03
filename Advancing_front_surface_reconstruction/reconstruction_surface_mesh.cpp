#include<CGAL/Surface_mesh.h>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Advancing_front_surface_reconstruction.h>
#include<CGAL/disable_warnings.h>
#include<CGAL/array.h>
#include <iostream>
#include <fstream>
#include <algorithm>

typedef CGAL::cpp11::array<std::size_t,3>Facet;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef CGAL::Surface_mesh<Point_3> Mesh;

struct Construct
{
    Mesh &mesh;
    template<typename PointIterator>
    Construct(Mesh &mesh,PointIterator b, PointIterator e):mesh(mesh)
    {
        for(; b!=e;++b)
        {
            boost::graph_traits<Mesh>::vertex_descriptor v;
            v=add_vertex(mesh);
            mesh.point(v)=*b;
        }
    }

    Construct &operator=(const Facet f)
    {
        typedef  boost::graph_traits<Mesh>::vertex_descriptor vertex_descriptor;
        typedef  boost::graph_traits<Mesh>::vertices_size_type size_type;
        mesh.add_face(vertex_descriptor(static_cast<size_type>(f[0])),
                vertex_descriptor(static_cast<size_type>(f[1])),
                vertex_descriptor(static_cast<size_type>(f[2])));
        return *this;
    }

    Construct &operator*(){return *this;}
    Construct &operator++() {return *this;}
    Construct &operator++(int){return *this;}

};

int main(int argc, char *argv[])
{
    std::ifstream in((argc>1) ? argv[1]:"/media/hossam/MyFiles/cProj/ComputationalGeometry/CGAL_Practice/Advancing_front_surface_reconstruction/data/half.xyz");
    std::vector<Point_3> points;
    std::vector<Facet> facets;
    Mesh mesh;
    std::copy (std::istream_iterator<Point_3>(in), std::istream_iterator<Point_3>(),std::back_inserter(points));

    Construct construct (mesh,points.begin(),points.end());
    CGAL::advancing_front_surface_reconstruction(points.begin(),points.end(),construct);

    std::cout<<mesh<<std::endl;
    std::ofstream out("out.off");
    out<<mesh;
    return 0;
}
