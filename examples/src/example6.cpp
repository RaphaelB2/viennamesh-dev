#include <iostream>
#include <boost/concept_check.hpp>
#include <CGAL/Line_2.h>




#include "viennagrid/domain/config.hpp"
#include "viennagrid/domain/element_creation.hpp"
#include "viennagrid/io/vtk_writer.hpp"
#include "viennagrid/algorithm/geometry.hpp"
#include "viennagrid/algorithm/cross_prod.hpp"

#include "viennagrid/io/poly_reader.hpp"

#include "viennamesh/algorithm/cgal_plc_mesher.hpp"
#include "viennagrid/domain/neighbour_iteration.hpp"
#include "viennagrid/algorithm/geometry.hpp"

#include "viennamesh/base/segments.hpp"



#include "viennamesh/algorithm/vgmodeler_hull_adaption.hpp"
#include "viennamesh/algorithm/netgen_tetrahedron_mesher.hpp"








int main()
{
    viennagrid::config::plc_3d_domain plc_domain;
    
    
    viennagrid::io::poly_reader reader;
    reader(plc_domain, "../../examples/data/big_and_small_cube.poly");
    
    
    viennagrid::config::triangular_3d_domain triangulated_plc_domain;
    viennamesh::result_of::settings<viennamesh::cgal_plc_3d_mesher_tag>::type plc_settings(0.0, 0.0);
    
    viennamesh::run_algo< viennamesh::cgal_plc_3d_mesher_tag >( plc_domain, triangulated_plc_domain, plc_settings );
    
    {
        viennagrid::io::vtk_writer<viennagrid::config::triangular_3d_domain, viennagrid::config::triangular_3d_cell> vtk_writer;
        vtk_writer(triangulated_plc_domain, "meshed_plc_hull");
    }

    
    
    typedef typename viennagrid::result_of::point_type<viennagrid::config::triangular_3d_domain>::type point_type;
    
    std::cout << "Num triangle after PLC meshing: " << viennagrid::elements<viennagrid::triangle_tag>( triangulated_plc_domain ).size() << std::endl;
    
    std::cout << std::endl << std::endl << std::endl;
    viennamesh::detect_and_mark_facet_segment( triangulated_plc_domain, point_type(0.0, 0.0, 0.0), 0 );
    std::cout << std::endl << std::endl << std::endl;
    viennamesh::detect_and_mark_facet_segment( triangulated_plc_domain, point_type(0.0, 0.0, 20.0), 1 );
    std::cout << std::endl << std::endl << std::endl;
    
    

    
    viennagrid::config::triangular_3d_domain oriented_adapted_hull_domain;
    viennamesh::result_of::settings<viennamesh::vgmodeler_hull_adaption_tag>::type vgm_settings;
    
    vgm_settings.cell_size = 3.0;
    
    viennamesh::run_algo< viennamesh::vgmodeler_hull_adaption_tag >( triangulated_plc_domain, oriented_adapted_hull_domain, vgm_settings );
    
    
    {        
        viennagrid::io::vtk_writer<viennagrid::config::triangular_3d_domain, viennagrid::config::triangular_3d_cell> vtk_writer;
        vtk_writer(oriented_adapted_hull_domain, "netgen_adapt_hull");
    }

    

    
    viennagrid::config::tetrahedral_3d_domain tetrahedron_domain;
    viennamesh::result_of::settings<viennamesh::netgen_tetrahedron_tag>::type netgen_settings;
    
    netgen_settings.cell_size = 3.0;
    
    viennamesh::run_algo< viennamesh::netgen_tetrahedron_tag >( oriented_adapted_hull_domain, tetrahedron_domain, netgen_settings );
    
    
    {        
        viennagrid::io::vtk_writer<viennagrid::config::tetrahedral_3d_domain, viennagrid::config::tetrahedral_3d_cell> vtk_writer;
        vtk_writer(tetrahedron_domain, "netgen_volume");
    }

    
    
}
