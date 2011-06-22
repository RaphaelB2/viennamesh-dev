/* =============================================================================
   Copyright (c) 2011, Institute for Microelectronics, TU Wien
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMesh - The Vienna Mesh Generation Framework
                             -----------------

   authors:    Josef Weinbub                         weinbub@iue.tuwien.ac.at


   license:    see file LICENSE in the base directory
============================================================================= */
#ifndef VIENNAMESH_TAGS_HPP
#define VIENNAMESH_TAGS_HPP

namespace viennamesh {
   
namespace tag {
   
struct mesh_kernel {};   
struct wrapper {};
   
struct none      {};
struct triangle  {};
struct tetgen    {};
struct netgen    {};
struct netgen2    {};
struct vgmodeler {};
struct cervpt    {};

struct algorithm {};
struct criteria  {};
struct dim_topo  {};
struct dim_geom  {};
struct cell_type {};
struct size      {};

struct incremental_delaunay {};
struct advancing_front      {};
struct constrained_delaunay {};
struct conforming_delaunay  {};
struct convex               {};
struct minimal              {};
struct one                  {};
struct two                  {};
struct three                {};
struct simplex              {};
struct cuboid               {};

struct consistancy          {};
struct orienter             {};
struct cell_normals         {};
struct hull_quality         {};
}
   
} // end namespace viennamesh

#endif
