#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_AMPL PT_AMPL PT_NORMAL_NUM + 15
Element_AMPL::Element_AMPL()
{
	Identifier = "DEFAULT_PT_AMPL";
	Name = "AMPL";
	Colour = PIXPACK(0xDFDFDF);
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
	HeatConduct = 0;
	Description = "Amplifier, speeds up sound waves.";

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

	Update = NULL;
}

Element_AMPL::~Element_AMPL() {}
