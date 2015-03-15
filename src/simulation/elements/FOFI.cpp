#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_FOFI PT_FOFI PT_NORMAL_NUM + 5
Element_FOFI::Element_FOFI()
{
	Identifier = "DEFAULT_PT_FOFI";
	Name = "FOFI";
	Colour = PIXPACK(0x127BC1);
	MenuVisible = 0;
	MenuSection = SC_SPECIAL;
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
	Meltable = 0;
	Hardness = 0;

	Weight = 100;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 186;
	Description = "Force Field.";

	State = ST_SOLID;
	Properties = TYPE_SOLID | PROP_LIFE_DEC | PROP_LIFE_KILL;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_FOFI::update;
	Graphics = &Element_FOFI::graphics;

}
//#TPT-Directive ElementHeader Element_FOFI static int update(UPDATE_FUNC_ARGS)
int Element_FOFI::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx<2; rx++)
	for (ry = -1; ry<2; ry++)
	if (BOUNDS_CHECK && (rx || ry))
	{
		r = pmap[y + ry][x + rx];
		if (!r)
			continue;
		if (!parts[i].ctype && parts[i].tmp == 0)
		{
			if ((r & 0xFF) != PT_NONE && (r & 0xFF) != PT_FOFI && (r & 0xFF) != PT_FSPW)
				sim->kill_part(r >> 8);
		}
		if (parts[i].ctype && parts[i].tmp == 0)
		{
			if ((r & 0xFF) != PT_NONE && (r & 0xFF) != PT_FOFI && (r & 0xFF) != PT_FSPW && (r & 0xFF) != parts[i].ctype)
				sim->kill_part(r >> 8);
		}
		if (parts[i].ctype && parts[i].tmp == 1)
		{
			if ((r & 0xFF) == parts[i].ctype)
				sim->kill_part(r >> 8);
		}
	}

	return 0;
}

//#TPT-Directive ElementHeader Element_FOFI static int graphics(GRAPHICS_FUNC_ARGS)
int Element_FOFI::graphics(GRAPHICS_FUNC_ARGS)
{
	*colr = rand() % 100;
	*colg = rand() % 100;
	*colb = rand() % 55 + 200;

	*firea = 255;
	*firer = *colr;
	*fireg = *colg;
	*fireb = *colb;

	*pixel_mode = PMODE_GLOW;
	*pixel_mode |= FIRE_ADD;

	return 0;
}

Element_FOFI::~Element_FOFI() {}
