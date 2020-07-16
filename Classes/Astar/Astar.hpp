//
//  Astar.hpp
//  FindPathTest-mobile
//
//  Created by 志强 on 2020/6/13.
//

#ifndef Astar_hpp
#define Astar_hpp

#include "cocos2d.h"
#include "AstarNode.hpp"
#include "AstarGrid.hpp"
USING_NS_CC;

class Astar : public cocos2d::Node{
private:
    //待考察表
    Vector<AstarNode*> _open;
    //已考察表
    Vector<AstarNode*> _closed;
    //网格
    AstarGrid*_grid;
    //终点node
    AstarNode*_endNode;
    //起点node
    AstarNode*_startNode;
    //保存路径
    Vector<AstarNode*> _path;
    //寻路算法
    std::function<float (AstarNode*node)> _heuristic;
    //上下左右走的代价
    float _straightCost = 1.0;
    //斜着走的代价 2的平方根
    float _diagCost = 1.4142135623730951;
public:
    Astar();
    ~Astar();
public:
    bool findPath(AstarGrid*grid);
    
    bool search();
    
    Vector<AstarNode*> path();
    
    Vector<AstarNode*> visited();
    
private:
    //获取路径
    void buildPath();
    //是否d待检查
    bool isOpen(AstarNode*node);
    //是否已i检查
    bool isClosed(AstarNode*node);
    //曼哈顿算法
    void manhattan(AstarNode*node);
    
    void euclidian(AstarNode*node);
    
    float diagonal(AstarNode*node);
    
};

#endif /* Astar_hpp */
