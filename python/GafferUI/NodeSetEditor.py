import Gaffer
import GafferUI

## The NodeSetEditor is a base class for all Editors which focus their
# editing on a subset of nodes beneath a ScriptNode. This set defaults
# to the ScriptNode.selection() but can be modified to be any Set of nodes.
class NodeSetEditor( GafferUI.EditorWidget ) :

	def __init__( self, gtkWidget, scriptNode ) :
	
		GafferUI.EditorWidget.__init__( self, gtkWidget, scriptNode )
			
	def setScriptNode( self, scriptNode ) :
	
		GafferUI.EditorWidget.setScriptNode( self, scriptNode )
		
		if scriptNode :
			self.setNodeSet( scriptNode.selection() )
		else :
			self.setNodeSet( Gaffer.Set() )
			
	def setNodeSet( self, nodeSet ) :
	
		self.__nodeSet = nodeSet
		self.__memberAddedConnection = self.__nodeSet.memberAddedSignal().connect( self.__membersChanged )
		self.__memberRemovedConnection = self.__nodeSet.memberRemovedSignal().connect( self.__membersChanged )
		self._updateFromSet()
		
	def getNodeSet( self ) :
	
		return self.__nodeSet
		
	def _updateFromSet( self ) :
	
		raise NotImplementedError

	def __membersChanged( self, set, member ) :
	
		## \todo Check that all set members are children of the script
		
		self._updateFromSet()
