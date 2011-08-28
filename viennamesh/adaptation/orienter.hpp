/* =============================================================================
   Copyright (c) 2011, Institute for Microelectronics, TU Wien
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMesh - The Vienna Mesh Generation Framework
                             -----------------

   authors:    Josef Weinbub                         weinbub@iue.tuwien.ac.at
               Franz Stimpfl


   license:    see file LICENSE in the base directory
============================================================================= */

#ifndef VIENNAMESH_ADAPTORS_ORIENTER_HPP
#define VIENNAMESH_ADAPTORS_ORIENTER_HPP

// *** vienna includes
#include "viennamesh/adaptation/base.hpp"
#include "viennamesh/tags.hpp"
#include "viennagrid/domain.hpp"
#include "viennagrid/config/simplex.hpp"


// *** boost includes
#include <boost/shared_ptr.hpp>

//#define MESH_ADAPTOR_DEBUG

/*

basic idea:
get the normal vector of a seed/start/reference cell and determine how often 
the line of this normal vector intersects with faces of the mesh.
if the number of intersections is an even number, the normal vector points outwards.
if it's an odd number, the normal vector points inwards.

*/

namespace viennamesh {

template <>
struct mesh_adaptor <viennamesh::tag::orienter>
{
   typedef double          numeric_type;
   typedef std::size_t     index_type;

   typedef viennagrid::result_of::domain<viennagrid::config::triangular_3d>::type     domain_type;
   typedef boost::shared_ptr< domain_type >                          input_type;
   typedef input_type                                                result_type;

   typedef domain_type::config_type                     DomainConfiguration;

   typedef DomainConfiguration::numeric_type            CoordType;
   typedef DomainConfiguration::dimension_tag           DimensionTag;
   typedef DomainConfiguration::cell_tag                CellTag;

   typedef domain_type::segment_type                                                                  SegmentType;
   typedef viennagrid::result_of::point<DomainConfiguration>::type                               PointType;
   typedef viennagrid::result_of::ncell<DomainConfiguration, 0>::type                            VertexType;
   typedef viennagrid::result_of::ncell<DomainConfiguration, 1>::type                            EdgeType;   
   typedef viennagrid::result_of::ncell<DomainConfiguration, CellTag::topology_level>::type      CellType;
   typedef viennagrid::result_of::ncell_range<SegmentType, CellTag::topology_level>::type         CellContainer;      
   typedef viennagrid::result_of::iterator<CellContainer>::type                                       CellIterator;      
   typedef viennagrid::result_of::ncell_range<CellType, 0>::type                                  VertexOnCellContainer;
   typedef viennagrid::result_of::iterator<VertexOnCellContainer>::type                               VertexOnCellIterator;      
   typedef viennagrid::result_of::ncell_range<CellType, 1>::type                                  EdgeOnCellContainer;
   typedef viennagrid::result_of::iterator<EdgeOnCellContainer>::type                                 EdgeOnCellIterator;      
   typedef viennagrid::result_of::ncell_range<EdgeType, CellTag::topology_level>::type            CellOnEdgeContainer;
   typedef viennagrid::result_of::iterator<CellOnEdgeContainer>::type                                 CellOnEdgeIterator;   
   
   static const int DIMG = DomainConfiguration::dimension_tag::value;
   static const int DIMT = DomainConfiguration::cell_tag::topology_level;   
   static const int CELLSIZE = DIMT+1;      

   // --------------------------------------------------------------------------         
   mesh_adaptor();
  ~mesh_adaptor();
   // --------------------------------------------------------------------------     
   result_type operator()(domain_type& domain);
   result_type operator()(input_type  domain);
   // --------------------------------------------------------------------------     
private:
   // --------------------------------------------------------------------------     
   template<typename SegmentT>
   bool cell_orienter(SegmentT& segment, std::size_t& corrected_cells);

   template<typename CellT>
   bool is_consistant_orientation(CellT & c1, CellT & c2);
   // --------------------------------------------------------------------------     
   std::string id;
   // --------------------------------------------------------------------------     
};

} // end namespace viennamesh

#endif

















