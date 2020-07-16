//
//  MapViewBg.hpp
//  FindPathTest-mobile
//
//  Created by 志强 on 2020/6/13.
//

#ifndef MapViewBg_hpp
#define MapViewBg_hpp

#include "cocos2d.h"
#include "GameMap.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocos2d::ui;
struct MapShowCfg
{
    bool show;
    Sprite*img;
};

class MapViewBg : public cocos2d::Layer {
private:
    int maxImgX;
    int maxImgY;
    GridObj*_birthG;
    Size visibleSize;
    std::map<std::string,MapShowCfg*> mapShowlish;
public:
    MapViewBg(GridObj*birthP);
    ~MapViewBg();
public:
    void updateHDMap();
    
    void clearHDMap();
    
    void refreshViewPort(int gx,int gy);
};
#endif /* MapViewBg_hpp */
