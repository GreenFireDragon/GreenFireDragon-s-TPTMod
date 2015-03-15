#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_TSED PT_TSED PT_NORMAL_NUM + 20
Element_TSED::Element_TSED()
{
	Identifier = "DEFAULT_PT_TSED";
	Name = "TSED";
	Colour = PIXPACK(0xA3B808);
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

	Flammable = 100;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 10;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 70;
	Description = "Tree Seed, place on soil to graw a tree.";

	State = ST_SOLID;
	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 273.15f + 500.0f;
	HighTemperatureTransition = PT_FIRE;

	Update = &Element_TSED::update;
}

//#TPT-Directive ElementHeader Element_TSED static int update(UPDATE_FUNC_ARGS)
int Element_TSED::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = 0; rx<1; rx++)
	for (ry = -1; ry<2; ry++)
	if (BOUNDS_CHECK && (rx || ry))
	{
		r = pmap[y + ry][x + rx];
		if (!r)
			continue;
		if ((r & 0xFF) == PT_SOIL)
		{
			if (parts[r >> 8].temp < 273.15f)
				parts[i].tmp = 1;

			parts[i].ctype = PT_TSED;
			parts[i].tmp2 = 0;

			sim->part_change_type(i, x, y, PT_WOOD);
		}
	}

	return 0;
}

//#TPT-Directive ElementHeader Element_TSED static int TreeGen(UPDATE_FUNC_ARGS)
int Element_TSED::TreeGen(UPDATE_FUNC_ARGS) //TreeGen V1.0 by GreenFireDragon
{
	int rx, ry, h, ch, np;

	if (parts[i].tmp2 == 0)
	{
		h = rand() % 150 + 50;
		for (rx = -1; rx < 2; rx++)
		for (ch = 0; ch < h; ch++)
		{
			if (rand() % 10)
			{
				np = sim->create_part(-1, x + rx, y - ch, PT_WOOD);
				if (rand() % (ch + 1) > (h / 3))
				{
					parts[np].ctype = PT_TSED;

					if (parts[i].tmp == 0)
					{
						if (ch > (h / 3) * 2)
						{
							parts[np].life = h - ch;
						}
						else
						{
							parts[np].life = ch - (h / 3);
						}
					}
					else
					{
						parts[np].life = (h - ch) / 2;
					}

					if (rx == -1)
					{
						parts[np].tmp2 = 1;
					}
					else if (rx == 1)
					{
						parts[np].tmp2 = 2;
					}
					else
					{
						parts[np].tmp2 = 3;
					}
				}
				else
				{
					parts[np].tmp2 = 3;
				}
			}
		}
	}
	else
	{
		if (parts[i].life > 0)
		{
			if (parts[i].tmp2 == 1)
				rx = -1;
			else if (parts[i].tmp2 == 2)
				rx = 1;
				
			ry = rand() % 3 + (-1);
		
			np = sim->create_part(-1, x + rx, y + ry, PT_WOOD);

			parts[np].ctype = PT_TSED;
			parts[np].life = parts[i].life - 1;
			parts[np].tmp2 = parts[i].tmp2;
		}

		if (parts[i].tmp2 > 0)
		{
			for (rx = -1; rx<2; rx++)
			for (ry = -1; ry<2; ry++)
			{
				if (rand() % 2)
				{
					sim->create_part(-1, x + rx, y + ry, PT_PLNT);
				}
			}
			parts[i].tmp2 = 0;
		}
	}

	return 0;
}

Element_TSED::~Element_TSED() {}
