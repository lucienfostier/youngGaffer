###################################################################################################
# try to import gtk, handling any errors as gracefully as we can
###################################################################################################
import sys
import IECore

import warnings
warnings.filterwarnings( "error", "could not open display", Warning, "gtk" )

try :

	import pygtk
	pygtk.require( "2.0" )
	import gtk

except Exception, e :

	IECore.msg( IECore.Msg.Level.Error, "GafferUI", "Unable to initialise UI toolkit (%s)." % e )
	sys.exit( 1 )

###################################################################################################
# gtk imported ok. bring in the GafferUI components
###################################################################################################

from _GafferUI import *
import CamelCase
from Widget import Widget
from Menu import Menu
from PlugValueWidget import PlugValueWidget
from NumericPlugValueWidget import NumericPlugValueWidget
from StringPlugValueWidget import StringPlugValueWidget
from FileNamePlugValueWidget import FileNamePlugValueWidget
from PlugWidget import PlugWidget
from ContainerWidget import ContainerWidget
from Window import Window
from Splittable import Splittable
from EditorWidget import EditorWidget
from ScriptEditor import ScriptEditor
from ListContainer import ListContainer
from GLWidget import GLWidget
from GadgetWidget import GadgetWidget
from GraphEditor import GraphEditor
from ScriptWindow import ScriptWindow
from MenuBar import MenuBar
from EventLoop import EventLoop
from TabbedContainer import TabbedContainer
from CompoundEditor import CompoundEditor
from TextWidget import TextWidget
from NameWidget import NameWidget
from NodeSetEditor import NodeSetEditor
from NodeEditor import NodeEditor
from ScrolledContainer import ScrolledContainer
from PathWidget import PathWidget
from PathListingWidget import PathListingWidget
from PathChooserWidget import PathChooserWidget
from Button import Button
from Dialogue import Dialogue
from PathChooserDialogue import PathChooserDialogue
import FileMenu
import Layouts
import LayoutMenu
import EditMenu
import NodeMenu
from TextInputDialogue import TextInputDialogue
from Viewer import Viewer
from Frame import Frame
from CompoundNumericPlugValueWidget import CompoundNumericPlugValueWidget
from Collapsible import Collapsible
from NodeUI import NodeUI
from ColorSwatch import ColorSwatch
from ColorPlugValueWidget import ColorPlugValueWidget
from Slider import Slider
from ColorChooser import ColorChooser
from ColorChooserDialogue import ColorChooserDialogue
from SplineWidget import SplineWidget
from SplinePlugValueWidget import SplinePlugValueWidget
from SplineEditor import SplineEditor
from ShowURL import showURL
from Label import Label
from URLWidget import URLWidget
from AboutWindow import AboutWindow
import ApplicationMenu

## \todo Move the settings munging somewhere else
# - perhaps this is best done by the Preferences node?
settings = gtk.settings_get_default()

# stop gtk menus feeling sluggish
## \todo Should we not be doing this in the Menu code somewhere rather than here?
m = gtk.Menu() # have to make a menu for the property to be created
del m
settings.set_property( "gtk-menu-popup-delay", 0 )
settings.set_property( "gtk-menu-popdown-delay", 0 )
