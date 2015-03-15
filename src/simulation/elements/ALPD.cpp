#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_ALPD PT_ALPD PT_NORMAL_NUM + 2
Element_ALPD::Element_ALPD()
{
	Identifier = "DEFAULT_PT_ALPD";
	Name = "ALPD";
	Colour = PIXPACK(0xdedede);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.7f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.96f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 25;

	Weight = 89;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 85;
	Description = "Aluminum Powder. Combine with Iron Oxide to make Thermite.";

	State = ST_SOLID;
	Properties = TYPE_PART | PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 2773;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_ALPD::update;

}

//#TPT-Directive ElementHeader Element_ALPD static int update(UPDATE_FUNC_ARGS)
int Element_ALPD::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx<2; rx++)
	for (ry = -1; ry<2; ry++)
	if (BOUNDS_CHECK && (rx || ry))
	{
		r = pmap[y + ry][x + rx];
		if (!r)
			continue;
		if ((r & 0xFF) == PT_IRNX)
		{
			sim->part_change_type(r >> 8, x, y, PT_THRM);
			sim->kill_part(i);
		}
	}
	return 0;
}

Element_ALPD::~Element_ALPD() {}
