#include "boost/python.hpp"

#include "GafferUIBindings/GadgetBinding.h"
#include "GafferUIBindings/EventBinding.h"
#include "GafferUIBindings/ModifiableEventBinding.h"
#include "GafferUIBindings/KeyEventBinding.h"
#include "GafferUIBindings/ButtonEventBinding.h"
#include "GafferUIBindings/NodeGadgetBinding.h"

using namespace GafferUIBindings;

BOOST_PYTHON_MODULE( _GafferUI )
{

	bindGadget();
	bindEvent();
	bindModifiableEvent();
	bindKeyEvent();
	bindButtonEvent();
	bindNodeGadget();

}