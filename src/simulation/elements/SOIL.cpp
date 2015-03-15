#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_SOIL PT_SOIL PT_NORMAL_NUM + 18
Element_SOIL::Element_SOIL()
{
	Identifier = "DEFAULT_PT_SOIL";
	Name = "SOIL";
	Colour = PIXPACK(0x9F7616);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.7f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.94f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.2f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 2;
	Hardness = 2;

	Weight = 56;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 70;
	Description = "Soil place seed on it to grow a tree.";

	State = ST_SOLID;
	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_SOIL::update;
}

//#TPT-Directive ElementHeader Element_SOIL static int update(UPDATE_FUNC_ARGS)
int Element_SOIL::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	float cxy = 0;
	for (rx = -1; rx<2; rx++)
	for (ry = -1; ry<2; ry++)
	if (BOUNDS_CHECK && (rx || ry))
	{
		r = pmap[y + ry][x + rx];
		if (!r)
			continue;
		if ((r & 0xFF) == PT_WATR)
		{
			if (!(rand() % 50))
			{
				sim->part_change_type(i, x, y, PT_MUD);
				sim->kill_part(r >> 8);
			}
		}
	}
	return 0;
}

Element_SOIL::~Element_SOIL() {}
