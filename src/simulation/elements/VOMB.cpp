#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_VOMB PT_VOMB PT_NORMAL_NUM + 16
Element_VOMB::Element_VOMB()
{
	Identifier = "DEFAULT_PT_VOMB";
	Name = "VOMB";
	Colour = PIXPACK(0x6d2828);
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 30;

	Temperature = R_TEMP - 2.0f + 273.15f;
	HeatConduct = 29;
	Description = "Void bomb.";

	State = ST_NONE;
	Properties = TYPE_PART | PROP_LIFE_DEC | PROP_LIFE_KILL_DEC | PROP_SPARKSETTLE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_VOMB::update;
	Graphics = &Element_VOMB::graphics;
}

//#TPT-Directive ElementHeader Element_VOMB static int update(UPDATE_FUNC_ARGS)
int Element_VOMB::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry, nx, ny, np;

	if (parts[i].life == 0)
	{
		for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
		if (BOUNDS_CHECK && (rx || ry))
		{
			r = pmap[y + ry][x + rx];
			if (!r)
				continue;
			if ((r & 0xFF) != PT_VOMB && ((r & 0xFF) != PT_EMBR && parts[r >> 8].ctype != PT_VOMB) && (r & 0xFF) != PT_DMND)
			{
				for (int l = 0; l < 25; l++)
				{
					for (int a = 0; a < 361; a++)
					{
						nx = x + sin(a) * l;
						ny = y + cos(a) * l;
						if (!(nx > XRES && ny > YRES && nx < 0 && ny < 0))
						{
							if ((sim->pmap[ny][nx] & 0xFF) != PT_VOMB && (sim->pmap[ny][nx] & 0xFF) != PT_DMND && ((sim->pmap[ny][nx] & 0xFF) != PT_EMBR && parts[sim->pmap[ny][nx] >> 8].ctype != PT_VOMB))
							{
								sim->delete_part(nx, ny);
							}
								np = sim->create_part(-1, x + sin(a) * l, y + cos(a) * l, PT_EMBR);
								if (np)
								{
									parts[np].life = (25 - l) * 2;
									if (l > 23)
									{
										parts[np].vx = sin(a) * 10;
										parts[np].vy = cos(a) * 10;
									}
									parts[np].ctype = PT_VOMB;
									parts[np].dcolour = 0xFF6D2828;
								}
						}
					}
				}
				parts[i].life = 50;
			}
		}
	}

	if (parts[i].life > 0)
	{
		sim->pv[y / CELL][x / CELL] -= 75.0f;
		parts[i].vx = parts[i].vy = 0;
	}

	return 0;
}


//#TPT-Directive ElementHeader Element_VOMB static int graphics(GRAPHICS_FUNC_ARGS)
int Element_VOMB::graphics(GRAPHICS_FUNC_ARGS)
{
	*pixel_mode |= PMODE_FLARE;
	return 1;
}


Element_VOMB::~Element_VOMB() {}
