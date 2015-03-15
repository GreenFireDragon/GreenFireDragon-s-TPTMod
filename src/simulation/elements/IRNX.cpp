#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_IRNX PT_IRNX PT_NORMAL_NUM + 3
Element_IRNX::Element_IRNX()
{
	Identifier = "DEFAULT_PT_IRNX";
	Name = "IRNX";
	Colour = PIXPACK(0x340000);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
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

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 10;

	Weight = 85;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 100;
	Description = "Iron Oxide. Combine with Aluminum Powder to make Thermite.";

	State = ST_SOLID;
	Properties = TYPE_PART | PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1720;
	HighTemperatureTransition = PT_IRON;

	Update = NULL;
}

Element_IRNX::~Element_IRNX() {}
