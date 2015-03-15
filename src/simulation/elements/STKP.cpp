#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_STKP PT_STKP PT_NORMAL_NUM + 7
Element_STKP::Element_STKP()
{
	Identifier = "DEFAULT_PT_STKP";
	Name = "STKP";
	Colour = PIXPACK(0xFFE9A9);
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
	HotAir = 0.00f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 100;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 0;
	Description = "Stickman Portal, Teleports stickman to other save with the id from it's TMP2.";

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

	Update = &Element_STKP::update;
	Graphics = &Element_STKP::graphics;
}

//#TPT-Directive ElementHeader Element_STKP static int update(UPDATE_FUNC_ARGS)
int Element_STKP::update(UPDATE_FUNC_ARGS)
{
	int r, nnx, rx, ry, fe = rand() % 50;
	int count = 0;
	parts[i].tmp = (int)((parts[i].temp - 73.15f) / 100 + 1);
	if (parts[i].tmp >= CHANNELS) parts[i].tmp = CHANNELS - 1;
	else if (parts[i].tmp<0) parts[i].tmp = 0;

	if (fe) {
		int orbd[4] = { 0, 0, 0, 0 };	//Orbital distances
		int orbl[4] = { 0, 0, 0, 0 };	//Orbital locations
		if (!sim->parts[i].life) parts[i].life = rand()*rand()*rand();
		if (!sim->parts[i].ctype) parts[i].ctype = rand()*rand()*rand();
		sim->orbitalparts_get(parts[i].life, parts[i].ctype, orbd, orbl);
		for (r = 0; r < 4; r++) {
			if (orbd[r]>1) {
				orbd[r] -= 12;
				if (orbd[r]<1) {
					orbd[r] = (rand() % 128) + 128;
					orbl[r] = rand() % 255;
				}
				else {
					orbl[r] += 2;
					orbl[r] = orbl[r] % 255;
				}
			}
			else {
				orbd[r] = (rand() % 128) + 128;
				orbl[r] = rand() % 255;
			}
		}
		sim->orbitalparts_set(&parts[i].life, &parts[i].ctype, orbd, orbl);
	}
	else {
		parts[i].life = 0;
		parts[i].ctype = 0;
	}
	return 0;
}


//#TPT-Directive ElementHeader Element_STKP static int graphics(GRAPHICS_FUNC_ARGS)
int Element_STKP::graphics(GRAPHICS_FUNC_ARGS)

{
	*firea = 8;
	*firer = 255;
	*fireg = 0;
	*fireb = 0;
	*pixel_mode |= EFFECT_DBGLINES;
	*pixel_mode |= EFFECT_GRAVIN;
	*pixel_mode &= ~PMODE;
	*pixel_mode |= PMODE_ADD;
	return 1;
}


Element_STKP::~Element_STKP() {}
