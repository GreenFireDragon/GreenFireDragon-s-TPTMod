#include "simulation/Elements.h"
#include "simulation/Air.h"
//#TPT-Directive ElementClass Element_BSLN PT_BSLN PT_NORMAL_NUM + 9
Element_BSLN::Element_BSLN()
{
	Identifier = "DEFAULT_PT_BSLN";
	Name = "BSLN";
	Colour = PIXPACK(0x575757);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.7f;
	AirDrag = 0.05f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.85f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 1;
	Hardness = 10;

	Weight = 100;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 201;
	Description = "Broken Silicons.";

	State = ST_SOLID;
	Properties = TYPE_PART | PROP_CONDUCTS | PROP_HOT_GLOW | PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1687.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = NULL;
}

Element_BSLN::~Element_BSLN() {}
