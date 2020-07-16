//
//  AstarGrid.cpp
//  FindPathTest-mobile
//
//  Created by 志强 on 2020/6/12.
//

#include "AstarGrid.hpp"

AstarGrid::AstarGrid(int numCols,int numRows)
{
    this->_numCols = numCols;
    this->_numRows = numRows;
    this->_nodes.clear();
    for(int i = 0;i<numCols;i++)
    {
        std::vector<AstarNode*> vecs;
        for(int j = 0;j<numRows;j++)
        {
            vecs.push_back(new AstarNode(i,j));
        }
        this->_nodes.push_back(vecs);
    }
}
AstarNode *AstarGrid::getNode(int x,int y)
{
    return this->_nodes.at(x).at(y);
}
void AstarGrid::setEndNode(int x,int y)
{
    this->_endNode = this->_nodes.at(x).at(y);
}
void AstarGrid::setStartNode(int x,int y)
{
    this->_startNode = this->_nodes.at(x).at(y);
}
void AstarGrid::setWalkable(int x,int y ,bool value)
{
    this->_nodes.at(x).at(y)->walkable = value;
}
AstarNode* AstarGrid::endNode()
{
    return this->_endNode;
}
AstarNode* AstarGrid::startNode()
{
    return this->_startNode;
}
int AstarGrid::numCols()
{
    return this->_numCols;
}
int AstarGrid::numRows()
{
    return this->_numRows;
}
AstarGrid::~AstarGrid()
{
    
}
