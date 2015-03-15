#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_MUD PT_MUD PT_NORMAL_NUM + 19
Element_MUD::Element_MUD()
{
	Identifier = "DEFAULT_PT_MUD";
	Name = "MUD";
	Colour = PIXPACK(0x493804);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f  * CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 25;

	Weight = 35;

	Temperature = R_TEMP - 2.0f + 273.15f;
	HeatConduct = 40;
	Description = "Mud.";

	State = ST_LIQUID;
	Properties = TYPE_LIQUID | PROP_LIFE_DEC | PROP_NEUTPENETRATE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 273.15f + 500.0f;
	HighTemperatureTransition = PT_BRCK;

	Update = NULL;
}

Element_MUD::~Element_MUD() {}
