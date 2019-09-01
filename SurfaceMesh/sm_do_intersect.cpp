#include<CGAL/Exact_predicates_exact_constructions_kernel.h>
#include<CGAL/Surface_mesh.h>
#include<CGAL/box_intersection_d.h>
#include<fstream>
#include <CGAL/Timer.h>

#include <boost/functional/value_factory.hpp>
#include<boost/bind.hpp>
#include<boost/range/algorithm/transform.hpp>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef K::Triangle_3 Triangle_3;

typedef CGAL::Surface_mesh<Point_3> Mesh;
typedef boost::graph_traits<Mesh>::face_descriptor face_descriptor;
typedef boost::graph_traits<Mesh>::halfedge_descriptor halfedge_descriptor;
typedef CGAL::Bbox_3 Bbox_3;

typedef  CGAL::Timer Timer;


//small helper function to extract triangle from face;

Triangle_3 triangle(const Mesh &m,face_descriptor f )
{
    halfedge_descriptor hf=m.halfedge(f);
    Point_3 a=m.point(m.target(hf));
    hf=m.next(hf);
    Point_3 b=m.point(m.target(hf));
    hf=m.next(hf);
    Point_3 c=m.point(m.target(hf));

    return Triangle_3(a,b,c);

}

class Box :public CGAL::Box_intersection_d::Box_d<double,3,CGAL::Box_intersection_d::ID_NONE>
{
private:
    typedef CGAL::Box_intersection_d::Box_d<double,3,CGAL::Box_intersection_d::ID_NONE>Base;
    face_descriptor fd;

public:
    typedef double NT;
    typedef std::size_t ID;

    Box(face_descriptor f, const Mesh&m):Base(triangle(m,f).bbox()),fd(f){}
    Box(const Bbox_3 &b,face_descriptor fd ):Base(b),fd(fd){}
    face_descriptor f() const {return  fd;}
    ID id() const {return static_cast<ID>(fd);}
};



struct Callback{
    Callback(const Mesh &P,const Mesh &Q , unsigned int &i):P(P),Q(Q),count(i){}


    void operator() (const Box * bp, const Box * bq)
    {
        face_descriptor fp=bp->f();
        Triangle_3 tp=triangle(P,fp);

        face_descriptor fq=bq->f();
        Triangle_3 tq=triangle(Q,fq);

        if(do_intersect(tp,tq))
        {
            ++count;
        }
    }


    const Mesh&P;
    const Mesh&Q;
    unsigned  int& count;
};

const  Box* address_of_box(const Box &bbox)
{
    return  &bbox;
}
unsigned int intersect (const Mesh &P,const Mesh &Q)
{
    std::vector<Box> P_boxes,Q_boxes;
    std::vector<const Box*> P_box_ptr,Q_box_ptr;
    P_boxes.reserve(P.number_of_faces());
    Q_boxes.reserve(Q.number_of_faces());
    P_box_ptr.reserve(P.number_of_faces());
    Q_box_ptr.reserve(Q.number_of_faces());

    //build boxes and pointers to boxes;
    boost::transform(P.faces(), std::back_inserter(P_boxes),boost::bind(boost::value_factory<Box>(),_1,boost::cref(P)));
    std::transform(P_boxes.begin(),P_boxes.end(),std::back_inserter(P_box_ptr),&address_of_box);

    boost::transform(Q.faces(),std::back_inserter(Q_boxes),boost::bind(boost::value_factory<Box>(),_1,boost::cref(Q)));

    std::transform(Q_boxes.begin(),Q_boxes.end(),std::back_inserter(Q_box_ptr),&address_of_box);

    unsigned int i=0;
    Callback c(P,Q,i);
    CGAL::box_intersection_d(P_box_ptr.begin(),P_box_ptr.end(),Q_box_ptr.begin(),Q_box_ptr.end(),c);

    return i;
}




int main(int argc , char** argv)
{
    std::cout.precision(17);
    Mesh P,Q;

    if (argc < 3)
    {
        std::cerr << "Usage: do_intersect <mesh_1.off> <mesh_2.off" <<std::endl;
        return  EXIT_FAILURE;
    }

    std::ifstream inP(argv[1]);
    inP>>P;

    std::ifstream inQ(argv[2]);
    inQ>>Q;

    Timer timer;
    timer.start();
    unsigned int num_intersections=intersect(P,Q);
    timer.stop();
    std::cout << "Counted " <<num_intersections  << " in "
              <<timer.time() << " seconds." <<std::endl;
    return 0;
}

