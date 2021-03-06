#include "boost/python.hpp"

#include "GafferUIBindings/LinearContainerBinding.h"
#include "GafferUI/LinearContainer.h"

#include "Gaffer/Node.h"

#include "IECorePython/RunTimeTypedBinding.h"

using namespace boost::python;
using namespace GafferUIBindings;
using namespace GafferUI;

void GafferUIBindings::bindLinearContainer()
{
	/// \todo It would be nice if we could make this behave a lot like the ListContainer
	IECorePython::RunTimeTypedClass<LinearContainer> c;
		c.def( "setOrientation", &LinearContainer::setOrientation )
		.def( "getOrientation", &LinearContainer::getOrientation )
		.def( "setAlignment", &LinearContainer::setAlignment )
		.def( "getAlignment", &LinearContainer::getAlignment )
		.def( "setSpacing", &LinearContainer::setSpacing )
		.def( "getSpacing", &LinearContainer::getSpacing )
	;
	
	scope s = c;
	
	enum_<LinearContainer::Orientation>( "Orientation" )
		.value( "InvalidOrientation", LinearContainer::InvalidOrientation )
		.value( "X", LinearContainer::X )
		.value( "Y", LinearContainer::Y )
		.value( "Z", LinearContainer::Z )
	;
	
	enum_<LinearContainer::Alignment>( "Alignment" )
		.value( "InvalidAlignment", LinearContainer::InvalidAlignment )
		.value( "Min", LinearContainer::Min )
		.value( "Centre", LinearContainer::Centre )
		.value( "Max", LinearContainer::Max )
	;
	
	// we have to define the constructor after the enums, as they must be registered in order for boost::python to figure out the correct
	// python values for the default arguments
	c.def( init< optional<const std::string &, LinearContainer::Orientation, LinearContainer::Alignment, float> >(
			( arg_( "name" )=LinearContainer::staticTypeName(), arg_( "orientation" )=LinearContainer::X, arg_( "alignment" )=LinearContainer::Centre, arg_( "spacing" )=0.0f )
		)
	);

}
