//
//  MapParse.cpp
//
//
//  Created by 志强 on 2020/3/25.
//

#include "MapParse.h"
#include "cocostudio/CocoStudio.h"
#include "GameMap.hpp"
#include <iostream>


MapParse::MapParse(){}

USING_NS_CC;

static MapParse *s_pInstance = NULL; // pointer to singleton
MapParse* MapParse::getInstance()
{
    if (s_pInstance == NULL)
    {
        s_pInstance = new MapParse();
    }

    return s_pInstance;
}
void MapParse::loadJson(const char* jsonName)
{
    rapidjson::Document _doc;
//    bool bRet = false;
    ssize_t size = 0;
    unsigned char *pBytes = NULL;
    do {
        pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(jsonName, "r", &size);
        CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
        std::string load_str((const char*)pBytes, size);
        CC_SAFE_DELETE_ARRAY(pBytes);
        _doc.Parse<0>(load_str.c_str());
        CC_BREAK_IF(_doc.HasParseError());
        //生成json文档对像
 
        if(!_doc.IsObject())
            return;
            
        //是否有此成员
        if(_doc.HasMember("grids") && _doc.HasMember("gridw") && _doc.HasMember("gridh") && _doc.HasMember("slicew") && _doc.HasMember("sliceh") && _doc.HasMember("pixwidth") && _doc.HasMember("pixheight")&& _doc.HasMember("cols")&& _doc.HasMember("rows"))
        {
            MapInfo*mapinfo = new MapInfo();
            std::vector<int> vecs;
            for(int i = 0;i< _doc["grids"].Size();i++)
            {
                vecs.push_back(_doc["grids"][i].GetInt());
            }
            mapinfo->grids = vecs;
            mapinfo->gridw = _doc["gridw"].GetInt();
            mapinfo->gridh = _doc["gridh"].GetInt();
            mapinfo->slicew = _doc["slicew"].GetInt();
            mapinfo->sliceh = _doc["sliceh"].GetInt();
            mapinfo->pixwidth = _doc["pixwidth"].GetInt();
            mapinfo->pixheight = _doc["pixheight"].GetInt();
            mapinfo->cols = _doc["cols"].GetInt();
            mapinfo->rows = _doc["rows"].GetInt();
            GM()->init(mapinfo);
        }
           
 
//        // 通过[]取成员值,再根据需要转为array,int,double,string
//        const rapidjson::Value &pArray = _doc["standKey"];
//
//        //是否是数组
//        if(!pArray.IsArray())
//            return;
//        for (rapidjson::SizeType i = 0; i < pArray.Size(); i++)
//        {
//            const rapidjson::Value &p = pArray[i];
//            if(p.HasMember("entity"))
//            {
//                const rapidjson::Value &valueEnt = p["entity"];
//                FirstCfg *val_vec = new FirstCfg();
//                if(valueEnt.HasMember("TapOpposite") && valueEnt.HasMember("Interval") && valueEnt.HasMember("BallNum"))
//                {
//
//                    const rapidjson::Value &tapOpposite = valueEnt["TapOpposite"];
//                    int tapOp = tapOpposite.GetInt();      //得到int值
//                    val_vec->TapOpposite = tapOp;
//                    tapOpposite.get
//
//                    const rapidjson::Value &interval = valueEnt["Interval"];
//                    float inter = interval.GetDouble();  //得到float,double值
//                    val_vec->Interval = inter;
//
//                    const rapidjson::Value &ballNum = valueEnt["BallNum"];
//                    int ball = ballNum.GetInt();      //得到int值
//                    val_vec->BallNum = ball;
//                }
//                ConfigCtl::getInstance()->firstCfg.pushBack(val_vec);
//                val_vec->release();
//            }
//            else
//            {
//                return;
//            }
//        }
//        const char*str = "1";
//        callBack(str);
//        bRet = true;
 
    } while (0);
}


