#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_BPOW PT_BPOW PT_NORMAL_NUM + 1
Element_BPOW::Element_BPOW()
{
	Identifier = "DEFAULT_PT_BPOW";
	Name = "BPOW";
	Colour = PIXPACK(0x191919);
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
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

	Flammable = 50;
	Explosive = 1;
	Meltable = 0;
	Hardness = 10;

	Weight = 90;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 100;
	Description = "Black powder, very very explosive, maybe a bit to explosive.";

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

	Update = &Element_BPOW::update;

}

//#TPT-Directive ElementHeader Element_BPOW static int update(UPDATE_FUNC_ARGS)
int Element_BPOW::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx<2; rx++)
	for (ry = -1; ry<2; ry++)
	if (BOUNDS_CHECK && (rx || ry))
	{
		r = pmap[y + ry][x + rx];
		if (!r)
			continue;
		if ((r & 0xFF) == PT_FIRE || (r & 0xFF) == PT_PLSM || (r & 0xFF) == PT_SPRK || (r & 0xFF) == PT_LIGH || (r & 0xFF) == PT_THDR || (r & 0xFF) == PT_SMKE || (r & 0xFF) == PT_EMBR)
		{
			int nb = sim->create_part(-1, x + rand() % 3 - 1, y + rand() % 3 - 1, PT_EMBR);
			if (nb != -1) {
				parts[nb].tmp = 0;
				parts[nb].life = 30;
				parts[nb].vx = rand() % 20 - 10;
				parts[nb].vy = rand() % 20 - 10;
				parts[nb].temp = restrict_flt(parts[i].temp - 273.15f + 400.0f, MIN_TEMP, MAX_TEMP);
			}
			sim->pv[y / CELL][x / CELL] += 50;
		}
	}
	return 0;
}

Element_BPOW::~Element_BPOW() {}
