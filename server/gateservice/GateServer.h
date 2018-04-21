//=============================================================================
/* 
*  File: GateServer.h
*
*  Author: bing
*
*  Date: 2016-09-20
*
*  Version: v2.0
*
*  Github/Mail: https://github.com/binchen-china    <563853086@qq.com>
*
*  Note:
*/
//=============================================================================

#pragma once

#include "DMaker.h"
#include "DMServer.h"
#include "GateService.h"
#include "GateMessageFactory.h"

class GateServer : public DMServer <GateService, GateMessageFactory>
{
public:
    
};
