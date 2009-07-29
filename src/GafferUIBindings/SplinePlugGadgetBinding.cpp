#include "boost/python.hpp"

#include "GafferUIBindings/SplinePlugGadgetBinding.h"
#include "GafferUI/SplinePlugGadget.h"

#include "IECore/bindings/RunTimeTypedBinding.h"

using namespace boost::python;
using namespace GafferUIBindings;
using namespace GafferUI;

void GafferUIBindings::bindSplinePlugGadget()
{
	IECore::RunTimeTypedClass<SplinePlugGadget>()
		.def( init<>() )
		.def( "splines", (Gaffer::PlugSetPtr (SplinePlugGadget::*)())&SplinePlugGadget::splines )
		.def( "selection", (Gaffer::PlugSetPtr (SplinePlugGadget::*)())&SplinePlugGadget::selection )
	;
}