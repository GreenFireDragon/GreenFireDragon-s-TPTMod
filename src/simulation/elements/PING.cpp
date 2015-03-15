#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_PING PT_PING PT_NORMAL_NUM + 13
Element_PING::Element_PING()
{
	Identifier = "DEFAULT_PT_PING";
	Name = "PING";
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
	Description = "PING";

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

	Update = &Element_PING::update;

}

//#TPT-Directive ElementHeader Element_PING static int RuleTable[5][16]
int Element_PING::RuleTable[5][16] =
{
	{ 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0 },
	{ 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0 },
};

//#TPT-Directive ElementHeader Element_PING static int ping[XRES/16][YRES/5];
int Element_PING::ping[XRES / 16][YRES / 5];

//#TPT-Directive ElementHeader Element_PING static int update(UPDATE_FUNC_ARGS)
int Element_PING::update(UPDATE_FUNC_ARGS)
{
	if (parts[i].life < 1)
	{
		sim->part_change_type(i, x, y, PT_PONG);
		parts[i].life = 30;
	}

	return 0;
}

Element_PING::~Element_PING() {}
