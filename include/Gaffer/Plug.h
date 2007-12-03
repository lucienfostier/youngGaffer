#ifndef GAFFER_PLUG_H
#define GAFFER_PLUG_H

#include "Gaffer/GraphComponent.h"

#include "IECore/Object.h"

namespace Gaffer
{

IE_CORE_FORWARDDECLARE( Plug )
IE_CORE_FORWARDDECLARE( Node )

/// CompoundPlug mapping onto CompoundParameter? or just ui groupings independent of plugs?
/// ParameterPlug<ParameterType> subclasses.
///
///		- but - if we want connections into the components of vector and color plugs then
///				we'll have to not wrap V3fParameter but instead use a Compound of FloatPlugs
///					-it'd be nice to have getValue() for a V3fPlug return V3fData and not CompoundData though.
///						-what to do?
///		- so - shall we abandon Parameters?
///			 - or have a mapping layer so we can have OpHolderNode?
///			 - or use them where appropriate?
///				- they do implement a lot of useful validation logic already
///
///		- either way we should complete the Plug interface before worrying
///
/// memory usage
///
///		- IntPlug storing IntData rather than int has some overhead.
///		- is this a problem?
///
/// let's not have DoublePlug or DoubleVectorPlug
///		- keep all real types as float
///		- and all integers as int? - except for maybe UIntVectorData?
///
/// CompoundPlug with dynamic addition/removal of plugs? that would be useful for lots of stuff?
/// Cannot dirty an input plug without a connection
///		- and input plugs revert to default (or current value) on disconnect?
/// Expressions
///		- Node? or intrinsic to Plug somehow? do they dirty automatically? or compute each time?
///		- it'd be nice not to have to call IntData::value() just to get values from Plugs in these
/// Memory management
///		- Is this where we flush less often used values into a disk cache? and load 'em again when needed?
///
/// Image plugs with partial computation - how would they work????
class Plug : public GraphComponent
{

	public :
	
		Plug();
		virtual ~Plug();

		IE_CORE_DECLARERUNTIMETYPEDEXTENSION( Plug, PlugTypeId, GraphComponent );

		/// Just returns parent<Node>() as a syntactic convenience.
		NodePtr node();
		/// Just returns parent<Node>() as a syntactic convenience.
		ConstNodePtr node() const;

		/// Do we need this one? How about we make custom setValue( int ) type things on each
		/// Plug?
		bool acceptsInput( IECore::ConstObjectPtr input ) const;
		virtual bool acceptsInput( ConstPlugPtr input, std::string &reason ) const;

		PlugPtr input();
		ConstPlugPtr input() const;
		const std::vector<const Plug *> outputs() const;
		
		/// does all this value stuff belong in a ValuePlug base class????
		bool acceptsValue( IECore::ConstObjectPtr value ) const;
		virtual bool acceptsValue( IECore::ConstObjectPtr value, std::string &reason ) const;
		/// Propagates through connections and triggers dirty(). is a copy taken? - if yes
		/// then IntPlug can store int? Throws an Exception if an output plug.
		void setValue();
		/// Triggers compute if needed. I don't think you can ever have non-const access
		/// to the value either - this could allow IntPlug to store int rather than IntData
		IECore::ConstObjectPtr getValue() const;
		bool isDirty() const;
		
		/// Accepts no children.
		virtual bool acceptsChild( ConstGraphComponentPtr potentialChild ) const;
		/// Accepts only Nodes or Plugs as a parent.
		virtual bool acceptsParent( ConstGraphComponentPtr potentialParent ) const;
		
	protected :
	
		void dirty();
		
	private :

		friend class Node;
		
		Node *m_node;

		Plug *m_input;
		std::list<Plug *> m_outputs;
				
};

} // namespace Gaffer

#endif // GAFFER_PLUG_H
