//
//  MapParse.hpp
//
//
//  Created by 志强 on 2020/3/25.
//

#ifndef MapParse_h
#define MapParse_h
#define MP() MapParse::getInstance()

#include <stdio.h>

#include "cocos2d.h"

class MapParse {

    
public:
   MapParse();
   typedef std::function<void(const char*)> JsonCallBack;
    
   static MapParse *getInstance();
   
   void loadJson(const char* jsonName);
   

};

#endif /* JsonParse_hpp */
