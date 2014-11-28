// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef DB_MYSQL_MYSQL_DATABASE_H_
#define DB_MYSQL_MYSQL_DATABASE_H_

#include "db/base_database.h"

#ifdef OS_WIN
#include <winsock2.h>
#endif

#include <mysql.h>

namespace db {
  
class MySQLDatabase :
  public BaseDatabase {
public:
	MySQLDatabase();
	virtual ~MySQLDatabase();
  
  virtual base::StringPiece GetDatabaseName() const {
    return "mysql";
  }
    
  //virtual bool Open(const base::StringPiece& conn_string);
  virtual void CloseDb();
    
	// ��ѯ���
	virtual QueryAnswer* Query(const base::StringPiece& q_str);
  
	// ����
	// ����INSERT ���������� ID
	virtual uint64 ExecuteInsertID(const base::StringPiece& q_str);
  
	// ����͸���
	virtual int Execute(const base::StringPiece& q_str);

  virtual uint64 GetNextID(const char* table_name, const char* field_name);
    
	virtual bool BeginTransaction();
	virtual bool CommitTransaction();
	virtual bool RollbackTransaction();
  
  virtual int GetLastError();

  static void DatabaseServerCallback(void* callback_data, uint8 msg, uint32 handle, void* pParam);

protected:
  // static void 
  // this callback will be replaced by imconn_callback() in OnConnect()
//   {
//     if (msg == NETLIB_MSG_CONNECT)
//     {
//       CLoginConn* pConn = new CLoginConn();
//       pConn->OnConnect2(handle, LOGIN_CONN_TYPE_MSG_SERV);
//     }
//     else
//     {
//       log("!!!error msg: %d\n", msg);
//     }
//   }

  bool CheckConnection();
  virtual bool BuildConnection();
	virtual bool Ping();
  
private:
  int SafeQuery(const base::StringPiece& q_str, int* err);
    
  st_mysql* my_;
  st_mysql mysql_;

  //int last_error_;
};

}

#endif /* defined(DB_MYSQL_MYSQL_DATABASE_H_) */
