//
//  MapViewBg.cpp
//  FindPathTest-mobile
//
//  Created by 志强 on 2020/6/13.
//

#include "MapViewBg.hpp"

MapViewBg::MapViewBg(GridObj*birthP)
{
    this->_birthG = birthP;
    visibleSize = Director::getInstance()->getVisibleSize();
    this->setContentSize(Size(GM()->MAX_WIDTH,GM()->MAX_HEIGHT));
    this->updateHDMap();
}
void MapViewBg::refreshViewPort(int gx,int gy)
{
//    int imgSize = 256;
//    int blockW = ceil(visibleSize.width/imgSize);
//    int blockH = ceil(visibleSize.height/imgSize);
//    GridObj*blockXY = GM()->grid2MapBlock(gx, gy);
//    int initX = blockXY->col - ceil(blockW>>1) - 2;
//    int initY = blockXY->row - ceil(blockH >> 1) - 1;
//    int maxX = ceil(GM()->MAX_WIDTH / imgSize);
//    int maxY = ceil(GM()->MAX_HEIGHT / imgSize);
//    initX = initX < 0?0:initX;
//    initY = initY < 0?0:initY;
//    int endX = blockXY->col + ceil(blockW>>1) + 1;
//    int endY = blockXY->row + ceil(blockH>>1) + 1;
//    endX = endX > maxX?maxX:endX;
//    endY = endY > maxY?maxY:endY;
//    for(int i = initX;i<endX;i++)
//    {
//        for(int j = initY;j<endY;j++)
//        {
//            std::string key = StringUtils::format("%d_",i)+StringUtils::format("%d",j);
//            std::string sourceName = StringUtils::format("map%d/",GM()->levelMapId)+key+".png";
//            MapShowCfg*cfg = mapShowlish[key];
//            if(cfg != NULL && !cfg->show)
//            {
//                mapShowlish[key]->show = true;
////                mapShowlish[key]->img->setVisible(true);
//                Sprite*sp = Sprite::create(sourceName);
//                mapShowlish[key]->img->setTexture(sp->getTexture());
////                mapShowlish[key]->img->setContentSize(texture->getContentSize());
//
//                mapShowlish[key]->img->setTextureRect(sp->getTextureRect());
//            }
//        }
//    }
}
void MapViewBg::clearHDMap()
{
    mapShowlish.clear();
    this->removeAllChildren();
}
void MapViewBg::updateHDMap()
{
    int imgSize = 256;
    this->maxImgX = ceil(GM()->MAX_WIDTH / imgSize);
    this->maxImgY = ceil(GM()->MAX_HEIGHT / imgSize);
    for(int i = 0;i<this->maxImgX;i++)
    {
        for(int j = 0;j<this->maxImgY;j++)
        {
            std::string key = StringUtils::format("%d_",i)+StringUtils::format("%d",j);
            std::string sourceName = StringUtils::format("map%d/",GM()->levelMapId)+key+".png";
            Sprite*rect = Sprite::create("map1/0_0.png");
            Sprite*bg = Sprite::create(sourceName);
            bg->setAnchorPoint(Vec2(0,1));
//            bg->setContentSize(Size(imgSize,imgSize));
            bg->setTextureRect(rect->getTextureRect());
            
            bg->setPosition(Vec2(i*imgSize,GM()->MAX_HEIGHT - j*imgSize));
//            std::string key = StringUtils::format("%d_",i)+StringUtils::format("%d",j);
            this->addChild(bg);
            MapShowCfg*obj = new MapShowCfg();
            obj->show = false;
            obj->img = bg;
            mapShowlish[key] = obj;
            
            
        }
    }
}
MapViewBg::~MapViewBg()
{
    
}
