#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_RAND PT_RAND PT_NORMAL_NUM + 25
Element_RAND::Element_RAND()
{
	Identifier = "DEFAULT_PT_RAND";
	Name = "RAND";
	Colour = PIXPACK(0xFFFFFF);
	MenuVisible = 1;
	MenuSection = SC_SPECIAL;
	Enabled = 1;

	Advection = 0.00f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.00f;
	Loss = 0.00f;
	Collision = 0.00f;
	Gravity = -0.00f;
	Diffusion = 0.00f;
	HotAir = 0.00f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 0;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 0;
	Description = "RANDOM, changes into a random element.";

	State = ST_SOLID;
	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_RAND::update;
}


//#TPT-Directive ElementHeader Element_RAND static int update(UPDATE_FUNC_ARGS)
int Element_RAND::update(UPDATE_FUNC_ARGS)
{
	sim->part_change_type(i, x, y, rand() % (sim->DEFAULT_PT_NUM + 25));

	return 0;
}

Element_RAND::~Element_RAND() {}