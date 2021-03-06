#ifndef GAFFER_TYPEIDS_H
#define GAFFER_TYPEIDS_H

namespace Gaffer
{

enum TypeId
{

	GraphComponentTypeId = 400000,
	NodeTypeId = 400001,
	PlugTypeId = 400002,
	ValuePlugTypeId = 400003,
	FloatPlugTypeId = 400004,
	IntPlugTypeId = 400005,
	StringPlugTypeId = 400006,
	ScriptNodeTypeId = 400007,
	ApplicationRootTypeId = 400008,
	ScriptContainerTypeId = 400009,
	SetTypeId = 400010,
	ObjectPlugTypeId = 400011,
	CompoundPlugTypeId = 400012,
	V2fPlugTypeId = 400013,
	V3fPlugTypeId = 400014,
	V2iPlugTypeId = 400015,
	V3iPlugTypeId = 400016,
	Color3fPlugTypeId = 400017,
	Color4fPlugTypeId = 400018,
	SplineffPlugTypeId = 400019,
	SplinefColor3fPlugTypeId = 400020,
	M33fPlugTypeId = 400021,
	M44fPlugTypeId = 400022,
	
	FirstPythonTypeId = 405000,
	
	LastTypeId = 409999
	
};

} // namespace Gaffer

#endif // GAFFER_TYPEIDS_H
