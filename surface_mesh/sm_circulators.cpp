#include<CGAL/Simple_cartesian.h>
#include<CGAL/Surface_mesh.h>

#include<boost/foreach.hpp>

typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Surface_mesh<K::Point_3> Mesh;
typedef Mesh::vertex_index vertex_descriptor;
typedef Mesh::Face_index  face_descriptor;


int main()
{
    Mesh m;
    // u            x
    // +------------+
    // |            |
    // |            |
    // |      f     |
    // |            |
    // |            |
    // +------------+
    // v            w

    // Add the points as vertices
    vertex_descriptor u =m.add_vertex(K::Point_3(0,1,0));
    vertex_descriptor v=m.add_vertex(K::Point_3(0,0,0));
    vertex_descriptor w=m.add_vertex(K::Point_3(1,0,0));
    vertex_descriptor x=m.add_vertex(K::Point_3(1,1,0));

    face_descriptor f=m.add_face(u,v,w,x);
    {
        std::cout << "vertices around vertex(using circulator) " << v << std::endl;
        CGAL::Vertex_around_target_circulator<Mesh> vb(m.halfedge(v),m),ve;
        ve=vb;
        do {
            std::cout<<*vb++ <<std::endl;

        } while (vb!=ve);
    }
    {
        std::cout << "vertices around vertex(using iterator) " << v << std::endl;
//        CGAL::Vertex_around_target_iterator<Mesh> vb(m.halfedge(v),m), ve;
        CGAL::Vertex_around_target_iterator<Mesh>vb,ve;
        for(boost::tie(vb,ve)=vertices_around_target(v,m);vb!=ve;++vb)
        {
            std::cout<<*vb << std::endl;
        }
    }
    {
        std::cout<<"vertices around face " << f <<std::endl;
        CGAL::Vertex_around_face_iterator<Mesh> vbegin,vend;
        for(boost::tie(vbegin,vend)=vertices_around_face(m.halfedge(f),m);vbegin!=vend;++vbegin)
        {
            std::cout<<*vbegin<<std::endl;
        }
    }
    // or the same again, but directly with a range based loop
    BOOST_FOREACH(vertex_descriptor vd, vertices_around_face(m.halfedge(f),m))
    {
        std::cout << vd <<std::endl;
    }


}



