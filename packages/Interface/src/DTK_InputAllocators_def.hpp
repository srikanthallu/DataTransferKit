/****************************************************************************
 * Copyright (c) 2012-2017 by the DataTransferKit authors                   *
 * All rights reserved.                                                     *
 *                                                                          *
 * This file is part of the DataTransferKit library. DataTransferKit is     *
 * distributed under a BSD 3-clause license. For the licensing terms see    *
 * the LICENSE file in the top-level directory.                             *
 ****************************************************************************/
/*!
 * \file DTK_InputAllocators_def.hpp
 * \brief Allocators for user input data.
 */
//---------------------------------------------------------------------------//

#ifndef DTK_INPUTALLOCATORS_DEF_HPP
#define DTK_INPUTALLOCATORS_DEF_HPP

#include <Kokkos_Core.hpp>

namespace DataTransferKit
{
//---------------------------------------------------------------------------//
// Allocate a node list.
template <class... ViewProperties>
NodeList<ViewProperties...>
InputAllocators<ViewProperties...>::allocateNodeList(
    const unsigned space_dim, const size_t local_num_nodes,
    const bool has_ghosts )
{
    NodeList<ViewProperties...> node_list;

    node_list.coordinates = Kokkos::View<Coordinate **, ViewProperties...>(
        "coordinates", local_num_nodes, space_dim );

    if ( has_ghosts )
    {
        node_list.is_ghost_node = Kokkos::View<bool *, ViewProperties...>(
            "is_ghost_node", local_num_nodes );
    }

    return node_list;
}

//---------------------------------------------------------------------------//
// Allocate a bounding volume list.
template <class... ViewProperties>
BoundingVolumeList<ViewProperties...>
InputAllocators<ViewProperties...>::allocateBoundingVolumeList(
    const unsigned space_dim, const size_t local_num_volumes,
    const bool has_ghosts )
{
    BoundingVolumeList<ViewProperties...> bv_list;

    bv_list.bounding_volumes =
        Kokkos::View<Coordinate * * [2], ViewProperties...>(
            "bounding_volumes", local_num_volumes, space_dim, 2 );

    if ( has_ghosts )
    {
        bv_list.is_ghost_volume = Kokkos::View<bool *, ViewProperties...>(
            "is_ghost_volume", local_num_volumes );
    }

    return bv_list;
}

//---------------------------------------------------------------------------//
// Allocate a polyhedron list.
template <class... ViewProperties>
PolyhedronList<ViewProperties...>
InputAllocators<ViewProperties...>::allocatePolyhedronList(
    const unsigned space_dim, const size_t local_num_nodes,
    const size_t local_num_faces, const size_t total_nodes_per_face,
    const size_t local_num_cells, const size_t total_faces_per_cell,
    const bool has_ghosts )
{
    PolyhedronList<ViewProperties...> poly_list;

    poly_list.coordinates = Kokkos::View<Coordinate **, ViewProperties...>(
        "coordinates", local_num_nodes, space_dim );

    poly_list.faces = Kokkos::View<LocalOrdinal *, ViewProperties...>(
        "faces", total_nodes_per_face );

    poly_list.nodes_per_face = Kokkos::View<unsigned *, ViewProperties...>(
        "nodes_per_face", local_num_faces );

    poly_list.cells = Kokkos::View<LocalOrdinal *, ViewProperties...>(
        "cells", total_faces_per_cell );

    poly_list.faces_per_cell = Kokkos::View<unsigned *, ViewProperties...>(
        "faces_per_cell", local_num_cells );

    poly_list.face_orientation = Kokkos::View<int *, ViewProperties...>(
        "face_orientation", total_faces_per_cell );

    if ( has_ghosts )
    {
        poly_list.is_ghost_cell = Kokkos::View<bool *, ViewProperties...>(
            "is_ghost_cell", local_num_cells );
    }

    return poly_list;
}

//---------------------------------------------------------------------------//
// Allocate a cell list of cells with the same topology.
template <class... ViewProperties>
CellList<ViewProperties...>
InputAllocators<ViewProperties...>::allocateCellList(
    const unsigned space_dim, const size_t local_num_nodes,
    const size_t local_num_cells, const unsigned nodes_per_cell,
    const bool has_ghosts )
{
    CellList<ViewProperties...> cell_list;

    cell_list.coordinates = Kokkos::View<Coordinate **, ViewProperties...>(
        "coordinates", local_num_nodes, space_dim );

    cell_list.cells = Kokkos::View<LocalOrdinal **, ViewProperties...>(
        "cells", local_num_cells, nodes_per_cell );

    if ( has_ghosts )
    {
        cell_list.is_ghost_cell = Kokkos::View<bool *, ViewProperties...>(
            "is_ghost_cell", local_num_cells );
    }

    return cell_list;
}

//---------------------------------------------------------------------------//
// Allocate a cell list from cells with different topologies.
template <class... ViewProperties>
CellList<ViewProperties...>
InputAllocators<ViewProperties...>::allocateMixedTopologyCellList(
    const unsigned space_dim, const size_t local_num_nodes,
    const size_t local_num_cells, const size_t total_nodes_per_cell,
    const bool has_ghosts )
{
    CellList<ViewProperties...> cell_list;

    cell_list.coordinates = Kokkos::View<Coordinate **, ViewProperties...>(
        "coordinates", local_num_nodes, space_dim );

    cell_list.cells = Kokkos::View<LocalOrdinal *, ViewProperties...>(
        "cells", total_nodes_per_cell );

    cell_list.cell_topology_ids = Kokkos::View<unsigned *, ViewProperties...>(
        "cell_topology_ids", local_num_cells );

    if ( has_ghosts )
    {
        cell_list.is_ghost_cell = Kokkos::View<bool *, ViewProperties...>(
            "is_ghost_cell", local_num_cells );
    }

    return cell_list;
}

//---------------------------------------------------------------------------//
// Allocate a boundary.
template <class... ViewProperties>
template <class ListType>
void InputAllocators<ViewProperties...>::allocateBoundary(
    const size_t local_num_faces, ListType &list )
{
    list.boundary_cells = Kokkos::View<LocalOrdinal *, ViewProperties...>(
        "boundary_cells", local_num_faces );

    list.cell_faces_on_boundary = Kokkos::View<unsigned *, ViewProperties...>(
        "cell_faces_on_boundary", local_num_faces );
}

//---------------------------------------------------------------------------//
// Allocate a degree-of-freedom id Map for objects that all have the same
// number of degrees of freedom.
template <class... ViewProperties>
DOFMap<ViewProperties...> InputAllocators<ViewProperties...>::allocateDOFMap(
    const size_t local_num_dofs, const size_t local_num_objects,
    const unsigned dofs_per_object )
{
    DOFMap<ViewProperties...> dof_id_map;

    dof_id_map.global_dof_ids =
        Kokkos::View<GlobalOrdinal *, ViewProperties...>( "global_dof_ids",
                                                          local_num_dofs );

    dof_id_map.object_dof_ids =
        Kokkos::View<LocalOrdinal **, ViewProperties...>(
            "object_dof_ids", local_num_objects, dofs_per_object );

    return dof_id_map;
}

//---------------------------------------------------------------------------//
// Allocate a degree-of-freedom id Map for objects that have the
// different numbers of degrees of freedom.
template <class... ViewProperties>
DOFMap<ViewProperties...>
InputAllocators<ViewProperties...>::allocateMixedTopologyDOFMap(
    const size_t local_num_dofs, const size_t local_num_objects,
    const size_t total_dofs_per_object )
{
    DOFMap<ViewProperties...> dof_id_map;

    dof_id_map.global_dof_ids =
        Kokkos::View<GlobalOrdinal *, ViewProperties...>( "global_dof_ids",
                                                          local_num_dofs );

    dof_id_map.object_dof_ids = Kokkos::View<LocalOrdinal *, ViewProperties...>(
        "object_dof_ids", total_dofs_per_object );

    dof_id_map.dofs_per_object = Kokkos::View<unsigned *, ViewProperties...>(
        "dofs_per_object", local_num_objects );

    return dof_id_map;
}

//---------------------------------------------------------------------------//
// Allocate a field.
template <class... ViewProperties>
template <class Scalar>
Field<Scalar, ViewProperties...>
InputAllocators<ViewProperties...>::allocateField(
    const size_t local_num_dofs, const unsigned field_dimension )
{
    Field<Scalar, ViewProperties...> field;

    field.dofs = Kokkos::View<Scalar **, ViewProperties...>(
        "dofs", local_num_dofs, field_dimension );

    return field;
}

//---------------------------------------------------------------------------//
// Allocate an evaluation set.
template <class... ViewProperties>
EvaluationSet<ViewProperties...>
InputAllocators<ViewProperties...>::allocateEvaluationSet(
    const size_t local_num_evals, const unsigned space_dim )
{
    EvaluationSet<ViewProperties...> eval_set;

    eval_set.evaluation_points = Kokkos::View<Coordinate **, ViewProperties...>(
        "evaluation_points", local_num_evals, space_dim );

    eval_set.object_ids = Kokkos::View<LocalOrdinal *, ViewProperties...>(
        "object_ids", local_num_evals );

    return eval_set;
}

//---------------------------------------------------------------------------//

} // end namespace DataTransferKit

//---------------------------------------------------------------------------//

#endif // end DTK_INPUTALLOCATORS_DEF_HPP

//---------------------------------------------------------------------------//
// end DTK_InputAllocators.hpp
//---------------------------------------------------------------------------//
