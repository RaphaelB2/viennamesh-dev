#ifndef VIENNAMESH_ALGORITHM_FILE_WRITER_HPP
#define VIENNAMESH_ALGORITHM_FILE_WRITER_HPP

#include "viennamesh/core/dynamic_algorithm.hpp"

#include "viennagrid/config/default_configs.hpp"
#include "viennagrid/io/vtk_writer.hpp"


namespace viennamesh
{
  template<typename MeshT, typename SegmentationT>
  bool writeToFile( ConstParameterHandle const & mesh, string const & filename )
  {
    typedef MeshWrapper<MeshT, SegmentationT> WrappedMeshType;
    typename result_of::const_parameter_handle<WrappedMeshType>::type tmp = dynamic_handle_cast<const WrappedMeshType>( mesh );
    if (!tmp)
      tmp = mesh->get_converted<WrappedMeshType>();

    if (!tmp)
      return false;

    info(5) << "Found conversion to ViennaGrid mesh." << std::endl;

    string extension = filename.substr( filename.rfind(".")+1 );

    if (extension == "vtu" || extension == "pvd")
    {
      info(5) << "Found .vtu/.pvd extension, using ViennaGrid VTK Writer" << std::endl;
      viennagrid::io::vtk_writer<MeshT, SegmentationT> vtk_writer;
      vtk_writer( tmp->value.mesh, tmp->value.segmentation, filename.substr(0, filename.rfind(".")) );
      return true;
    }

    error(1) << "Unsupported extension: " << extension << std::endl;

    return false;
  }



  class FileWriter : public BaseAlgorithm
  {
  public:

    bool run_impl()
    {
      LoggingStack stack( "Algoritm: FileWriter" );

      ConstParameterHandle mesh = inputs.get("default");
      if (!mesh)
      {
        error(1) << "Input Parameter 'default' (type: mesh) is missing" << std::endl;
        return false;
      }

      ConstStringParameterHandle filename = inputs.get<string>("filename");
      if (!filename)
      {
        error(1) << "Input Parameter 'filename' (type: string) is missing" << std::endl;
        return false;
      }

      if (writeToFile<viennagrid::triangular_3d_mesh, viennagrid::triangular_3d_segmentation>(mesh, filename->value))
        return true;

      if (writeToFile<viennagrid::tetrahedral_3d_mesh, viennagrid::tetrahedral_3d_segmentation>(mesh, filename->value))
        return true;

      error(1) << "Input mesh is not convertable to any supported ViennaGrid mesh." << std::endl;

      return false;
    }

  private:

  };



}



#endif
