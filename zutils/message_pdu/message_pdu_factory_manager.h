// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef MESSAGE_PDU_MESSAGE_PDU_FACTORY_MANAGER_H_
#define MESSAGE_PDU_MESSAGE_PDU_FACTORY_MANAGER_H_

#include "base/memory/singleton.h"
#include "base/hash_tables.h"
#include "message_pdu/message_pdu_factory.h"

namespace message {

class MessagePDUFactoryManager;
typedef bool (*RegisterMessagePDUFactoryFunc)(MessagePDUFactoryManager*);

//����
class MessagePDUFactoryManager {
public :
	static MessagePDUFactoryManager* GetInstance();

	//��ʼ���ӿ�
	// void Initialize();
	bool RegisterMessage(RegisterMessagePDUFactoryFunc func);

	//������Ϣ���ʹ��ڴ��������Ϣʵ�����ݣ�������߳�ͬʱ���ã�
	MessagePDU* CreateMessage(MessagePDUType message_type);
	bool GetMessageNameAndNullable(MessagePDUType message_type, const char** message_name, bool* null_able);
	const char* GetMessageName(MessagePDUType message_type);

	//ɾ����Ϣʵ�壨������߳�ͬʱ���ã�
	// void RemoveMessage( const MessagePDU* message ) ;
	
	void AddFactory( MessagePDUFactory* pFactory ) ;

private:
	friend class Singleton<MessagePDUFactoryManager>;
	friend struct DefaultSingletonTraits<MessagePDUFactoryManager>;

  typedef base::hash_map<MessagePDUType, MessagePDUFactory*> MessageFactoryMap;

	MessagePDUFactoryManager();
	virtual ~MessagePDUFactoryManager() ;

  MessageFactoryMap factories_;
	// MessagePDUFactory**	factories_ ;
	// uint16 size_;
	// uint32* message_alloc_count_;
	// base::Lock lock_;
};


}

//ÿ��Ӧ�ó���Ҫʵ�����������
bool RegisterPDUMessageFactory(message::MessagePDUFactoryManager* factory_manager);

//������
#define ADD_MESSAGEPDU_FACTORY(Message, MessageType) factory_manager->AddFactory(new message::MessagePDUFactoryTemplate<Message>(MessageType, #MessageType))

#endif
