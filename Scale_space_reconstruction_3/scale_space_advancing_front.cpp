#include <fstream>
#include <iostream>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include<CGAL/Point_set_3.h>
#include<CGAL/Point_set_3/IO.h>
#include<CGAL/Scale_space_surface_reconstruction_3.h>
#include<CGAL/Scale_space_reconstruction_3/Advancing_front_mesher.h>
#include<CGAL/Scale_space_reconstruction_3/Jet_smoother.h>

#include<CGAL/IO/read_off_points.h>
#include<CGAL/Timer.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Scale_space_surface_reconstruction_3<K> Reconstruction;
typedef CGAL::Scale_space_reconstruction_3::Advancing_front_mesher<K> Mesher;
typedef CGAL::Scale_space_reconstruction_3::Jet_smoother<K> Smoother;

typedef K::Point_3 Point;
typedef CGAL::Point_set_3<Point>Point_set;

typedef Reconstruction::Facet_const_iterator Facet_iterator;

int main(int argc, char *argv[])
{

    //Read the data
    Point_set points;
    std::ifstream in ((argc>1)?argv[1]:"/media/hossam/MyFiles/cProj/ComputationalGeometry/CGAL_Practice/Scale_space_reconstruction_3/data/kitten.off");
    std::cerr<<"Reading" << std::endl;
    in>>points;
    if(points.is_empty())
    {
        std::cerr<< "Error:cannot read the file"<<std::endl;
        return EXIT_FAILURE;
    }

    std::cerr<<"done: " <<points.size()<<" points." <<std::endl;
    std::cerr<<"Reconstruction ";

    CGAL::Timer t;
    t.start();

    //Constuct the mesh in a scale space
    Reconstruction reconstruct(points.points().begin(),points.points().end());
    reconstruct.increase_scale<Smoother>(4);
    reconstruct.reconstruct_surface(Mesher(0.5));
    std::cerr<<" done in " <<t.time() << " sec" <<std::endl;
    t.reset();

    std::ofstream out("out.off");
    out << "OFF" <<std::endl<<points.size() << " " <<reconstruct.number_of_facets()<<" 0" <<std::endl;
    for (Point_set::iterator it =points.begin();it!=points.end();++it)
    {
        out<<points.point(*it)<<std::endl;
    }

    for(Reconstruction::Facet_iterator it=reconstruct.facets_begin();it!=reconstruct.facets_end();++it)
    {
        out << "3 " <<(*it)[0]<<" "<<(*it)[1] <<" "<<(*it)[2]<<std::endl;
    }
    out.close();
    std::cerr << "Writing result in " <<t.time()<<" sec." <<std::endl;
    t.reset();
    std::cerr << "Done." << std::endl;
    return  EXIT_SUCCESS;
}

