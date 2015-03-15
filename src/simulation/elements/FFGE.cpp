#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_FFGE PT_FFGE PT_NORMAL_NUM + 4
Element_FFGE::Element_FFGE()
{
	Identifier = "DEFAULT_PT_FFGE";
	Name = "FFGE";
	Colour = PIXPACK(0x591B69);
	MenuVisible = 1;
	MenuSection = SC_POWERED;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.0f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 10;

	Weight = 100;

	Temperature = R_TEMP + -200.0f + 273.15f;
	HeatConduct = 0;
	Description = "Force Field Generator.";

	State = ST_SOLID;
	Properties = TYPE_SOLID | PROP_DRAWONCTYPE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_FFGE::update;

}

//#TPT-Directive ElementHeader Element_FFGE static int update(UPDATE_FUNC_ARGS)
int Element_FFGE::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry, x2, y2, ang, np;

	for (rx = -1; rx<2; rx++)
	for (ry = -1; ry<2; ry++)
	if (BOUNDS_CHECK && (rx || ry))
	{
		r = pmap[y + ry][x + rx];
		if (!r)
			continue;
		if ((r&0xFF) == PT_SPRK)
		{
			for (ang = 0; ang <= 360; ang++)
			{
				x2 = x + (parts[i].temp * sin(ang));
				y2 = y + (parts[i].temp * cos(ang));
				np = sim->create_part(-1, x2, y2, PT_FSPW);
				if (np)
				{
					parts[np].ctype = parts[i].ctype;
					parts[np].tmp = parts[i].tmp;
					if (parts[i].tmp2 < 3)
						parts[np].tmp2 = 3;
					else
						parts[np].tmp2 = parts[i].tmp2;
				}
			}
		}
	}

	return 0;
}

Element_FFGE::~Element_FFGE() {}
