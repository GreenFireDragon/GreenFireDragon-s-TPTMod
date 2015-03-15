#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_SND PT_SND PT_NORMAL_NUM + 11
Element_SND::Element_SND()
{
	Identifier = "DEFAULT_PT_SND";
	Name = "SND";
	Colour = PIXPACK(0xDFDFDF);
	MenuVisible = 1;
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
	Hardness = 1;

	Weight = 100;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 0;
	Description = "Sound, creates sound waves.";

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

	Update = &Element_SND::update;
}

//#TPT-Directive ElementHeader Element_SND static int update(UPDATE_FUNC_ARGS)
int Element_SND::update(UPDATE_FUNC_ARGS)
{
	int np, ang, x2, y2;

	if (parts[i].tmp < 1)
	{
		for (ang = 0; ang < 361; ang++)
		{
			x2 = x + sin(ang);
			y2 = y + cos(ang);
			np = sim->create_part(-1, x2, y2, PT_SWAV);
			if (np)
			{
				parts[np].tmp = ang;
				parts[np].tmp2 = parts[i].temp;
				parts[np].life = parts[i].life;
				if (parts[i].tmp2 > 5)
				{
					parts[np].vx = sin(ang) * parts[i].temp;
					parts[np].vy = cos(ang) * parts[i].temp;
				}
				else
				{
					parts[np].vx = sin(ang) * 5;
					parts[np].vy = cos(ang) * 5;
				}
			}
		}
	}

	return 0;
}

Element_SND::~Element_SND() {}
