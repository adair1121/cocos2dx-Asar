//
//  GameMap.hpp
//  FindPathTest-mobile
//
//  Created by 志强 on 2020/6/13.
//

#ifndef GameMap_hpp
#define GameMap_hpp
#include "AstarGrid.hpp"
#define GM() GameMap::getInstance()

struct MapInfo{
    std::vector<int> grids;
    int gridw;
    int gridh;
    int slicew;
    int sliceh;
    int pixwidth;
    int pixheight;
    int cols;
    int rows;
};
struct GridObj{
    float row;
    float col;
};
class GameMap {
public:
    GameMap();
    static GameMap *getInstance();
    /**当前地图id*/
    int levelMapId;
    /**当前地图格子大小*/
    int CELL_SIZE;
    /**当前地图最大宽度*/
    int MAX_WIDTH;
    /**当前地图最大高度*/
    int MAX_HEIGHT;
    int COL;
    int ROW;
    /**格子数据*/
    bool buildTouch;
    std::vector<std::vector<int>> grids;
    std::vector<GridObj*> runGrids;
    AstarGrid*astarGrid;
    std::vector<GridObj*> monGrids;
    std::vector<GridObj*> roleBirthGrids;
public:
    void init(MapInfo*data)
    {
        std::vector<int> gds = data->grids;
        grids.clear();
        runGrids.clear();
        monGrids.clear();
        roleBirthGrids.clear();
        CELL_SIZE = data->gridw;
        MAX_WIDTH = data->pixwidth;
        MAX_HEIGHT = data->pixheight;
        COL = data->cols;
        ROW = data->rows;
        astarGrid = new AstarGrid(data->cols,data->rows);
        
        for(int i = 0;i<data->rows;i++)
        {
            std::vector<int> vecs;
            for(int j = 0;j<data->cols;j++)
            {
                int num = gds.at(i*data->cols+j);
                vecs.push_back(num);
                GridObj*obj = new GridObj();
                obj->row = i;
                obj->col = j;
                if(num == 1){//可行走
                    runGrids.push_back(obj);
                }else if(num == 3){//怪物出生点
                    monGrids.push_back(obj);
                }else if(num == 4){//人物出生点
                    roleBirthGrids.push_back(obj);
                }else if(num == 0){//不可行走区域
                    astarGrid->setWalkable(j, i, false);
                }
            }
            grids.push_back(vecs);
        }
    }
    GridObj*point2Grid(int px,int py)
    {
        //像数转格子坐标
        int gridXnum = (px/CELL_SIZE)>>0;
        int gridYnum = (py/CELL_SIZE)>>0;
        GridObj*obj = new GridObj();
        obj->row = gridYnum;
        obj->col = gridXnum;
        return obj;
    }
    GridObj*grid2point(int gx,int gy)
    {
        float x = float(gx)*float(CELL_SIZE);
        float y = float(gy)*float(CELL_SIZE);
        GridObj*obj = new GridObj();
        obj->row = y;
        obj->col = x;
        return obj;
    }
    GridObj*grid2MapBlock(int gx,int gy)
    {
        GridObj*xy = grid2point(gx, gy);
        
        int x = ceil(xy->col / 256);
        int y = ceil(xy->row / 256);
        GridObj*obj = new GridObj();
        obj->row = y;
        obj->col = x;
        return obj;
    }
    bool walkable(int x,int y)
    {
        //判断是够处于阻挡点
        if(grids.size()-1 >= x && grids.at(x).size() - 1 >= y)
        {
            int gridnum = grids.at(x).at(y);
            if(gridnum == 1)
            {
                return true;
            }
            return false;
        }
        return false;
    }
};

#endif /* GameMap_hpp */
