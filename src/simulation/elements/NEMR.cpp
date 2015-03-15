#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_NEMR PT_NEMR PT_NORMAL_NUM + 24
Element_NEMR::Element_NEMR()
{
	Identifier = "DEFAULT_PT_NEMR";
	Name = "NEMR";
	Colour = PIXPACK(0x154242);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = -0.09f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.96f;
	Loss = 0.89f;
	Collision = -0.09f;
	Gravity = -0.70f;
	Diffusion = 1.00f;
	HotAir = 0.0000f * CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 99;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 0;
	Description = "Negative Matter, follows weird pyshics.";

	State = ST_NONE;
	Properties = TYPE_PART | PROP_LIFE_KILL | PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_NEMR::update;
	Graphics = &Element_NEMR::graphics;
}

//#TPT-Directive ElementHeader Element_NEMR static int update(UPDATE_FUNC_ARGS)
int Element_NEMR::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry, rt, nb;
	for (rx = -1; rx<2; rx++)
	for (ry = -1; ry<2; ry++)
	if (BOUNDS_CHECK && (rx || ry))
	{
		r = pmap[y + ry][x + rx];
		if ((r & 0xFF) == PT_NEMR)
			parts[r >> 8].temp = parts[i].temp;
		if (!r)
			continue;
		if (parts[r >> 8].type != PT_NEMR && parts[r >> 8].type != PT_EXOT)
		{
			parts[i].temp = (rand() * rand()) % 10000;
			parts[r >> 8].temp = (rand() * rand()) % 10000;
			if (parts[r >> 8].temp > MAX_TEMP){
				parts[r >> 8].temp = MAX_TEMP;
			}
		}
		if (parts[r >> 8].type == PT_EXOT)
		{
			parts[r >> 8].temp -= 400.f;
			sim->pv[y / CELL][x / CELL] = 256;
			sim->gravmap[(y / CELL)*(XRES / CELL) + (x / CELL)] = 0.2f*(-900);

			sim->create_part(-1, parts[i].x - 1, parts[i].y - 1, PT_THDR);
			sim->create_part(-1, parts[i].x - 1, parts[i].y + 1, PT_PLSM);
			sim->create_part(-1, parts[i].x + 1, parts[i].y + 1, PT_PROT);
			sim->create_part(-1, parts[i].x + 1, parts[i].y - 1, PT_ELEC);
		}
	}
	return 0;
}

//#TPT-Directive ElementHeader Element_NEMR static int graphics(GRAPHICS_FUNC_ARGS)
int Element_NEMR::graphics(GRAPHICS_FUNC_ARGS)
{
	*firea = 255;
	*firer = 121;
	*fireg = 166;
	*fireb = 166;
	*pixel_mode |= FIRE_ADD;
	return 1;
}

Element_NEMR::~Element_NEMR() {}