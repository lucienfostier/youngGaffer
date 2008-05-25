import IECore
import Gaffer
import unittest
import GafferUI

class NameGadgetTest( unittest.TestCase ) :

	def test( self ) :
	
		n = Gaffer.Node()
	
		g = GafferUI.NameGadget( IECore.Font( "/usr/X11R6/lib/X11/fonts/TTF/Vera.ttf" ), n )
		
		self.assertEqual( g.getText(), n.getName() )
		
		n.setName( "somethingElse" )
		self.assertEqual( g.getText(), n.getName() )
		
	
		
	
if __name__ == "__main__":
	unittest.main()
	