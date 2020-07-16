//
//  Node.hpp
//  FindPathTest-mobile
//  Node 节点
//  Created by 志强 on 2020/6/12.
//

#ifndef Node_hpp
#define Node_hpp

#include "cocos2d.h"

USING_NS_CC;
class AstarNode : public cocos2d::Node {
public:
    //列
    int x;
    //行
    int y;
    //代价 f = g+h
    float f;
    //起点到当前点代价
    float g;
    //当前点到终点估计代价
    float h;
    bool walkable = true;
    AstarNode*parent;
    float costMultiplier = 1.0;
public:
    AstarNode(int x,int y);
    ~AstarNode();
};

#endif /* Node_hpp */
