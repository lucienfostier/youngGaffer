#include "IECore/Exception.h"

#include "Gaffer/ScriptNode.h"
#include "Gaffer/TypedPlug.h"
#include "Gaffer/Action.h"

using namespace Gaffer;

GAFFER_DECLARECONTAINERSPECIALISATIONS( ScriptContainer, ScriptContainerTypeId )

ScriptNode::ScriptNode( const std::string &name )
	:	Node( name ), m_selection( new NodeSet ), m_undoIterator( m_undoList.end() )
{
	m_fileNamePlug = new StringPlug( "fileName", Plug::In, "" );
	addChild( m_fileNamePlug );
}

ScriptNode::~ScriptNode()
{
}

bool ScriptNode::acceptsParent( const GraphComponent *potentialParent ) const
{
	return potentialParent->isInstanceOf( ScriptContainer::staticTypeId() );
}

NodeSetPtr ScriptNode::selection()
{
	return m_selection;
}

ConstNodeSetPtr ScriptNode::selection() const
{
	return m_selection;
}

void ScriptNode::undo()
{
	if( m_undoIterator==m_undoList.begin() )
	{
		throw IECore::Exception( "Nothing to undo" );
	}
	m_undoIterator--;
	for( ActionVector::reverse_iterator it=(*m_undoIterator)->rbegin(); it!=(*m_undoIterator)->rend(); it++ )
	{
		(*it)->undoAction();
	}
}

void ScriptNode::redo()
{
	if( m_undoIterator==m_undoList.end() )
	{
		throw IECore::Exception( "Nothing to redo" );
	}
	for( ActionVector::iterator it=(*m_undoIterator)->begin(); it!=(*m_undoIterator)->end(); it++ )
	{
		(*it)->doAction();
	}
	m_undoIterator++;
}

void ScriptNode::deleteNode( NodePtr child )
{
	if( child->ancestor<ScriptNode>() != this )
	{
		throw IECore::Exception( "Node is not a child of script." );
	}

	for( InputPlugIterator it=child->inputPlugsBegin(); it!=child->inputPlugsEnd(); it++ )
	{
		(*it)->setInput( 0 );
	}
	
	for( OutputPlugIterator it=child->outputPlugsBegin(); it!=child->outputPlugsEnd(); it++ )
	{
		(*it)->removeOutputs();
	}
	
	selection()->remove( child );
	child->parent<GraphComponent>()->removeChild( child );
}

StringPlugPtr ScriptNode::fileNamePlug()
{
	return m_fileNamePlug;
}

ConstStringPlugPtr ScriptNode::fileNamePlug() const
{
	return m_fileNamePlug;
}
	
void ScriptNode::dirty( ConstPlugPtr dirty ) const
{
}

void ScriptNode::compute( PlugPtr output ) const
{
	assert( 0 );
}

void ScriptNode::execute( const std::string &pythonScript )
{
	throw IECore::Exception( "Cannot execute scripts on a ScriptNode not created in Python." );
}

ScriptNode::ScriptExecutedSignal &ScriptNode::scriptExecutedSignal()
{
	return m_scriptExecutedSignal;
}

PyObject *ScriptNode::evaluate( const std::string &pythonExpression )
{
	throw IECore::Exception( "Cannot execute scripts on a ScriptNode not created in Python." );
}

ScriptNode::ScriptEvaluatedSignal &ScriptNode::scriptEvaluatedSignal()
{
	return m_scriptEvaluatedSignal;
}

std::string ScriptNode::serialise( ConstNodeSetPtr filter ) const
{
	throw IECore::Exception( "Cannot serialise scripts on a ScriptNode not created in Python." );
}

void ScriptNode::load()
{
	throw IECore::Exception( "Cannot load scripts on a ScriptNode not created in Python." );
}

void ScriptNode::save() const
{
	throw IECore::Exception( "Cannot save scripts on a ScriptNode not created in Python." );
}
