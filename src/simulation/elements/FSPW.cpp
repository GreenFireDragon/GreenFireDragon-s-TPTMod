#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_FSPW PT_FSPW PT_NORMAL_NUM + 6
Element_FSPW::Element_FSPW()
{
	Identifier = "DEFAULT_PT_FSPW";
	Name = "FSPW";
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

	Temperature = R_TEMP + 273.15f;
	HeatConduct = 3;
	Description = "Force Field Spawner.";

	State = ST_SOLID;
	Properties = TYPE_SOLID | PROP_HOT_GLOW | PROP_LIFE_DEC | PROP_LIFE_KILL;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 2573.15f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_FSPW::update;
}

//#TPT-Directive ElementHeader Element_FSPW static int update(UPDATE_FUNC_ARGS)
int Element_FSPW::update(UPDATE_FUNC_ARGS)
{
	int _ran = rand() % 25, np, t;
	for (t = 0; t < 4; t++)
	if (_ran >= 1 && _ran <= 13)
	{
		if (_ran >= 1 && _ran <= 3)
		{
			np = sim->create_part(-1, x + rand() % parts[i].tmp2, y, PT_FOFI);
			if (np)
			{
				parts[np].ctype = parts[i].ctype;
				parts[np].tmp = parts[i].tmp;
			}
		}
		if (_ran >= 4 && _ran <= 6)
		{
			np = sim->create_part(-1, x, y + rand() % parts[i].tmp2, PT_FOFI);
			if (np)
			{
				parts[np].ctype = parts[i].ctype;
				parts[np].tmp = parts[i].tmp;
			}
		}
		if (_ran >= 7 && _ran <= 9)
		{
			np = sim->create_part(-1, x - rand() % parts[i].tmp2, y, PT_FOFI);
			if (np)
			{
				parts[np].ctype = parts[i].ctype;
				parts[np].tmp = parts[i].tmp;
			}
		}
		if (_ran >= 10 && _ran <= 12)
		{
			np = sim->create_part(-1, x, y - rand() % parts[i].tmp2, PT_FOFI);
			if (np)
			{
				parts[np].ctype = parts[i].ctype;
				parts[np].tmp = parts[i].tmp;
			}
		}
	}

	return 0;
}

Element_FSPW::~Element_FSPW() {}
