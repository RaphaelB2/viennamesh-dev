#ifndef VIENNAMESH_ALGORITHM_VGMODELER_ADAPT_HULL_HPP
#define VIENNAMESH_ALGORITHM_VGMODELER_ADAPT_HULL_HPP

#include "viennamesh/core/algorithm.hpp"
#include "viennamesh/algorithm/triangle/triangle_mesh.hpp"

namespace viennamesh
{
  namespace vgmodeler
  {
    class adapt_hull : public base_algorithm
    {
    public:
      adapt_hull();

      string name() const;
      string id() const;

      bool run_impl();

    private:
      dynamic_required_input_parameter_interface      input_mesh;
      optional_input_parameter_interface<double>      cell_size;

      output_parameter_interface                      output_mesh;
    };
  }
}

#endif