#include "Tiles_JailTrap.h"
#include "Sprite.h"

CTiles_JailTrap::CTiles_JailTrap()
{
}
CTiles_JailTrap::~CTiles_JailTrap()
{
}

void CTiles_JailTrap::Init()
{
	LoadDat("Resource/Data/Tiles/Jail_trap.dat") ;
}

void CTiles_JailTrap::Effect()
{
	m_State = EFFECT ;
}