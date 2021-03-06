#ifndef VIENNAMESH_ALGORITHM_MESH_HEALING_MERGE_CLOSE_POINTS_HPP
#define VIENNAMESH_ALGORITHM_MESH_HEALING_MERGE_CLOSE_POINTS_HPP

/* ============================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                ViennaMesh - The Vienna Meshing Framework
                            -----------------

                    http://viennamesh.sourceforge.net/

   License:         MIT (X11), see file LICENSE in the base directory
=============================================================================== */

#include "viennameshpp/plugin.hpp"

namespace viennamesh
{
  class merge_close_points : public plugin_algorithm
  {
  public:
    merge_close_points();

    static std::string name();
    bool run(viennamesh::algorithm_handle &);
  };
}

#endif
