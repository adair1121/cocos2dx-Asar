//
//  GameMap.cpp
//  FindPathTest-mobile
//
//  Created by 志强 on 2020/6/13.
//

#include "GameMap.hpp"
GameMap::GameMap(){}

USING_NS_CC;

static GameMap *s_pInstance = NULL; // pointer to singleton
GameMap* GameMap::getInstance()
{
    if (s_pInstance == NULL)
    {
        s_pInstance = new GameMap();
    }

    return s_pInstance;
}
