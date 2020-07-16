//
//  Astar.cpp
//  FindPathTest-mobile
//
//  Created by 志强 on 2020/6/13.
//

#include "Astar.hpp"
#include "GameMap.hpp"

Astar::Astar()
{
    this->_heuristic = CC_CALLBACK_1(Astar::diagonal,this);
}
bool Astar::findPath(AstarGrid*grid)
{
    
    this->_grid = grid;
    this->_open.clear();
    this->_closed.clear();
    this->_startNode = this->_grid->startNode();
    this->_endNode = this->_grid->endNode();
    
    this->_startNode->g = 0;
    this->_startNode->h = this->_heuristic(this->_startNode);
    this->_startNode->f = this->_startNode->g + this->_startNode->h;
    
    return this->search();
}
bool Astar::search()
{
    AstarNode*node = this->_startNode;
    while (node != this->_endNode)
    {
        int startX = 0 > (node->x - 1)?0:(node->x - 1);
        int endX = (this->_grid->numCols() - 1) > (node->x + 1)?(node->x + 1):(this->_grid->numCols() - 1);
        int startY = 0 > (node->y - 1)?0:(node->y - 1);
        int endY = (this->_grid->numRows() - 1) > (node->y + 1)?(node->y + 1):(this->_grid->numRows() - 1);
        
        for(int i = startX;i<=endX;i++)
        {
            for(int j = startY;j<=endY;j++)
            {
                AstarNode*test = this->_grid->getNode(i, j);
                if(test == node || !test->walkable || !this->_grid->getNode(node->x, node->y)->walkable || !this->_grid->getNode(test->x,node->y)->walkable)
                {
                    continue;
                }
                float cost = this->_straightCost;
                if(!((node->x == test->x) || (node->y == test->y)))
                {
                    cost = this->_diagCost;
                }
                
                float g = node->g + cost*test->costMultiplier;
                float h = this->_heuristic(test);
                float f = g+h;
                
                if(isOpen(test) || isClosed(test))
                {
                    if(test->f > f)
                    {
                        test->f = f;
                        test->g = g;
                        test->h = h;
                        test->parent = node;
                    }
                }else{
                    test->f = f;
                    test->g = g;
                    test->h = h;
                    test->parent = node;
                    _open.pushBack(test);
                }
            }
        }
        _closed.pushBack(node);
        if(_open.size() == 0)
        {
            printf("------Astar path not fount");
            return false;
        }
        int openLen = this->_open.size();
        for(int i = 0;i<openLen;i++) {
            
            for(int j = i+1;j<openLen;j++){
                
                if(_open.at(i)->f > _open.at(j)->f){
                    
                    AstarNode*temp = _open.at(i);
                    _open.replace(i, _open.at(j));
                    _open.replace(j, temp);
                }
            }
        }
        node = _open.at(0);
        _open.erase(0);
    }
    this->buildPath();
    return true;
}
void Astar::buildPath()
{
    this->_path.clear();
    AstarNode*node = this->_endNode;
    this->_path.pushBack(node);
    while (node != this->_startNode) {
        node = node->parent;
        this->_path.insert(0, node);
    }
}
Vector<AstarNode*> Astar::path()
{
    return this->_path;
}
bool Astar::isOpen(AstarNode*node)
{
    for(int i = 0;i< _open.size();i++)
    {
        if(_open.at(i) == node)
        {
            return true;
        }
    }
    return false;
}
bool Astar::isClosed(AstarNode*node)
{
    for(int i = 0;i< _closed.size();i++)
    {
        if(_closed.at(i) == node)
        {
            return true;
        }
    }
    return false;
}
Vector<AstarNode*> Astar::visited()
{
    Vector<AstarNode*> vecs = this->_closed;
    for(auto c : _open)
    {
        vecs.pushBack(c);
    }
    return vecs;
}
float Astar::diagonal(AstarNode*node)
{
    int dx = abs(node->x - this->_endNode->x);
    int dy = abs(node->y - this->_endNode->y);
    int diag = dx<=dy?dx:dy;
    int straight = dx + dy;
    
    return this->_diagCost * diag + this->_straightCost * (straight - 2 * diag);
}
Astar::~Astar()
{
    
}
