//---------------------------------------------------------------------------//
/*!
 * \file DTK_TopologyTools.hpp
 * \author Stuart R. Slattery
 * \brief TopologyTools declaration.
 */
//---------------------------------------------------------------------------//

#ifndef DTK_TOPOLOGYTOOLS_HPP
#define DTK_TOPOLOGYTOOLS_HPP

#include <MBInterface.hpp>

#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

namespace DataTransferKit
{

namespace TopologyTools
{

// Get the number of linear nodes for a particular iMesh topology.
int numLinearNodes( const moab::EntityType element_topology );

// Point in element query.
bool pointInElement( Teuchos::Array<double>& coords,
		     const moab::EntityHandle element,
		     const Teuchos::RCP<moab::Interface>& moab );

} // end namespace TopologyTools

} // end namepsace DataTransferKit

#endif // end DTK_TOPOLOGYTOOLS_HPP

//---------------------------------------------------------------------------//
// end DTK_TopologyTools.hpp
//---------------------------------------------------------------------------//
