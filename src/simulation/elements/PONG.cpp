#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_PONG PT_PONG PT_NORMAL_NUM + 14
Element_PONG::Element_PONG()
{
	Identifier = "DEFAULT_PT_PONG";
	Name = "PONG";
	Colour = PIXPACK(0x2535fc);
	MenuVisible = 0;
	MenuSection = SC_WALL;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.00f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.0f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 100;

	Temperature = 373.0f;
	HeatConduct = 40;
	Description = "PONG";

	State = ST_GAS;
	Properties = TYPE_SOLID | PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_PONG::update;

}

//#TPT-Directive ElementHeader Element_PONG static int RuleTable[5][16]
int Element_PONG::RuleTable[5][16] =
{
	{ 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0 },
	{ 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1 },
	{ 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0 },
};

//#TPT-Directive ElementHeader Element_PONG static int pong[XRES/16][YRES/5];
int Element_PONG::pong[XRES / 16][YRES / 5];

//#TPT-Directive ElementHeader Element_PONG static int update(UPDATE_FUNC_ARGS)
int Element_PONG::update(UPDATE_FUNC_ARGS)
{
	if (parts[i].life < 1)
	{
		sim->part_change_type(i, x, y, PT_PING);
		parts[i].life = 30;
	}

	return 0;
}

Element_PONG::~Element_PONG() {}
