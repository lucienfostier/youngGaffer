import unittest
import weakref

import IECore
import gtk

import Gaffer
import GafferUI

class TestWidget( GafferUI.Widget ) :

	def __init__( self ) :
	
		GafferUI.Widget.__init__( self, gtk.Label( "hello" ) )
		self.gtkWidget().show()
		
class WidgetTest( unittest.TestCase ) :

	def testOwner( self ) :
	
		w = TestWidget()
		self.assert_( GafferUI.Widget.owner( w.gtkWidget() ) is w )
		
	def testParent( self ) :
	
		w = TestWidget()
		self.assert_( w.parent() is None )
		
	def testCanDie( self ) :
	
		w = TestWidget()
		
		wr1 = weakref.ref( w )
		wr2 = weakref.ref( w.gtkWidget() )
		
		del w
		self.assert_( wr1() is None )
		self.assert_( wr2() is None )
	
	def testAncestor( self ) :
	
		w = GafferUI.Window( "test" )
		l = GafferUI.ListContainer( GafferUI.ListContainer.Orientation.Vertical )
		p = GafferUI.Splittable()
		l.append( p )
		
		w.setChild( l )

		self.assert_( p.ancestor( GafferUI.ListContainer ) is l )
		self.assert_( p.ancestor( GafferUI.Window ) is w )
		self.assert_( p.ancestor( GafferUI.Menu ) is None )
			
if __name__ == "__main__":
	unittest.main()
	
