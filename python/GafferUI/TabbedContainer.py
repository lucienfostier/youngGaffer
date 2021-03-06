import gtk
import IECore

import GafferUI

class TabbedContainer( GafferUI.ContainerWidget ) :

	def __init__( self ) :
	
		GafferUI.ContainerWidget.__init__( self, gtk.Notebook() )
		
		self.__widgets = []
								
	def append( self, child ) :
	
		oldParent = child.parent()
		if oldParent :
			oldParent.removeChild( child )
		
		self.__widgets.append( child )
		self.gtkWidget().append_page( child.gtkWidget() )
				
	def remove( self,  child ) :
	
		self.removeChild( child )
		
	def setLabel( self, child, labelText ) :
	
		assert child in self.__widgets
	
		self.gtkWidget().set_tab_label_text( child.gtkWidget(), labelText )
			
	def getLabel( self, child ) :
	
		return self.gtkWidget().get_tab_label_text( child.gtkWidget() )
	
	def setCurrent( self, child ) :
	
		self.gtkWidget().set_current_page( self.__widgets.index( child ) )

	def getCurrent( self ) :
	
		if not self.__widgets :
			return None
			
		return self.__widgets[ self.gtkWidget().get_current_page() ]
		
	def __getitem__( self, index ) :
	
		return self.__widgets[index]
	
	def __delitem__( self, index ) :
	
		self.removeChild( self.__widgets[index] )
	
	def __len__( self ) :
	
		return len( self.__widgets )
	
	## Implemented to always return True - otherwise empty TabbedContainers
	# are considered False and we don't really want that.
	def __nonzero__( self ) :
	
		return True
		
	def removeChild( self, child ) :
	
		self.__widgets.remove( child )
		self.gtkWidget().remove( child.gtkWidget() )

GafferUI.Widget._parseRCStyle(

	"""
	style "gafferTabbed" = "gafferWidget"
	{
		bg[ACTIVE] = $bgActive # for some reason the active color is used for the unselected tabs
	}

	style "gafferTabbedLabel" = "gafferWidget"
	{
		fg[ACTIVE] = $fgActive
		text[ACTIVE] = $fgActive
	}

	widget_class "*<GtkNotebook>" style "gafferTabbed"
	widget_class "*<GtkNotebook>.*" style "gafferTabbedLabel"
	""",
	
	{
		"bgActive" : GafferUI.Widget._gtkRCColor( IECore.Color3f( 0.05 ) ),
		"fgActive" : GafferUI.Widget._gtkRCColor( IECore.Color3f( 0.6 ) ),
	}

)
