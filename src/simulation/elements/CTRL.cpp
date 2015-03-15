#include "simulation/Elements.h"
#ifdef SDL_INC
#include "SDL/SDL.h"
#else
#include "SDL.h"
#endif
//#TPT-Directive ElementClass Element_CTRL PT_CTRL PT_NORMAL_NUM + 17
Element_CTRL::Element_CTRL()
{
	Identifier = "DEFAULT_PT_CTRL";
	Name = "CTRL";
	Colour = PIXPACK(0xAFAFAF);
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
	HeatConduct = 251;
	Description = "Controller, set key by tmp, interval by tmp2.";

	State = ST_SOLID;
	Properties = TYPE_SOLID | PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_CTRL::update;
	Graphics = &Element_CTRL::graphics;
}

//#TPT-Directive ElementHeader Element_CTRL static int update(UPDATE_FUNC_ARGS)
int Element_CTRL::update(UPDATE_FUNC_ARGS)
{
	if (SDL_GetKeyState(0)[parts[i].tmp] && parts[i].life == 0)
	{
		int r, rx, ry, rt;
		for (rx = -2; rx < 3; rx++)
		for (ry = -2; ry < 3; ry++)
		if (BOUNDS_CHECK && (rx || ry) && abs(rx) + abs(ry) < 4)
		{
			r = pmap[y + ry][x + rx];
			if (!r)
				continue;
			rt = (r & 0xFF);
			if (sim->parts_avg(i, r >> 8, PT_INSL) != PT_INSL)
			{
				if ((sim->elements[rt].Properties&PROP_CONDUCTS) && parts[r >> 8].life == 0)
				{
					parts[i].life = 4 + parts[i].tmp2;
					parts[r >> 8].life = 4;
					parts[r >> 8].ctype = rt;
					sim->part_change_type(r >> 8, x + rx, y + ry, PT_SPRK);
				}
			}
		}
	}

	return 0;
}

//#TPT-Directive ElementHeader Element_CTRL static int graphics(GRAPHICS_FUNC_ARGS)
int Element_CTRL::graphics(GRAPHICS_FUNC_ARGS)
{
	int ftmp2;
	if (cpart->tmp2 == 0)
		ftmp2 = 1;
	else
		ftmp2 = cpart->tmp2;

	int stage = (int)(((float)cpart->life / ftmp2)*100.0f);
	*colr += stage;
	*colg += stage;
	*colb += stage;
	return 0;
}

Element_CTRL::~Element_CTRL() {}
