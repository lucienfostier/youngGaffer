import unittest

import IECore

import Gaffer

class SplinePlugTest( unittest.TestCase ) :

	def testConstructor( self ) :
	
		s = IECore.Splineff(
			IECore.CubicBasisf.catmullRom(),
			(
				( 0, 0 ),
				( 0, 0 ),
				( 0.2, 0.3 ),
				( 0.4, 0.9 ),
				( 1, 1 ),
				( 1, 1 ),
			)
		)
	
		p = Gaffer.SplineffPlug( "a", defaultValue=s )
		
		self.assertEqual( p.getValue(), s )
		
		s2 = IECore.Splineff(
			IECore.CubicBasisf.linear(),
			(
				( 1, 1 ),
				( 1, 1 ),
				( 0.2, 0.3 ),
				( 0.4, 0.9 ),
				( 0, 0 ),
				( 0, 0 ),
			)
		)
		
		p.setValue( s2 )
		
		self.assertEqual( p.getValue(), s2 ) 

	def testSerialisation( self ) :
	
		s = IECore.Splineff(
			IECore.CubicBasisf.catmullRom(),
			(
				( 0, 0 ),
				( 0, 0 ),
				( 0.2, 0.3 ),
				( 0.4, 0.9 ),
				( 1, 1 ),
				( 1, 1 ),
			)
		)
	
		p = Gaffer.SplineffPlug( "a", defaultValue=s, flags=Gaffer.Plug.Flags.Dynamic )
		self.assertEqual( p.getValue(), s )
		
		sn = Gaffer.ScriptNode()
		sn["n"] = Gaffer.Node()
		sn["n"]["p"] = p
		
		se = sn.serialise()
		
		sn = Gaffer.ScriptNode()
		sn.execute( se )
		
		self.assertEqual( sn["n"]["p"].getValue(), s )

if __name__ == "__main__":
	unittest.main()
	