#include "viennamesh/algorithm/viennagrid.hpp"
#include "viennamesh/algorithm/io.hpp"


int main()
{
  // creating an algorithm for reading a mesh from a file
  viennamesh::algorithm_handle reader( new viennamesh::io::mesh_reader() );

  // creating a hull extraction algorithm
  viennamesh::algorithm_handle extract_hull( new viennamesh::extract_hull::algorithm() );
  viennamesh::algorithm_handle linear_transform( new viennamesh::linear_transform::algorithm() );

  // creating an algorithm for writing a mesh to a file
  viennamesh::algorithm_handle writer( new viennamesh::io::mesh_writer() );


  // linking the output from the reader to the mesher
  extract_hull->link_input( "default", reader, "default" );
  linear_transform->link_input( "default", extract_hull, "default" );
  writer->link_input( "default", linear_transform, "default" );


  // Setting the filename for the reader and writer
  reader->set_input( "filename", "/export/florian/work/projects/2013_11 ViennaSHE Yannick/mesh/ridiculously_fine_ortho_for_florian_out.devbz.vtu_main.pvd" );

  std::vector<double> matrix(3*2, 0);
  matrix[0*3+0] = 1;
  matrix[1*3+1] = 1;
  linear_transform->set_input( "matrix", matrix );

  writer->set_input( "filename", "nld_mosfet_lines.vtu" );

  // start the algorithms
  reader->run();
  extract_hull->run();
  linear_transform->run();
  writer->run();


}
