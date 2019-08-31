#include<iostream>

#include<CGAL/Simple_cartesian.h>
#include<CGAL/Surface_mesh.h>

typedef CGAL::Simple_cartesian<double>K;
typedef CGAL::Surface_mesh<K::Point_3> Mesh;
typedef Mesh::vertex_index vertex_dexcrriptor;

int main()
{
    Mesh m;
    Mesh::vertex_index u;
    for(unsigned int i=0; i<5 ;++i)
    {
        Mesh::Vertex_index v=m.add_vertex(K::Point_3(0,0,i+1));
        if (i==2) u=v;
    }
    m.remove_vertex(u);
    std::cout << "After insertion of 5 vertices and removal of the 3. vertex\n"
              << "# vertices  / # vertices + # removed vertices = "
              <<m.number_of_vertices()
             <<" / "<<m.number_of_vertices()+m.number_of_removed_vertices()<<std::endl;

    std::cout <<"iterate over vertices " <<std::endl;
    {
        BOOST_FOREACH(vertex_dexcrriptor vd , m.vertices())
        {
            std::cout<<m.point(vd)<<std::endl;
        }
    }


    // The status of being used or removes is stored in ap property_map
    Mesh::Property_map<Mesh::Vertex_index,bool> removed
            =m.add_property_map<Mesh::vertex_index,bool>("v:removed").first;

    std::cout <<"\nItrerate over vertices and deleted vertices\n"
             <<"#vertices /# vertices+ #removes vertices = "
            <<m.number_of_vertices()
           << " / " << m.number_of_vertices()+m.number_of_removed_vertices() <<std::endl;
    {
        unsigned int i=0,end=m.number_of_vertices()+m.number_of_removed_vertices();
        for (;i<end;++i) {
            vertex_dexcrriptor vh(i);
            assert(m.is_removed(vh)==removed[vh]);
            std::cout <<m.point(vh) <<((m.is_removed(vh))? " R\n" : "\n");
        }
    }
    m.collect_garbage();
    std::cout<<" after garbage collecation\n"
            << "# vertices / # vertices + # removed vertices = "
            <<m.number_of_vertices()
           <<" / " << m.number_of_vertices()+m.number_of_removed_vertices() <<std::endl;
    {
        unsigned i=0, end=m.number_of_vertices()+m.number_of_removed_vertices();
        for (;i<end;++i) {
            vertex_dexcrriptor vh(i);
            std::cout <<m.point(vh) <<((m.is_removed(vh)) ? " R\n": "\n");
        }
    }
    return 0;
}

