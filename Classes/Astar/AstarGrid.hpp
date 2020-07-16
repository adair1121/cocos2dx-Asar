//
//  AstarGrid.hpp
//  FindPathTest-mobile
//  网格类
//  Created by 志强 on 2020/6/12.
//

#ifndef AstarGrid_hpp
#define AstarGrid_hpp

#include "cocos2d.h"
#include "AstarNode.hpp"

USING_NS_CC;

class AstarGrid : public cocos2d::Node {
private:
    //起点
    AstarNode*_startNode;
    //终点
    AstarNode*_endNode;
    //node 数组
    std::vector<std::vector<AstarNode*>> _nodes;
    //网格行列
    int _numCols;
    int _numRows;
public:
    AstarGrid(int numCols,int numRows);
    ~AstarGrid();
public:
    AstarNode *getNode(int x,int y);
    void setEndNode(int x,int y);
    void setStartNode(int x,int y);
    void setWalkable(int x,int y ,bool value);
    
    AstarNode* endNode();
    AstarNode* startNode();
    int numCols();
    int numRows();
    
};

#endif /* AstarGrid_hpp */
