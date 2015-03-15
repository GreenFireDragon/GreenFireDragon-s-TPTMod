#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_RBTY PT_RBTY PT_NORMAL_NUM + 23
Element_RBTY::Element_RBTY()
{
	Identifier = "DEFAULT_PT_RBTY";
	Name = "RBTY";
	Colour = PIXPACK(0x9A9A4C);
	MenuVisible = 1;
	MenuSection = SC_ELEC;
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
	Description = "Recharable battery, PSCN charges, NSCN sets charge to 0.";

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

	Update = &Element_RBTY::update;
	Graphics = &Element_RBTY::graphics;
}

//#TPT-Directive ElementHeader Element_RBTY static int update(UPDATE_FUNC_ARGS)
int Element_RBTY::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry, rt;
	for (rx = -2; rx<3; rx++)
	for (ry = -2; ry<3; ry++)
	if (BOUNDS_CHECK && (rx || ry) && abs(rx) + abs(ry)<4)
	{
		r = pmap[y + ry][x + rx];
		if (!r)
			continue;
		rt = (r & 0xFF);
		if (sim->parts_avg(i, r >> 8, PT_INSL) != PT_INSL)
		{
			if ((sim->elements[rt].Properties&PROP_CONDUCTS) && !(rt == PT_WATR || rt == PT_SLTW || rt == PT_NTCT || rt == PT_PTCT || rt == PT_INWR || rt == PT_PSCN || rt == PT_NSCN) && parts[r >> 8].life == 0 && parts[i].life > 0)
			{
				parts[i].life--;
				parts[r >> 8].life = 4;
				parts[r >> 8].ctype = rt;
				sim->part_change_type(r >> 8, x + rx, y + ry, PT_SPRK);
			}

			if (parts[i].life < parts[i].tmp && rt == PT_SPRK && parts[r >> 8].ctype == PT_PSCN && parts[r >> 8].life == 3)
			{
				parts[i].life += parts[i].tmp2;
			}

			if (parts[i].life > 0 && rt == PT_SPRK && parts[r >> 8].ctype == PT_NSCN && parts[r >> 8].life == 3)
			{
				parts[i].life = 0;
			}
		}
	}

	if (parts[i].life > parts[i].tmp)
		parts[i].life = parts[i].tmp;

	if (parts[i].life < 0)
		parts[i].life = 0;
	if (parts[i].tmp < 0)
		parts[i].tmp = 0;

	return 0;
}

//#TPT-Directive ElementHeader Element_RBTY static int graphics(GRAPHICS_FUNC_ARGS)
int Element_RBTY::graphics(GRAPHICS_FUNC_ARGS)
{
	int ftmp;
	if (cpart->tmp == 0)
		ftmp = 1;
	else
		ftmp = cpart->tmp;

	int stage = (int)(((float)cpart->life / ftmp)*100.0f);
	*colr += stage;
	*colg += stage;
	*colb += stage;

	return 0;
}

Element_RBTY::~Element_RBTY() {}
