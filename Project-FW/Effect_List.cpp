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
	std::vector<CTiles*> MapTiles_List = g_MapTiles_List->GetMapTilesList() ;
	/*const int ObjectSize = DynamicObjects_List.size() ;
	const int EffectSize = m_Effect_List.size() ;

	for(int Index_o=0; Index_o<ObjectSize; Index_o++)
	{
		pDynamicObject = DynamicObjects_List[Index_o] ;

		for(int Index_e=0; Index_e<EffectSize; Index_e++)
		{
			pEffect = m_Effect_List[Index_e] ;
			bool bCollision=false ;

			bCollision = col.DotCirleCollision(pDynamicObject, pEffect) ;
			if(bCollision)
				pEffect->Effect(pDynamicObject) ;
		}
	}*/

	const int ObjectSize = DynamicObjects_List.size() ;
	const int TileSize = MapTiles_List.size() ;
	const int EffectSize = m_Effect_List.size() ;

	for(int Index=0; Index<ObjectSize || Index<TileSize; Index++)
	{
		if(Index<ObjectSize)
		{
			pDynamicObject = DynamicObjects_List[Index] ;
			pDynamicObject->EventClear() ;
		}
		if(Index<TileSize)
		{
			pTile = MapTiles_List[Index] ;
			pTile->EventClear() ;
		}

		for(int Index_e=0; Index_e<EffectSize; Index_e++)
		{
			pEffect = m_Effect_List[Index_e] ;

			if(!pEffect->BeVisible())
				continue ;

			if(pDynamicObject!=NULL)
			{
				bool bCollision=false ;

				bCollision = col.RectCircleCollision(pDynamicObject, pEffect) ;
				if(bCollision)
					pEffect->Effect(pDynamicObject) ;
			}
			if(pTile!=NULL)
			{
				bool bCollision=false ;

				bCollision = col.RectCircleCollision(pTile, pEffect) ;
				if(bCollision)
					pEffect->Effect(pTile) ;
			}
		}

		pDynamicObject = NULL ;
		pTile = NULL ;
	}
}