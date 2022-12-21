#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Polygon_mesh_processing/triangulate_hole.h>
#include<CGAL/utility.h>

#include<vector>
#include<iterator>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point;

int main()
{
    std::vector<Point> polyline;
    polyline.push_back(Point(1.0,0.,0.));
    polyline.push_back(Point(0.,1.,0.));
    polyline.push_back(Point(-1.,0.,0.));
    polyline.push_back(Point( 1.,1.,0.));
    // repeating first point (i.e. polyline.push_back(Point(1.,0.,0.)) ) is optional
    // any type, having Type(int, int, int) constructor available, can be used to hold output triangles

    typedef CGAL::Triple<int, int, int> Triangle_int;
    std::vector<Triangle_int>patch;

    patch.reserve(polyline.size()); //there will be exaclty n-2 triangels in tyhe patch
    CGAL::Polygon_mesh_processing::triangulate_hole_polyline(polyline,std::back_inserter(patch));
    for (std::size_t i=0; i<patch.size();++i)
    {
//        std::cout << "Triangle " << i << ": "
//                  <<patch[i].first<<" "<<pa

    }

}
