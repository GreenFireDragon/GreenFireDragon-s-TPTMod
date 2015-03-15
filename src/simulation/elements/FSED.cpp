#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_FSED PT_FSED PT_NORMAL_NUM + 21
Element_FSED::Element_FSED()
{
	Identifier = "DEFAULT_PT_FSED";
	Name = "FSED";
	Colour = PIXPACK(0xD5EA3A);
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
	Description = "Flower seed, requires soil.";

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

	Update = &Element_FSED::update;
}

//#TPT-Directive ElementHeader Element_FSED static int update(UPDATE_FUNC_ARGS)
int Element_FSED::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry, type;

		for (rx = 0; rx < 1; rx++)
		for (ry = -1; ry < 2; ry++)
		if (BOUNDS_CHECK && (rx || ry))
		{
			r = pmap[y + ry][x + rx];
			if (!r)
				continue;
			if ((r & 0xFF) == PT_SOIL)
			{
				sim->part_change_type(i, x, y, PT_PLNT);

				if (!parts[i].tmp2)
					type = rand() % 3;
				else
					type = parts[i].tmp2 - 1;
				FlowerGen(type, sim, i, x, y, surround_space, nt, parts, pmap);
			}
		}

	return 0;
}

//#TPT-Directive ElementHeader Element_FSED static int FlowerGen(int type, UPDATE_FUNC_ARGS)
int Element_FSED::FlowerGen(int type, UPDATE_FUNC_ARGS)
{
	int h, ch, np, nx, ny, rt;

	h = rand() % 15 + 5;

	for (ch = 0; ch < h; ch++)
	{
		sim->create_part(-1, x, y - ch, PT_PLNT);
	}

	if (type == 0)
	{
		np = sim->create_part(-1, x, y - h, PT_FLWR);
		parts[np].tmp = rand() % 7;
	}

	if (type == 1)
	{
		int col = rand() % 7;
		for (nx = 0; nx < 5; nx++)
		for (ny = 0; ny < 6; ny++)
		{
			rt = pmap[y - h - ny][x - 2 + nx];
			if (!rt && Element_FSED::Type1Table[ny][nx] == 1)
			{
				np = sim->create_part(-1, x - 2 + nx, y - h - ny, PT_FLWR);
				parts[np].tmp = col;
			}
		}
	}

	if (type == 2)
	{
		int col = rand() % 7;
		for (nx = 0; nx < 11; nx++)
		for (ny = 0; ny < 11; ny++)
		{
			rt = pmap[y - h - ny][x - 5 + nx];
			if (!rt && Element_FSED::Type2Table[ny][nx] == 1)
			{
				np = sim->create_part(-1, x - 5 + nx, y - h - ny, PT_FLWR);
				parts[np].tmp = col;
			}
			else if (!rt && Element_FSED::Type2Table[ny][nx] == 2)
			{
				np = sim->create_part(-1, x - 5 + nx, y - h - ny, PT_FLWR);
				parts[np].tmp = 3;
			}
		}
	}

	return 0;
}

//#TPT-Directive ElementHeader Element_FSED static int Type1Table[6][5]
int Element_FSED::Type1Table[6][5] =
{
	{ 0, 0, 1, 0, 0 },
	{ 0, 1, 1, 1, 0 },
	{ 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1 },
	{ 1, 0, 1, 0, 1 },
};

//#TPT-Directive ElementHeader Element_FSED static int Type2Table[11][11]
int Element_FSED::Type2Table[11][11] =
{
	{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 0, 0, 2, 0, 0, 1, 1, 0 },
	{ 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1 },
	{ 0, 1, 1, 0, 0, 2, 0, 0, 1, 1, 0 },
	{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
};

Element_FSED::~Element_FSED() {}
