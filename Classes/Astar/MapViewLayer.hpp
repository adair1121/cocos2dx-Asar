//
//  MapViewLayer.hpp
//  FindPathTest-mobile
//
//  Created by 志强 on 2020/6/13.
//

#ifndef MapViewLayer_hpp
#define MapViewLayer_hpp

#include "cocos2d.h"
//#include "GameMap.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MapViewBg.hpp"
USING_NS_CC;

using namespace cocos2d::ui;

class MapViewLayer : public cocos2d::Layer{
private:
    MapViewBg*_mapbg;
    Size visibleSize;
    Sprite*_hero;
    Vector<AstarNode*> _paths;
public:
    MapViewLayer();
    ~MapViewLayer();
public:
    void initMap();
    
    void refreshMapos(float rolex,float roley);
private:
    void judageMapImgX();
    void judageMapImgY();
    bool juageIfInXBorder();
    bool juageIfInYBorder();
    Vector<AstarNode*> findPath(int sx,int sy,int ex,int ey);
    void execMoveAct(GridObj*endP);
    void execMove();
    void drawTestGrid();
};

#endif /* MapViewLayer_hpp */
