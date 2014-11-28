// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef DB_CONN_POOL_MANAGER_H_
#define DB_CONN_POOL_MANAGER_H_

//#define USE_DATABASE_DLL

#include <string>
#include <vector>

#include "base/synchronization/lock.h"
#include "base/logging.h"

#ifdef USE_DATABASE_DLL
#include "base2/dyn_lib.h"
#endif

#include "db/base_database.h"


namespace db {

class CdbConnPoolManager {
public:
  CdbConnPoolManager() :
    conned_pointer_(0),
#ifdef USE_DATABASE_DLL
    dyn_lib_(NULL),
#endif
    auto_commit_(true) {
  }
  
  ~CdbConnPoolManager();
  
  // ��������mysql����
	//size_t Initialize(const std::string& conn_string, int min_conn_count=2, int max_conn_count=5);
	size_t Initialize(const base::DBAddrInfo& db_addr, bool auto_commit = true);
	// С��ʹ�ã��������е����ӻ����Ժ����ִ��
  void Shutdown();
  
	BaseDatabase* GetFreeConnection();
  void SetFreeConnection(BaseDatabase* conn);
  
  const std::string& GetDbType() const {
    return db_addr_.db_type;
  }
  
private:
  friend class ScopedPtr_DatabaseConnection;
  struct DatabaseConnection {
    
    enum DBConnState {
      kDBConnState_Null = 0,    // ��Ϊδ֪ԭ����dbδ����
      kDBConnState_Created = 1,  // �Ѵ�����δ���ӵ����ݿ�
      kDBConnState_Idle = 2,    // �����ӿ���
      kDBConnState_Busy = 3,    // �����������ṩ����
    };
    
    DatabaseConnection() :
      state(kDBConnState_Null),
      conn(NULL) {
    }
    
    // �Ƿ����
    DBConnState state;
    // is_idle;
    BaseDatabase* conn;
  };
  
  //std::string conn_string_;
  base::DBAddrInfo db_addr_;

  // ͬ��
  base::Lock mutex_;
  std::vector<DatabaseConnection> conn_pool_;
  
  // ��ǰ�Ѿ�������������
  int conned_pointer_;
  
  // std::string db_type_;
  
#ifdef USE_DATABASE_DLL
  base::DynLib* dyn_lib_;
#endif

  bool auto_commit_;
};

class ScopedPtr_DatabaseConnection {
public:
  explicit ScopedPtr_DatabaseConnection(CdbConnPoolManager* db) {
    DCHECK(db);
    db_ = db;
    db_conn_ = db_->GetFreeConnection();
  }
  
  ~ScopedPtr_DatabaseConnection() {
    release();
  }
  
  BaseDatabase& operator*() const {
    DCHECK(db_);
    if (db_conn_==NULL) {
      db_conn_ = db_->GetFreeConnection();
    }
    return *(db_conn_);
  }
  
  BaseDatabase* operator->() const {
    DCHECK(db_);
    if (db_conn_==NULL) {
      db_conn_ = db_->GetFreeConnection();
    }
    return db_conn_;
  }
  
  BaseDatabase* get() const {
    DCHECK(db_);
    if (db_conn_==NULL) {
      db_conn_ = db_->GetFreeConnection();
    }
    return db_conn_;
  }
  
  operator bool() const {
    return db_conn_ !=0;
  }

  bool operator! () const {
    return db_conn_ == 0;
  }

  void release() {
    DCHECK(db_);
    if (db_conn_) {
      db_->SetFreeConnection(db_conn_);
      db_conn_ = NULL;
    }
  }
  
private:
  CdbConnPoolManager* db_;
  mutable BaseDatabase* db_conn_;
  
  DISALLOW_COPY_AND_ASSIGN(ScopedPtr_DatabaseConnection);
};

}

#endif /* defined(DB_CONN_POOL_MANAGER_H_) */
