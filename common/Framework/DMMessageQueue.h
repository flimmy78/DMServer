//=============================================================================
/* 
*  File: DMMessageQueue.h
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
//#include "DMDispatcher.h"
#include "DMMessageEvent.h"

class DMDispatcher;
//rabitmq���������Ӵ�����service��dispatchʹ��
class DMMessageQueue
{
public:
	static DMMessageQueue* instance()
	{
		if (nullptr == _instance)
		{
			_instance = new DMMessageQueue;
		}
		return _instance;
	}
    //�������ó��Դ������ж��У�ȡ��svrid���

    void register_dispatcher(DMDispatcher* pDispatcher){_dispatcher = pDispatcher;}

    DM_INT32 init();

	void publish(const string &exchange, const string &routingKey, const DM_CHAR *message, size_t size);

    DM_INT32 getQueueMsgCount(string queueName);

    void runEvents();

	void destroy();

protected:
	DMMessageQueue(){};
	virtual ~DMMessageQueue();
    
private:
    DM_UINT8 _service_id;
    
	DMMessageEvent* _handle;

    DMDispatcher* _dispatcher;
    
	AMQP::TcpChannel* _channel;
    
	AMQP::TcpConnection* _connection;
    
	static DMMessageQueue *_instance;
};

