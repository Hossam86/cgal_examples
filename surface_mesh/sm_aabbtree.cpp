#include<CGAL/Simple_cartesian.h>
#include<CGAL/Surface_mesh.h>

#include<CGAL/AABB_tree.h>
#include<CGAL/AABB_traits.h>
#include<CGAL/AABB_face_graph_triangle_primitive.h>

#include<CGAL/boost/graph/Euler_operations.h>

typedef CGAL::Simple_cartesian<double>K;
typedef K::Point_3 Point;
typedef K::Plane_3 Plane;
typedef K::Vector_3 Vector;
typedef K::Segment_3 Segment;
typedef CGAL::Surface_mesh<Point> Mesh;

//AABBtree
typedef CGAL::AABB_face_graph_triangle_primitive<Mesh> Primitive;
typedef CGAL::AABB_traits<K,Primitive> Traits;
typedef CGAL::AABB_tree<Traits> Tree;

//Intersection
typedef boost::optional<Tree::Intersection_and_primitive_id<Segment>::Type> Segment_intersection;
typedef boost::optional<Tree::Intersection_and_primitive_id<Plane>::Type> Plane_Intersection;
typedef Tree::Primitive_id Primitive_id;

int main()
{
    Point p(1.0,0.0,0.0);
    Point q(0.0,1.0,0.0);
    Point r(0.0,0.0,1.0);
    Point s(0.0,0.0,0.0);

    Mesh m;
    CGAL::make_tetrahedron(p,q,r,s,m);

    //construct AABB tree
    Tree tree(faces(m).first,faces(m).second,m);

    // constructs segment query
    Point a(-0.2, 0.2, -0.2);
    Point b(1.3, 0.2, 1.3);
    Segment segment_query(a,b);

    // tests intersections with segment query
    if(tree.do_intersect(segment_query))
        std::cout << "intersection(s)" << std::endl;
    else
        std::cout<< "no intersections" <<std::endl;

    // computes #intersections with segment query

    std::cout<<tree.number_of_intersected_primitives(segment_query)<<std::endl;
    // computes first encountered intersection with segment query
    // (generally a point)

    Segment_intersection intersection=tree.any_intersection(segment_query);
    if(intersection)
    {
        //gets intersection object
       if(boost::get<Point>(&(intersection->first)))
       {
           Point *p=boost::get<Point>(&(intersection->first));
           std::cout<< "Intersection object is a point " <<*p<<std::endl;
           std::cout << "with face " <<intersection->second <<std::endl;
       }

    }

    //compute all intersections with segment query (as pairs object -primitive_id)
    std::list<Segment_intersection> intersections;
    tree.all_intersections(segment_query,std::back_inserter(intersections));

    //computes all intersected primitives with segment query as primitive ids
    std::list<Primitive_id>Primitives;
    tree.all_intersected_primitives(segment_query,std::back_inserter(Primitives));

    //construct plane query
    Point base(0.0,0.0,0.5);
    Vector vec(0.0,0.0,1.0);
    Plane Plane_query(base,vec);

    //computes first encountred intersection with plane query
    Plane_Intersection plane_intersection=tree.any_intersection(Plane_query);
    if(plane_intersection)
    {
        if(boost::get<Segment>(&(plane_intersection->first)))
        {
           Segment *s =boost::get<Segment>(&(plane_intersection->first));
           std::cout << "one intersection object is the segment " << s << std::endl;
           std::cout << "with face "<< intersection->second  <<  std::endl;
        }
    }
return EXIT_SUCCESS;
}
