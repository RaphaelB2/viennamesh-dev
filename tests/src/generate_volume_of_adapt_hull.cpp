/* =============================================================================
   Copyright (c) 2011, Institute for Microelectronics, TU Wien
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMesh - The Vienna Mesh Generation Framework
                             -----------------

   authors:    Josef Weinbub                         weinbub@iue.tuwien.ac.at


   license:    see file LICENSE in the base directory
============================================================================= */

#include <iostream>

#include "viennautils/io/bnd.hpp"
#include "viennautils/io/hin.hpp"
#include "viennautils/file.hpp"

#include "viennagrid/domain.hpp"
#include "viennagrid/algorithm/cell_normals.hpp"

#include "viennamesh/wrapper/hin.hpp"
#include "viennamesh/wrapper/bnd.hpp"
#include "viennamesh/generation/cervpt.hpp"
#include "viennamesh/adaptation/orienter.hpp"
#include "viennamesh/adaptation/hull_quality.hpp"
#include "viennamesh/generation/netgen.hpp"

template<typename WrappedDataT>
int meshing(WrappedDataT& wrapped_data)
{
   typedef viennamesh::result_of::mesh_generator<viennamesh::tag::cervpt>::type        cervpt_hull_mesh_generator_type;
   cervpt_hull_mesh_generator_type        hull_mesher;       

   typedef viennamesh::result_of::mesh_adaptor<viennamesh::tag::orienter>::type        orienter_adaptor_type;
   orienter_adaptor_type                  orienter;
   
   typedef viennamesh::result_of::mesh_adaptor<viennamesh::tag::hull_quality>::type    hull_quality_adaptor_type;
   hull_quality_adaptor_type              hull_quality;                  

   typedef viennamesh::result_of::mesh_generator<viennamesh::tag::netgen>::type        netgen_volume_mesh_generator_type;
   netgen_volume_mesh_generator_type      volume_mesher;      

   volume_mesher(hull_quality(orienter(hull_mesher(wrapped_data))));

   return 0;
}


int process_file(std::string filename)
{
   std::cout << "processing file: " << filename << std::endl;

   std::string input_extension  = viennautils::file_extension(filename);

   if(input_extension == "bnd")
   {
      viennautils::io::bnd_reader my_bnd_reader;
      my_bnd_reader(filename); 

      typedef viennamesh::wrapper<viennamesh::tag::bnd, viennautils::io::bnd_reader>      bnd_wrapper_type;
      bnd_wrapper_type                    wrapped_data(my_bnd_reader);      

      meshing(wrapped_data);
   }
   else
   if(input_extension == "hin")
   {
      viennautils::io::hin_reader my_hin_reader;
      my_hin_reader(filename); 

      typedef viennamesh::wrapper<viennamesh::tag::hin, viennautils::io::hin_reader>      hin_wrapper_type;
      hin_wrapper_type                    wrapped_data(my_hin_reader);      

      meshing(wrapped_data);
   }
   else
   {
      std::cerr << "Error: Fileformat not supported of input file: " << filename << std::endl;
      return -1;
   }
}

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      std::cerr << "## Error::Parameter - usage: " << argv[0] << " inputfile" << std::endl;
      std::cerr << "## shutting down .." << std::endl;
      return -1;
   }
   
   std::string inputfile(argv[1]);
   
   process_file(inputfile);

  
   return 0;
}

