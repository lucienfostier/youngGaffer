#ifndef GAFFER_NODE_H
#define GAFFER_NODE_H

#include "Gaffer/GraphComponent.h"

#include "IECore/Object.h"

namespace Gaffer
{

IE_CORE_FORWARDDECLARE( Plug )
IE_CORE_FORWARDDECLARE( Node )

/// Threading
///
///		- can we allow multiple computes() at once?
///		- or do we have to resort to computes() being threaded internally?
///
/// difference between dynamic and static plugs and children?
///		- flag in plug?
///		- implement as Node::acceptsRemoval()
///			- don't thing plugs need to know their dynamic/static status
///			- but nodes do for serialisation i think
///				- or they do clever addition of plugs during parsing
///
/// difference between input and output plugs?
///		- either in and out CompoundPlug parents
///			- not this because we want to be able just to reference node.plug
///		- or flags in plug
///			- plugs do need to know their own direction - to disallow dirtying of inputs with no input connection
class Node : public GraphComponent
{

	public :

		Node();
		virtual ~Node();

		IE_CORE_DECLARERUNTIMETYPEDEXTENSION( Node, NodeTypeId, GraphComponent );

		typedef boost::signal<void (PlugPtr)> UnaryPlugSignal;
		typedef boost::signal<void (PlugPtr)> BinaryPlugSignal;
		
		/// @name Plug signals
		/// These signals are emitted on events relating to child Plugs
		/// of this Node. They are implemented on the Node rather than
		/// on individual Plugs to limit the proliferation of huge numbers
		/// of signals.
		//////////////////////////////////////////////////////////////
		//@{
		/// Called when the value on a plug of this node is set.
		UnaryPlugSignal &plugSetSignal();
		/// Called when a plug of this node is dirtied.
		UnaryPlugSignal &plugDirtiedSignal();
		/// Called when a plug of this node is connected. First argument
		/// to slots is the source plug and second is the destination.
		BinaryPlugSignal &plugConnectedSignal();
		//@}
		
		/// Accepts only Nodes and Plugs.
		virtual bool acceptsChild( ConstGraphComponentPtr potentialChild ) const;
		/// Accepts only Nodes.
		virtual bool acceptsParent( ConstGraphComponentPtr potentialParent ) const;
		
	protected :
		
		/// Called when an input plug becomes dirty. Must be implemented to dirty any
		/// output plugs which depend on the input.
		virtual void dirty( ConstPlugPtr dirty ) const = 0;
		/// Called when getValue() is called on an output plug which is dirty. Must
		/// be implemented to calculate and return the value for this Plug.
		/// \todo Consider this : if we didn't
		/// have this return ObjectPtr then we could have Plugs storing values in any way -
		/// it would be the Node's responsibility to set the value in any way appropriate.
		virtual IECore::ObjectPtr compute( ConstPlugPtr output ) const = 0;
		
	private :
	
		friend class Plug;
	
		UnaryPlugSignal m_plugSetSignal;
		UnaryPlugSignal m_plugDirtiedSignal;
		BinaryPlugSignal m_plugConnectedSignal;

};

} // namespace Gaffer

#endif // GAFFER_NODE_H
