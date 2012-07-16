//---------------------------------------------------------------------------//
/*
  Copyright (c) 2012, Stuart R. Slattery
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  *: Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  *: Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  *: Neither the name of the University of Wisconsin - Madison nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
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

//---------------------------------------------------------------------------//
/*!
 * \class TopologyTools
 * \brief Tools based on concrete mesh topologies.
 */ 
//---------------------------------------------------------------------------//
class TopologyTools
{
  public:

    //! Constructor.
    TopologyTools()
    { /* ... */ }

    //! Destructor.
    ~TopologyTools()
    { /* ... */ }

    // Get the number of linear nodes for a particular iMesh topology.
    static int numLinearNodes( const moab::EntityType element_topology );

    // Reorder a list of element nodes from MBCN ordering to Shards ordering.
    static void MBCN2Shards( std::vector<moab::EntityHandle>& element_nodes, 
			     const int num_nodes,
			     const moab::EntityType entity_topology );

    // Point in element query.
    static bool pointInElement( Teuchos::Array<double>& coords,
				const moab::EntityHandle element,
				const Teuchos::RCP<moab::Interface>& moab );
};

} // end namepsace DataTransferKit

#endif // end DTK_TOPOLOGYTOOLS_HPP

//---------------------------------------------------------------------------//
// end DTK_TopologyTools.hpp
//---------------------------------------------------------------------------//
