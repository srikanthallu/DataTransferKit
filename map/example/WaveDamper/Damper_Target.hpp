#ifndef damper_target_hpp
#define damper_target_hpp

#include <algorithm>
#include <vector>

#include "Damper.hpp"

#include <DataTransferKit_Point.hpp>
#include <DataTransferKit_DataTarget.hpp>

#include "Teuchos_RCP.hpp"
#include "Teuchos_ArrayView.hpp"
#include "Teuchos_ArrayRCP.hpp"
#include "Teuchos_DefaultComm.hpp"

//---------------------------------------------------------------------------//
namespace DataTransferKit {

// DataTarget interface implementation for the Damper code.
template<class DataType, class HandleType, class CoordinateType, int DIM>
class Damper_DataTarget 
    : public DataTarget<DataType, HandleType, CoordinateType,DIM>
{
  public:

    typedef int                                      OrdinalType;
    typedef Point<1,HandleType,CoordinateType>       PointType;
    typedef Teuchos::Comm<OrdinalType>               Communicator_t;
    typedef Teuchos::RCP<const Communicator_t>       RCP_Communicator;
    typedef Teuchos::RCP<Damper>                     RCP_Damper;

  private:

    RCP_Damper damper;
    std::vector<PointType> local_points;

  public:

    Damper_DataTarget(RCP_Damper _damper)
	: damper(_damper)
    { /* ... */ }

    ~Damper_DataTarget()
    { /* ... */ }

    RCP_Communicator get_target_comm()
    {
	return damper->get_comm();
    }

    bool is_field_supported(const std::string &field_name)
    {
	bool return_val = false;

	if (field_name == "WAVE_TARGET_FIELD")
	{
	    return_val = true;
	}

	return return_val;
    }

    const Teuchos::ArrayRCP<PointType> 
    get_target_points(const std::string &field_name)
    {
	Teuchos::ArrayRCP<PointType> return_view;

	if ( field_name == "WAVE_TARGET_FIELD" )
	{
	    local_points.clear();
	    Teuchos::ArrayView<const DataType> local_grid( damper->get_grid() );
	    typename Teuchos::ArrayView<DataType>::const_iterator grid_it;
	    int n = 0;
	    int global_handle;
	    for (grid_it = local_grid.begin(); 
		 grid_it != local_grid.end();
		 ++grid_it, ++n)
	    {
		global_handle = damper->get_comm()->getRank() *
				local_grid.size() + n;
		local_points.push_back( 
		    point( global_handle, *grid_it) );
	    }
	    return_view = Teuchos::arcp<PointType>(
		&local_points[0], 0, (int) local_points.size(), false );
	}

	return return_view;
    }

    Teuchos::ArrayRCP<DataType> 
    get_target_data_space(const std::string &field_name)
    {
	Teuchos::ArrayRCP<DataType> return_view;

	if ( field_name == "WAVE_TARGET_FIELD" )
	{
	    return_view = Teuchos::arcp<DataType>( 
		&damper->set_wave_data()[0], 0, 
		(int) damper->set_wave_data().size(), false );
	}

	return return_view;
    }

    void set_global_target_data(const std::string &field_name,
				const DataType &data)
    { /* ... */ }
};

//---------------------------------------------------------------------------//

} // end namespace DataTransferKit

#endif // end damper_target_hpp