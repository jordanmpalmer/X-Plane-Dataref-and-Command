//
//  Hello_World_SDK_3.cpp
//  Hello-World-SDK-3
//
//  Created by Jordan Palmer on 12/23/23.
//

#include <iostream>
#include "Hello_World_SDK_3.hpp"
#include "Hello_World_SDK_3Priv.hpp"

void Hello_World_SDK_3::HelloWorld(const char * s)
{
    Hello_World_SDK_3Priv *theObj = new Hello_World_SDK_3Priv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void Hello_World_SDK_3Priv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

