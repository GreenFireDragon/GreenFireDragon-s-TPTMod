#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_FLWR PT_FLWR PT_NORMAL_NUM + 22
Element_FLWR::Element_FLWR()
{
	Identifier = "DEFAULT_PT_FLWR";
	Name = "FLWR";
	Colour = PIXPACK(0xF400A1);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.95f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 20;
	Explosive = 0;
	Meltable = 0;
	Hardness = 10;

	Weight = 100;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 65;
	Description = "Flower.";

	State = ST_SOLID;
	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 573.0f;
	HighTemperatureTransition = PT_FIRE;

	Graphics = &Element_FLWR::graphics;
}

//#TPT-Directive ElementHeader Element_FLWR static int graphics(GRAPHICS_FUNC_ARGS)
int Element_FLWR::graphics(GRAPHICS_FUNC_ARGS)
{
	switch (cpart->tmp)
	{
	case 1: //Red
		*colr = 255;
		*colg = 36;
		*colb = 00;
		break;
	case 2: //Orange
		*colr = 255;
		*colg = 127;
		*colb = 80;
		break;
	case 3: //Yellow
		*colr = 232;
		*colg = 222;
		*colb = 42;
		break;
	case 4: //Blue
		*colr = 101;
		*colg = 156;
		*colb = 239;
		break;
	case 5: //Purple
		*colr = 181;
		*colg = 126;
		*colb = 220;
		break;
	case 6: //White
		*colr = 255;
		*colg = 250;
		*colb = 240;
		break;
	case 0: //Pink
	default:
		break;
	}

	return 0;
}

Element_FLWR::~Element_FLWR() {}
