#include "Gaffer/Plug.h"
#include "Gaffer/Node.h"

#include "IECore/Exception.h"

#include "boost/format.hpp"

using namespace Gaffer;

Plug::Plug()
{
}

Plug::~Plug()
{
	setInput( 0, false );
	for( OutputContainer::iterator it=m_outputs.begin(); it!=m_outputs.end(); it++ )
	{
		(*it)->setInput( 0 );
	}
}

bool Plug::acceptsChild( ConstGraphComponentPtr potentialChild ) const
{
	return false;
}

bool Plug::acceptsParent( ConstGraphComponentPtr potentialParent ) const
{
	if( !GraphComponent::acceptsParent( potentialParent ) )
	{
		return false;
	}
	return potentialParent->isInstanceOf( (IECore::TypeId)NodeTypeId );
}

NodePtr Plug::node()
{
	return parent<Node>();
}


ConstNodePtr Plug::node() const
{
	return parent<const Node>();
}
		
bool Plug::acceptsInput( ConstPlugPtr input ) const
{
	return true;
}

void Plug::setInput( PlugPtr input )
{
	setInput( input, true );
}


void Plug::setInput( PlugPtr input, bool emit )
{
	if( input.get()==m_input )
	{
		return;
	}
	if( !acceptsInput( input ) )
	{
		std::string what = boost::str( boost::format( "Plug \"%s\" rejects input \"%s\"." ) % fullName() % input->fullName() );
		throw IECore::Exception( what );
	}
	if( m_input )
	{
		m_input->m_outputs.remove( this );
	}
	m_input = input.get();
	if( m_input )
	{
		m_input->m_outputs.push_back( this );
	}
	if( emit )
	{
		node()->plugInputChangedSignal()( this );
	}
}

const Plug::OutputContainer &Plug::outputs() const
{
	return m_outputs;
}