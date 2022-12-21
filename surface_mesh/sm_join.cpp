#include<CGAL/Surface_mesh.h>
#include<CGAL/Simple_cartesian.h>
#include<fstream>
#include<iostream>


typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;
typedef CGAL::Surface_mesh<Point> Mesh;

typedef  boost::graph_traits<Mesh>::vertex_descriptor vertex_descriptor;

int main(int argc, char *argv[])
{
    Mesh sm1 ,sm2;
    std::ifstream in1((argc>1)? argv[1]:"/media/hossam/MyFiles/cProj/ComputationalGeometry/CGAL_Practice/SurfaceMesh/data/triangle.off");
    in1>>sm1;
    std::ifstream in2((argc>2)? argv[2]:"/media/hossam/MyFiles/cProj/ComputationalGeometry/CGAL_Practice/SurfaceMesh/data/quad.off");
    in2>>sm2;

    Mesh::Property_map<vertex_descriptor,std::string>name1,name2;
    bool created;
    sm1.add_property_map<vertex_descriptor,int>("v:weight",7812);
    boost::tie(name1,created)=sm1.add_property_map<vertex_descriptor,std::string>("v:name","hello");
    boost::tie(name2,created)=sm2.add_property_map<vertex_descriptor,std::string>("v:name","world");

    //

    //merge
    sm1+=sm2;

    //print vertices and names;
    std::cout << "vertex" << "<-->" << "name" <<std::endl;
    BOOST_FOREACH(vertex_descriptor vd, vertices(sm1))
    {
        std::cerr <<vd <<"<-->"<<name1[vd] <<std::endl;
    }

    // print sm1 mesh ;
    std::cout<<"\n"<< sm1 <<std::endl;
    return 0;
}
