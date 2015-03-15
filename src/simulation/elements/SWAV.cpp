#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_SWAV PT_SWAV PT_NORMAL_NUM + 12
Element_SWAV::Element_SWAV()
{
	Identifier = "DEFAULT_PT_SWAV";
	Name = "SWAV";
	Colour = PIXPACK(0xDFDFDF);
	MenuVisible = 0;
	MenuSection = SC_SPECIAL;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 1.00f;
	Loss = 1.00f;
	Collision = -0.99f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = -1;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 251;
	Description = "Sound waves, break glass and kills stickman.";

	State = ST_GAS;
	Properties = TYPE_ENERGY | PROP_DEADLY | PROP_LIFE_DEC | PROP_LIFE_KILL | PROP_DRAWONCTYPE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_SWAV::update;
	Graphics = &Element_SWAV::graphics;
}

//#TPT-Directive ElementHeader Element_SWAV static int update(UPDATE_FUNC_ARGS)
int Element_SWAV::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;

	for (rx = -1; rx<2; rx++)
	for (ry = -1; ry<2; ry++)
	if (BOUNDS_CHECK && (rx || ry))
	{
		r = pmap[y + ry][x + rx];
		if (!r && !sim->bmap[(y + ry) / CELL][(x + rx) / CELL])
			continue;
		if ((r & 0xFF) == PT_GLAS)
		{
			sim->part_change_type(r >> 8, parts[r >> 8].x, parts[r >> 8].y, PT_BGLA);
		}
		if ((r & 0xFF) == PT_AMPL)
		{
			parts[i].life = parts[r >> 8].life;
			parts[i].tmp2 += parts[r >> 8].tmp / 10;
		}
		if (sim->bmap[(y + ry) / CELL][(x + rx) / CELL])
		{
			if (parts[i].pavg[0] == 0)
			{
				parts[i].pavg[0] = 1;
				parts[i].pavg[1] = rx;
				parts[i].pavg[2] = ry;
			}
			else
			{
				parts[i].pavg[0] = 0;
				parts[i].pavg[1] = rx;
				parts[i].pavg[2] = ry;
			}
		}
	}

	if (parts[i].pavg[0] == 0)
	{
		parts[i].vx = (sin(parts[i].tmp) * parts[i].tmp2);
		parts[i].vy = (cos(parts[i].tmp) * parts[i].tmp2);
	}
	else
	{
		parts[i].vx = (sin(parts[i].tmp) * parts[i].tmp2) * parts[i].pavg[1];
		parts[i].vy = (cos(parts[i].tmp) * parts[i].tmp2) * parts[i].pavg[2];
	}


	return 0;
}

//#TPT-Directive ElementHeader Element_SWAV static int graphics(GRAPHICS_FUNC_ARGS)
int Element_SWAV::graphics(GRAPHICS_FUNC_ARGS)
{
	*colr = cpart->life * 5;
	*colg = cpart->life * 5;
	*colb = cpart->life * 5;
	return 0;
}

Element_SWAV::~Element_SWAV() {}
