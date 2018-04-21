//=============================================================================
/* 
*  File: DMMessage.h
*
*  Author: bing
*
*  Date: 2016-08-12
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

/*-------------------------------------------------------------------------------
            msg head:
            --------------------------------------------------
            |       message uid      |      body length      |
            --------------------------------------------------
            |       message cmd      |        reserved       |
            --------------------------------------------------

---------------------------------------------------------------------------------*/

enum msg_type   //����ά����Ϣ 1000-1999
{
    ADD_PROXY_MSG = 1001,
    RMV_PROXY_MSG = 1002,
    STOP_SERVER   = 1003,
    HEARTBEAT_MSG = 1004,
    SYSTEM_MSG = 1999
};

enum DataSize
{
    HEAD_BIT_LEN = 128,
    HEAD_CHAR_LEN = 16,
    CHAR_BIT_LEN = 8
};


class DMMessageHead
{
public:
	DMMessageHead():msg_uid(0),msg_cmd(0),length(0),reserved(0){};
	DM_UINT32 msg_uid;
	DM_UINT32 msg_cmd;
	DM_UINT32 length;
	DM_UINT32 reserved;
    
    DMMessageHead& operator=(DMMessageHead other)
    {
        this->msg_uid = other.msg_uid;
        this->msg_cmd = other.msg_cmd;
        this->length = other.length;
        this->reserved = other.reserved;
        
        return *this;
    }
};

class DMMessage
{
public:
   	DMMessage()
	{
		body = nullptr;
	}
    
    ~DMMessage()
	{
		release_body_size();
	}
    
    void require_body_size(DM_UINT16 size)
    {
        body = new char[size];
    }
    
    void release_body_size()
    {
        delete[] body; 
    }
    
    DMMessage& operator=(DMMessage other)
    {
        this->head = other.head;
        this->body = other.body;
        return *this;
    }
    
	DMMessageHead head;
	DM_CHAR* body;
}; 

typedef void (*MESSAGE_CALLBACK_HANDLE)(DMMessage&);

