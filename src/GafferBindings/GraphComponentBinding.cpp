#include "boost/python.hpp"
#include "boost/format.hpp"

#include "GafferBindings/GraphComponentBinding.h"
#include "GafferBindings/SignalBinding.h"
#include "Gaffer/GraphComponent.h"

#include "IECorePython/RunTimeTypedBinding.h"

using namespace boost::python;
using namespace GafferBindings;
using namespace Gaffer;

static boost::python::tuple children( GraphComponent &c )
{
	const GraphComponent::ChildContainer &ch = c.children();
	boost::python::list l;
	for( GraphComponent::ChildContainer::const_iterator it=ch.begin(); it!=ch.end(); it++ )
	{
		l.append( *it );
	}
	return boost::python::tuple( l );
}

/// \todo Document the different semantics of addChild and setItem in a scripting
/// reference somewhere.
static void setItem( GraphComponent &g, const char *n, GraphComponentPtr c )
{
	GraphComponentPtr existingChild = g.getChild<GraphComponent>( n );
	if( existingChild )
	{
		g.removeChild( existingChild );
	}
	
	c->setName( n );
	g.addChild( c );
}

static GraphComponentPtr getItem( GraphComponent &g, const char *n )
{
	GraphComponentPtr c = g.getChild<GraphComponent>( n );
	if( c )
	{
		return c;
	}
	
	PyErr_SetString( PyExc_KeyError, n );
	throw_error_already_set();
	return 0; // shouldn't get here
}

static void delItem( GraphComponent &g, const char *n )
{
	GraphComponentPtr c = g.getChild<GraphComponent>( n );
	if( c )
	{
		g.removeChild( c );
		return;
	}
	
	PyErr_SetString( PyExc_KeyError, n );
	throw_error_already_set();
}

static bool contains( GraphComponent &g, const char *n )
{
	return g.getChild<GraphComponent>( n );
}

static GraphComponentPtr parent( GraphComponent &g )
{
	return g.parent<GraphComponent>();
}

static GraphComponentPtr ancestor( GraphComponent &g, IECore::TypeId t )
{
	return g.ancestor( t );
}

struct UnarySlotCaller
{
	boost::signals::detail::unusable operator()( boost::python::object slot, GraphComponentPtr g )
	{
		try
		{
			slot( g );
		}
		catch( const error_already_set &e )
		{
			PyErr_PrintEx( 0 ); // clears the error status
		}
		return boost::signals::detail::unusable();
	}
};

struct BinarySlotCaller
{

	boost::signals::detail::unusable operator()( boost::python::object slot, GraphComponentPtr g, GraphComponentPtr gg )
	{
		try
		{
			slot( g, gg );
		}
		catch( const error_already_set &e )
		{
			PyErr_PrintEx( 0 ); // clears the error status
		}
		return boost::signals::detail::unusable();
	}
};

void GafferBindings::bindGraphComponent()
{

	scope s = IECorePython::RunTimeTypedClass<GraphComponent>()
		.def( init<>() )
		.def( init<const std::string &>() )
		.def( "setName", &GraphComponent::setName, return_value_policy<copy_const_reference>() )
		.def( "getName", &GraphComponent::getName, return_value_policy<copy_const_reference>() )
		.def( "fullName", &GraphComponent::fullName )
		.def( "relativeName", &GraphComponent::relativeName )
		.def( "nameChangedSignal", &GraphComponent::nameChangedSignal, return_internal_reference<1>() )
		.def( "acceptsChild", &GraphComponent::acceptsChild )
		.def( "acceptsParent", &GraphComponent::acceptsParent )
		.def( "addChild", &GraphComponent::addChild )
		.def( "removeChild", &GraphComponent::removeChild )
		.def( "getChild", (GraphComponentPtr (GraphComponent::*)( const std::string & ))&GraphComponent::getChild<GraphComponent> )
		.def( "__getitem__", getItem )
		.def( "__setitem__", setItem )
		.def( "__delitem__", delItem )
		.def( "__contains__", contains )
		.def( "children", &children )
		.def( "parent", &parent )
		.def( "ancestor", &ancestor )
		.def( "commonAncestor", (GraphComponentPtr (GraphComponent::*)( ConstGraphComponentPtr, IECore::TypeId ))&GraphComponent::commonAncestor )
		.def( "isAncestorOf", &GraphComponent::isAncestorOf )
		.def( "childAddedSignal", &GraphComponent::childAddedSignal, return_internal_reference<1>() )
		.def( "childRemovedSignal", &GraphComponent::childRemovedSignal, return_internal_reference<1>() )
		.def( "parentChangedSignal", &GraphComponent::parentChangedSignal, return_internal_reference<1>() )
	;
	
	SignalBinder<GraphComponent::UnarySignal, DefaultSignalCaller<GraphComponent::UnarySignal>, UnarySlotCaller>::bind( "UnarySignal" );
	SignalBinder<GraphComponent::BinarySignal, DefaultSignalCaller<GraphComponent::BinarySignal>, BinarySlotCaller>::bind( "BinarySignal" );
		
}
