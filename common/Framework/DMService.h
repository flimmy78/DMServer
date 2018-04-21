//=============================================================================
/* 
*  File: DMService.h
*
*  Author: bing
*
*  Date: 2016-09-01
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
#include "DMMessageFactory.h"
#include "DMMessage.h"
#include "DMMessageRouter.h"

//�ײ��װ��Ϣ���պ���Ϣ����
enum send_dest
{
    DM_APP,
    DM_MQ
};

class DMService
{
public:  
    DMService(){};
    virtual ~DMService(){};
    
    void init(DMMessageFactory* msg_factory);
    
    void send_message(DM_INT uid, DMMessage& msg, DM_INT dest);

    void publish_message(vector<DM_INT> uid, DMMessage& msg, DM_INT dest);

    static void message_task_callback(DMMessage& msg);
    
private:
    
    void send_app_message(ACE_HANDLE fd, DMMessage& msg);
    
    void send_mq_message(DMMessage& msg);
    
private:
    
    static DMMessageFactory* _factory;

    DMMessageRouter _router;
};

