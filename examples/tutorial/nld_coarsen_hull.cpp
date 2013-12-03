#include <sstream>

#include "viennamesh/algorithm/viennagrid.hpp"
#include "viennamesh/algorithm/io.hpp"


int main( int argc, char** argv )
{
  if (argc != 7)
  {
    std::cout << "Usage: nld_mesh_quad_hull <input_line_mesh> <output_line_mesh> <num_iterations> <max_angle> <lambda> <max_distance>" << std::endl;
    return -1;
  }


  int num_iterations = atoi(argv[3]);
  double max_angle = atof(argv[4]);
  double lambda = atof(argv[5]);
  double max_distance = atof(argv[6]);

  viennamesh::info(1) << "Using num_iterations: " << num_iterations << std::endl;
  viennamesh::info(1) << "Using max_angle: " << max_angle << std::endl;
  viennamesh::info(1) << "Using lambda: " << lambda << std::endl;
  viennamesh::info(1) << "Using max_distance: " << max_distance << std::endl;

  std::string output_filename = argv[2];
  if (output_filename.rfind(".") != std::string::npos)
    output_filename = output_filename.substr( 0, output_filename.rfind(".") );


  // creating an algorithm for reading a mesh from a file
  viennamesh::algorithm_handle reader( new viennamesh::io::mesh_reader() );
  viennamesh::algorithm_handle coarsen_hull( new viennamesh::line_coarsening::algorithm() );
  viennamesh::algorithm_handle laplace_smooth( new viennamesh::laplace_smooth::algorithm() );
  viennamesh::algorithm_handle writer( new viennamesh::io::mesh_writer() );


  // linking the output from the reader to the mesher
//   coarsen_hull->link_input( "default", reader, "default" );
  laplace_smooth->link_input( "default", coarsen_hull, "default" );
  writer->link_input( "default", coarsen_hull, "default" );


  coarsen_hull->set_input( "max_angle", max_angle ); // 3.1

  laplace_smooth->set_input( "lambda", lambda ); // 0.75
  laplace_smooth->set_input( "max_distance", max_distance ); // 3e-8



  // Setting the filename for the reader and writer
  reader->set_input( "filename", std::string(argv[1]) );


  // start the algorithms
  reader->run();

  coarsen_hull->set_input( "default", reader->get_output("default") );
  coarsen_hull->run();

  coarsen_hull->link_input( "default", laplace_smooth, "default" );

  for (int i = 0; i < num_iterations; ++i)
  {
    std::stringstream ss;
    ss << output_filename << i << ".vtu";

    laplace_smooth->run();
    coarsen_hull->run();

    writer->set_input( "filename", ss.str() );
    writer->run();
  }
}