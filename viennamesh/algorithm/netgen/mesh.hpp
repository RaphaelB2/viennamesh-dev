#ifndef VIENNAMESH_ALGORITHM_NETGEN_MESH_HPP
#define VIENNAMESH_ALGORITHM_NETGEN_MESH_HPP

#include "netgen/libsrc/csg/csg.hpp"
namespace netgen
{
  extern CSGeometry * ParseCSG (istream & istr);
}




namespace viennamesh
{
  namespace netgen
  {

//     struct geometry
//     {
//       geometry() : geo(NULL) {}
//       ~geometry() { delete geo; }
//
//       netgen::CSGeometry * geo;
//     };


    struct output_mesh
    {
      output_mesh() : mesh( new ::netgen::Mesh() ) {}
      ~output_mesh() { delete mesh; }

      ::netgen::Mesh * mesh;
    };


    static bool convert(netgen::output_mesh const & input, viennagrid::tetrahedral_3d_mesh & output)
    {
      typedef viennagrid::tetrahedral_3d_mesh ViennaGridMeshType;
      typedef viennagrid::result_of::point<ViennaGridMeshType>::type PointType;
      typedef viennagrid::result_of::vertex_handle<ViennaGridMeshType>::type VertexHandleType;
//       typedef SegmentationType::segment_handle_type SegmentType;


      int num_points = input.mesh->GetNP();
      int num_tets = input.mesh->GetNE();

      std::cout << "Num Points: " << num_points << std::endl;
      std::cout << "Num Tets: " << num_tets << std::endl;

      std::vector<VertexHandleType> vertex_handles( num_points );

      for (int i = 1; i <= num_points; ++i)
      {
        PointType vgrid_point(input.mesh->Point(i)[0], input.mesh->Point(i)[1], input.mesh->Point(i)[2]);
        vertex_handles[i-1] = viennagrid::make_vertex( output, vgrid_point );
      }


      for (int i = 0; i < num_tets; ++i)
      {
          ::netgen::ElementIndex ei = i;
//           SegmentType segment = segmentation.get_make_segment( (*input)[ei].GetIndex() );
          viennagrid::make_tetrahedron( output, vertex_handles[(*input.mesh)[ei][0]-1], vertex_handles[(*input.mesh)[ei][1]-1],
                vertex_handles[(*input.mesh)[ei][2]-1], vertex_handles[(*input.mesh)[ei][3]-1]);
      }

      return true;
    }




    static bool convert(netgen::output_mesh const & input, viennagrid::segmented_mesh<viennagrid::tetrahedral_3d_mesh, viennagrid::tetrahedral_3d_segmentation> & output)
    {
      typedef viennagrid::tetrahedral_3d_mesh ViennaGridMeshType;
      typedef viennagrid::tetrahedral_3d_segmentation ViennaGridSegmentationType;
      typedef viennagrid::result_of::point<ViennaGridMeshType>::type PointType;
      typedef viennagrid::result_of::vertex_handle<ViennaGridMeshType>::type VertexHandleType;
      typedef ViennaGridSegmentationType::segment_handle_type ViennaGridSegmentType;


      int num_points = input.mesh->GetNP();
      int num_tets = input.mesh->GetNE();

      std::cout << "Num Points: " << num_points << std::endl;
      std::cout << "Num Tets: " << num_tets << std::endl;

      std::vector<VertexHandleType> vertex_handles( num_points );

      for (int i = 1; i <= num_points; ++i)
      {
        PointType vgrid_point(input.mesh->Point(i)[0], input.mesh->Point(i)[1], input.mesh->Point(i)[2]);
        vertex_handles[i-1] = viennagrid::make_vertex( output.mesh, vgrid_point );
      }


      for (int i = 0; i < num_tets; ++i)
      {
          ::netgen::ElementIndex ei = i;
          ViennaGridSegmentType segment = output.segmentation.get_make_segment( (*input.mesh)[ei].GetIndex() );
          viennagrid::make_tetrahedron( segment, vertex_handles[(*input.mesh)[ei][0]-1], vertex_handles[(*input.mesh)[ei][1]-1],
                vertex_handles[(*input.mesh)[ei][2]-1], vertex_handles[(*input.mesh)[ei][3]-1]);
      }

      return true;
    }


  }


  template<>
  struct static_init_impl< netgen::output_mesh >
  {
    typedef netgen::output_mesh SelfType;

    static void init()
    {
      typedef viennagrid::tetrahedral_3d_mesh Tetrahedral3DViennaGridMeshType;
      typedef viennagrid::segmented_mesh<viennagrid::tetrahedral_3d_mesh, viennagrid::tetrahedral_3d_segmentation> SegmentedTetrahedral3DViennaGridMeshType;

      converter::get().register_conversion<SelfType, Tetrahedral3DViennaGridMeshType>( &netgen::convert );
      converter::get().register_conversion<SelfType, SegmentedTetrahedral3DViennaGridMeshType>( &netgen::convert );

      type_properties::get().set_property<SelfType>( "is_mesh", "true" );
      type_properties::get().set_property<SelfType>( "geometric_dimension", "3" );
      type_properties::get().set_property<SelfType>( "cell_type", "tetrahedron" );
    }
  };


}

#endif