#include "Effect_List.h"
#include "Effect.h"
#include "DynamicObjects.h"
#include "Tiles.h"
#include "Collision.h"

#include "DynamicObjects_List.h"
#include "MapTiles_List.h"

CEffect_List::CEffect_List()
{
}
CEffect_List::~CEffect_List()
{
	Clear() ;
}

void CEffect_List::AddEffect(CEffect *pEffect)
{
	m_Effect_List.push_back(pEffect) ;
}

void CEffect_List::Clear()
{
	if(!m_Effect_List.empty())
		m_Effect_List.clear() ;
}

void CEffect_List::Collision()
{
	CCollision col ;

	CDynamicObjects *pDynamicObject ;
	CTiles *pTile ;
	CEffect *pEffect ;
	std::vector<CDynamicObjects*> DynamicObjects_List = g_DynamicObjects_List->GetDynamicObjectsList() ;
	std::vector<CTiles*> MapTiles_List ;
	
	const int EffectSize = m_Effect_List.size() ;
	const int ObjectSize = DynamicObjects_List.size() ;
	int TileSize ;

	for(int Index_e=0; Index_e<EffectSize; Index_e++)
	{
		pEffect = m_Effect_List[Index_e] ;

		if(!pEffect->BeVisible())
			continue ;

		//********** DynamicObjects_List Collision **********//
		for(int Index_o=0; Index_o<ObjectSize; Index_o++)
		{
			pDynamicObject = DynamicObjects_List[Index_o] ;

			bool bCollision=false ;

			bCollision = col.RectCircleCollision(pDynamicObject, pEffect) ;
			if(bCollision)
				pEffect->Effect(pDynamicObject) ;
		}

		//********** MapTiles_List Collision **********//
		const int x = (int)(pEffect->GetPositionX() / 64.0f) ;
		const int y = (int)(pEffect->GetPositionY() / 64.0f) ;
		const int radius = pEffect->GetBoundingCircle().radius ;

		MapTiles_List = g_MapTiles_List->GetAdjacentAllMapTilesList(x, y, radius) ;
		TileSize = MapTiles_List.size() ;

		for(int Index_t=0; Index_t<TileSize; Index_t++)
		{
			pTile = MapTiles_List[Index_t] ;

			bool bCollision=false ;

			bCollision = col.RectCircleCollision(pTile, pEffect) ;
			if(bCollision)
				pEffect->Effect(pTile) ;
		}
	}
}