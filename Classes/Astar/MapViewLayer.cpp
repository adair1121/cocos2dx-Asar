//
//  MapViewLayer.cpp
//  FindPathTest-mobile
//
//  Created by 志强 on 2020/6/13.
//

#include "MapViewLayer.hpp"
#include "MapParse.h"
#include "Astar.hpp"

MapViewLayer::MapViewLayer()
{
    
}
void MapViewLayer::initMap()
{
    this->setAnchorPoint(Vec2(0,0));
    visibleSize = Director::getInstance()->getVisibleSize();
    this->setContentSize(Size(GM()->MAX_WIDTH,GM()->MAX_HEIGHT));
    GM()->levelMapId = 1;
    std::string mapcfg = StringUtils::format("map%d.json",GM()->levelMapId);
    MP()->loadJson(mapcfg.c_str());
    _mapbg = new MapViewBg(GM()->roleBirthGrids.at(0));
    this->addChild(_mapbg);
    _mapbg->setAnchorPoint(Vec2(0,0));
    _mapbg->setPosition(Vec2(0,0));
    GridObj*roleBirth = GM()->roleBirthGrids.at(0);
    GridObj*obj = GM()->grid2point(roleBirth->col, roleBirth->row);
    
    _hero = Sprite::create("blur1.png");
    _hero->setTextureRect(Rect(0, 0, 50, 50));
    this->addChild(_hero);
    _hero->setPosition(Vec2(obj->col,GM()->MAX_HEIGHT - obj->row));
    
    this->refreshMapos(obj->col, obj->row);
    this->drawTestGrid();
    
    GridObj*endp = new GridObj();
    endp->col = 42;
    endp->row = 46;
    execMoveAct(endp);
}
void MapViewLayer::execMoveAct(GridObj*endP)
{
    GridObj*startG = GM()->point2Grid(_hero->getPositionX(), GM()->MAX_HEIGHT - _hero->getPositionY());
    Vector<AstarNode*> paths = findPath(startG->col, startG->row, endP->col, endP->row);
    _paths = paths;
    if(_paths.size() > 0)
    {
        //去掉第一个格子。这个格子与人物在同一位置
        _paths.erase(0);
        
        this->execMove();
    }
}
void MapViewLayer::execMove()
{
    if(_paths.size() > 0)
    {
        AstarNode*node = _paths.at(0);
        _paths.erase(0);
        
        GridObj*movePos = GM()->grid2point(node->x, node->y);
        auto moveto = MoveTo::create(2.0f, Vec2(movePos->col,GM()->MAX_HEIGHT - movePos->row));
        
        auto callback = CallFunc::create([&](){
            execMove();
        });
        _hero->runAction(Sequence::create(moveto,callback, NULL));
    }
    
}
Vector<AstarNode*> MapViewLayer::findPath(int sx,int sy,int ex,int ey)
{
    GM()->astarGrid->setEndNode(ex, ey);
    GM()->astarGrid->setStartNode(sx,sy);
    Vector<AstarNode*> vecs;
    
    Astar*astar = new Astar();
    if(astar->findPath(GM()->astarGrid))
    {
        vecs = astar->path();
    }
    return vecs;
}
void MapViewLayer::refreshMapos(float rolex,float roley)
{
    float x = (-rolex) + (visibleSize.width)/2;
    float y = GM()->MAX_HEIGHT - (-roley) + (visibleSize.height)/2;
    this->setPosition(Vec2(x,y));
    this->judageMapImgX();
    this->judageMapImgY();
    GridObj*obj = GM()->point2Grid(rolex, roley);
//    _mapbg->refreshViewPort(obj->col, obj->row);
}
//判断是否在X边界
bool MapViewLayer::juageIfInXBorder(){
//    return (this.hero.x <= StageUtils.inst().getWidth()>>1) || (this.hero.x >= (GameMap.MAX_WIDTH - (StageUtils.inst().getWidth()>>1)))
}
//判断是否在X边界
bool MapViewLayer::juageIfInYBorder(){
//    return (this.hero.y <= StageUtils.inst().getHeight()>>1) || (this.hero.y >= (GameMap.MAX_HEIGHT - (StageUtils.inst().getHeight()>>1)))
    
}
void MapViewLayer::judageMapImgX()
{
    if(this->getPositionX() < -(GM()->MAX_WIDTH - visibleSize.width)){
        float x =  -(GM()->MAX_WIDTH - visibleSize.width);
        this->setPositionX(x);
    }
    if(this->getPositionX() > 0){
        this->setPositionX(0);
    }
}
void MapViewLayer::judageMapImgY()
{
    if(this->getPositionY() < -(GM()->MAX_HEIGHT - visibleSize.height)){
        float y =  -(GM()->MAX_HEIGHT - visibleSize.height);
        this->setPositionY(y);
    }
    if(this->getPositionY() > 0){
        this->setPositionY(0);
    }
}
void MapViewLayer::drawTestGrid()
{
    Layout*container = Layout::create();
    _mapbg->addChild(container);
    container->setContentSize(Size(GM()->MAX_WIDTH,GM()->MAX_WIDTH));
    container->setAnchorPoint(Vec2(0,0));
    container->setPosition(Vec2(0,0));
    
    int maxX = GM()->COL;
    int maxY = GM()->ROW;
    for(int i = 0;i<maxY;i++)
    {
        for(int j = 0;j<maxX;j++)
        {
            std::string key = StringUtils::format("%d_",i)+StringUtils::format("%d",j);
            auto myLabel = Label::createWithSystemFont("My Label Text", "Arial", 16);
            this->addChild(myLabel);
            myLabel->setString(key);
            myLabel->setColor(Color3B(0,0,0));
            float x = j * GM()->CELL_SIZE;
            float y = GM()->MAX_HEIGHT - i * GM()->CELL_SIZE;
            myLabel->setPosition(Vec2(x,y));
        }
    }
    
}
MapViewLayer::~MapViewLayer()
{
    
}
