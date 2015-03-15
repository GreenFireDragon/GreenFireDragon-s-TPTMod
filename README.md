GreenFireDragon's TPTMod
========================

- Plant create oxygen with water
	- TMP = 1 PLNT does not grow, TMP = 0 PLNT grows
	
- More Spawn options
	- STKM ctype = SPWN ctype
	- STKM jetpackElement = SPWN TMP2
	- STKM life = SPWN life
	- If SPWN TMP = 1, STKM spawns with jetpack
	
- More info: TMP2, DColour, Flags, PAVG, VX and VY, AirMode and GravityMode

- New elements
	- Black POWder(BPOW), idea by NUCLEAR_FOX
	- ALuminum PowDer(ALPD) and IRoN Oxide(IRNX), idea by Squirtle
	- CoPpER(CPER), SiLiCoN(SLCN) and Broken SiLicoN(BSLN), idea by bengala
	- Force Fields(FFGE(ForceField GEnerator), FSPW(Forcefield SPaWner) and FOFI(FOrcefield FIller)), c++ version of lua script by electronic_steve
		- Width of FOFI is set by FFGE TMP
		- FFGE no ctype and TMP = 0, kills all
		- FFGE has ctype and TMP = 0, kills all but ctype
		- FFGE has ctype and TMP = 0, kills only ctype
	- STicKman Portal(STKP)
		- SaveID = STKP TMP2
	- PING and PONG :D
	- Sound(SND(SouND), AMPL(AMPLifier), SWAV(Sound WAVe)), based on sound material idea by Abalone710
	- Void bOMB (VOMB)
	- MUD(MUD), SOIL(SOIL), TSED(Tree SEeDs), based on Element Suggestions: Soil, Seed, Mud by ROHAN
	- FSED(Flower SEeDs), FLWR(FLoWeR)
	- CTRL(ConTRoLler), creates spark when key (set by tmp, for key numbers see http://www.libsdl.org/release/SDL-1.2.15/include/SDL_keysym.h) is pressed
	- RAND(RANDom)
	- RBTY(Rechargable BaTterY)
	- NEMR(NEgative MatteR)

- Added TreeGen V1.0 :D (SED will generate a random tree when touches SOIL, when SOIL < 0C it will be a pine tree)

- Instead of pressing next a lot of times, you can put the page number in a textbox :D

- More gravity modes
	- Left, Right, Up, Unradial

- Added water equalisation and heat simulation quickoption (don't know why)

- Added random save button on the first page (where otherwise the previous button is), set max save ID in options

- Added an updater :D

//It would be nice if someone can compile for mac/linux
