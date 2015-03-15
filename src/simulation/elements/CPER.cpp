#include "simulation/Elements.h"
#include "simulation/Air.h"
//#TPT-Directive ElementClass Element_CPER PT_CPER PT_NORMAL_NUM + 10
Element_CPER::Element_CPER()
{
	Identifier = "DEFAULT_PT_CPER";
	Name = "CPER";
	Colour = PIXPACK(0x995500);
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
	Meltable = 1;
	Hardness = 0;

	Weight = 100;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 100;
	Description = "Copper, conducts faster than metal but slower than gold.";

	State = ST_SOLID;
	Properties = TYPE_SOLID | PROP_CONDUCTS | PROP_HOT_GLOW | PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1357.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_CPER::update;
}

//#TPT-Directive ElementHeader Element_CPER static int update(UPDATE_FUNC_ARGS)
int Element_CPER::update(UPDATE_FUNC_ARGS)
{
	int rx, ry, r, blocking = 0;
	static int checkCoordsX[] = { -3, 3, 0, 0 };
	static int checkCoordsY[] = { 0, 0, -3, 3 };
	//Find sparks
	if (!parts[i].life)
	{
		for (int j = 0; j < 4; j++){
			rx = checkCoordsX[j];
			ry = checkCoordsY[j];
			if ((!rx != !ry) && BOUNDS_CHECK) {
				r = pmap[y + ry][x + rx];
				if (!r) continue;
				if ((r & 0xFF) == PT_SPRK && parts[r >> 8].life && parts[r >> 8].life<4)
				{
					parts[i].life = 4;
					parts[i].type = PT_SPRK;
					parts[i].ctype = PT_CPER;
				}
			}
		}
	}
	return 0;
}

Element_CPER::~Element_CPER() {}
