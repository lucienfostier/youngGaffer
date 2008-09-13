#include "boost/python.hpp"

#include "GafferUIBindings/NodeGadgetBinding.h"
#include "GafferUI/NodeGadget.h"
#include "GafferUI/Nodule.h"

#include "IECore/bindings/IntrusivePtrPatch.h"
#include "IECore/bindings/RunTimeTypedBinding.h"

using namespace boost::python;
using namespace GafferUIBindings;
using namespace GafferUI;

void GafferUIBindings::bindNodeGadget()
{
	typedef class_<NodeGadget, NodeGadgetPtr, boost::noncopyable, bases<IndividualContainer> > NodeGadgetPyClass;

	NodeGadgetPyClass( "NodeGadget", init<Gaffer::NodePtr>() )
		.IE_COREPYTHON_DEFRUNTIMETYPEDSTATICMETHODS( NodeGadget )
		.def( "node", (Gaffer::NodePtr (NodeGadget::*)())&NodeGadget::node )
		.def( "nodule", (NodulePtr (NodeGadget::*)( Gaffer::ConstPlugPtr ))&NodeGadget::nodule )
	;
		
	INTRUSIVE_PTR_PATCH( NodeGadget, NodeGadgetPyClass );
	
	implicitly_convertible<NodeGadgetPtr, GadgetPtr>();
	implicitly_convertible<NodeGadgetPtr, ConstNodeGadgetPtr>();

}
