#include "QuickOption.h"
#include "GameModel.h"

class SandEffectOption: public QuickOption
{
public:
	SandEffectOption(GameModel * m):
	QuickOption("P", "Sand effect", m, Toggle)
	{

	}
	virtual bool GetToggle() 
	{
		return m->GetSimulation()->pretty_powder;
	}
	virtual void perform()
	{
		m->GetSimulation()->pretty_powder = !m->GetSimulation()->pretty_powder;
	}
};

class DrawGravOption: public QuickOption
{
public:
	DrawGravOption(GameModel * m):
	QuickOption("G", "Draw gravity field \bg(ctrl+g)", m, Toggle)
	{

	}
	virtual bool GetToggle() 
	{
		return m->GetGravityGrid();
	}
	virtual void perform()
	{
		m->ShowGravityGrid(!m->GetGravityGrid());
	}
};

class DecorationsOption: public QuickOption
{
public:
	DecorationsOption(GameModel * m):
	QuickOption("D", "Draw decorations \bg(ctrl+b)", m, Toggle)
	{

	}
	virtual bool GetToggle() 
	{
		return m->GetDecoration();
	}
	virtual void perform()
	{
		m->SetDecoration(!m->GetDecoration());
	}
};

class NGravityOption: public QuickOption
{
public:
	NGravityOption(GameModel * m):
	QuickOption("N", "Newtonian Gravity \bg(n)", m, Toggle)
	{

	}
	virtual bool GetToggle() 
	{
		return m->GetSimulation()->grav->ngrav_enable;
	}
	virtual void perform()
	{
		if(m->GetSimulation()->grav->ngrav_enable)
		{
			m->GetSimulation()->grav->stop_grav_async();
			m->SetInfoTip("Newtonian Gravity: Off");
		}
		else
		{
			m->GetSimulation()->grav->start_grav_async();
			m->SetInfoTip("Newtonian Gravity: On");
		}
	}
};

class AHeatOption: public QuickOption
{
public:
	AHeatOption(GameModel * m):
	QuickOption("A", "Ambient heat \bg(u)", m, Toggle)
	{

	}
	virtual bool GetToggle() 
	{
		return m->GetAHeatEnable();
	}
	virtual void perform()
	{
		m->SetAHeatEnable(!m->GetAHeatEnable());
	}
};

class WaterEquaOption : public QuickOption
{
public:
	WaterEquaOption(GameModel * m) :
		QuickOption("E", "Water equalisation \bg(t)", m, Toggle)
	{

	}
	virtual bool GetToggle()
	{
		return m->GetWaterEnable();
	}
	virtual void perform()
	{
		m->SetWaterEnable(!m->GetWaterEnable());
	}
};

class HeatOption : public QuickOption
{
public:
	HeatOption(GameModel * m) :
		QuickOption("H", "Heat simulation \bg(m)", m, Toggle)
	{

	}
	virtual bool GetToggle()
	{
		return !m->GetHeatEnable();
	}
	virtual void perform()
	{
		m->SetHeatEnable(!m->GetHeatEnable());
	}
};

class ConsoleShowOption: public QuickOption
{
	GameController * c;
public:
	ConsoleShowOption(GameModel * m, GameController * c_):
	QuickOption("C", "Show Console \bg(~)", m, Toggle)
	{
		c = c_;
	}
	virtual bool GetToggle()
	{
		return 0;
	}
	virtual void perform()
	{
		c->ShowConsole();
	}
};