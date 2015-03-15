#include "simulation/Elements.h"
#include "simulation/Air.h"
//#TPT-Directive ElementClass Element_SLCN PT_SLCN PT_NORMAL_NUM + 8
Element_SLCN::Element_SLCN()
{
	Identifier = "DEFAULT_PT_SLCN";
	Name = "SLCN";
	Colour = PIXPACK(0x474747);
	MenuVisible = 1;
	MenuSection = SC_ELEC;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 1;
	Hardness = 0;

	Weight = 100;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 251;
	Description = "Silicons.";

	State = ST_SOLID;
	Properties = TYPE_SOLID | PROP_CONDUCTS | PROP_HOT_GLOW | PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = 95.0f;
	HighPressureTransition = PT_BSLN;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1687.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = NULL;
}

Element_SLCN::~Element_SLCN() {}
