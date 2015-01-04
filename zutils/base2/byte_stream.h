// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef BASE2_BYTE_STREAM_H_
#define BASE2_BYTE_STREAM_H_

#include "base/basictypes.h"
#include <string>

namespace base {

class ByteStream {
public:
	// Flag values
	// enum Mode { store = 0, load = 1}; // ���棨д�������س������������ڴ洢�棨�ڴ�д��������ڴ��س����ڴ������
	/**
	 * ��������д���ByteStream����,��д�������ֽ���
	 * @param dataLen ���ݵ���󳤶�
	 */
	ByteStream();
	
	/**
	 * �������ڶ�����ByteStream����,�ٶ�pBuffer����dataLen���ȵ�����
	 * �κζ�ByteStream����ĸ��Ľ�Ӱ�������pBuffer�е�����
	 * @param pBuffer ����,Ӧȷ��������dataLen����
	 * @param dataLen ���ݳ���
	 */
	ByteStream( const void* buffer, uint32 data_len );
	
	virtual ~ByteStream(void);

	//inline bool IsStoring() const    // ���棨д�ļ���ģʽ��
	//{ return m_nMode == ByteStream::store; }
	//inline bool IsLoading() const    // �س������ļ���ģʽ��
	//{ return m_nMode == ByteStream::load; }

public:
	/**
	 * ���ڲ�ָ�붨λ��ĳһλ��
	 * @param pos ���ڲ�ָ�붨λ����λ��,��λ������ڿ�ʼλ��(0)
	 * @return �ɹ����ص�ǰ�ڲ�ָ��ָ��λ��,���򷵻�-1
	 */
	int32 Seek(uint32 pos) const;

	/**
	 * �����ڲ�ָ����ָ��λ��
	 * @return ���ɹ�����-1
	 */
	uint32 Tell(void) const;

	/**
	 * ���������ֽ�
	 * @param pos Ҫ�������ֽ���
	 * @return �ɹ�����0
	 */
	int32 Skip(uint32 pos) const;

	/**
	 * �ж�operator << ��operator >>���� �Ƿ�ɹ�
	 * @return �����ɹ�,�򷵻�true
	 */
	bool Fail(void) const;

	/**
	 * ���صײ�Ļ�����ָ��
	 */
	const char* Data(void) const;
  char* MutableData(void);

	/**
	 * ���صײ�����ݵĳ���
	 */
	uint32 Length(void) const;

	/**
	 * ���������ֽ�
	 * @param pdata ��Ŷ���������,Ӧ��ȷ����ָ�������ܹ�����dataLen���ֽ�
	 * @param dataLen Ҫ�������ֽ���
	 * @return �ɹ�����0
	 */
	int32 ReadRawData(void* data, uint32 data_len) const;

	/**
	 * д�뼸���ֽ�
	 * @param pdata Ҫд�������,Ӧ��ȷ����ָ������ӵ��dataLen���ֽ�
	 * @param dataLen Ҫд����ֽ���
	 * @return �ɹ�����0
	 */
	int32 WriteRawData(const void* data, uint32 data_len);

	/**
	 * ����һ���ַ���(��'\0'��β)
	 * @param pdata ��Ŷ������ַ���,Ӧ��ȷ����ָ�������ܹ�����dataLen���ֽ�
	 * @param dataLen Ҫ�������ֽ���,������β�ַ�'\0'
	 * @return �ɹ�����0
	 */
	int32 ReadString(char* s, uint32 data_len) const;
	int32 ReadString(std::string& str) const;
	const ByteStream& operator >> (std::string& str) const;

	/**
	 * д��һ���ַ���(��'\0'��β)
	 * @param pdata Ҫд����ַ���
	 * @return �ɹ�����0
	 */
	int32 WriteString(const char* s);
	int32 WriteString(const std::string& str);
	ByteStream& operator << (const std::string& str);

	/**
	 * д��һ��bool����
	 * @param b Ҫд���bool
	 * @return ���ɹ�,��fail() == true
	 */
	ByteStream& operator << (bool b);

	/**
	 * д��һ��char��
	 * @param ch Ҫд���ch
	 * @return ���ɹ�,��fail() == true
	 */
	ByteStream& operator << (char ch);

	/**
	 * д��һ��uint8��
	 * @param ch Ҫд���uint8
	 * @return ���ɹ�,��fail() == true
	 */
	ByteStream& operator << (uint8 ch);

	/**
	 * д��һ��int16��
	 * @param s Ҫд���int16
	 * @return ���ɹ�,��fail() == true
	 */
	ByteStream& operator << (int16 s);

	/**
	 * д��һ��uint16��
	 * @param s Ҫд���uint16
	 * @return ���ɹ�,��fail() == true
	 */
	ByteStream& operator << (uint16 s);

	/**
	 * д��һ��int32��
	 * @param l Ҫд���int32
	 * @return ���ɹ�,��fail() == true
	 */
	ByteStream& operator << (int32 l);

	/**
	 * д��һ��uint32��
	 * @param l Ҫд���uint32
	 * @return ���ɹ�,��fail() == true
	 */
	ByteStream& operator << (uint32 l);

	/**
	 * д��һ��int32
	 * @param l ��Ŷ�����int32
	 * @return ���ɹ�,��fail() == true
	 */
	const ByteStream& operator >> (bool& b) const;

	/**
	 * ����һ��char
	 * @param ch ��Ŷ�����char
	 * @return ���ɹ�,��fail() == true
	 */
	const ByteStream& operator >> (char& ch) const;

	/**
	 * ����һ��uint8
	 * @param ch ��Ŷ�����uint8
	 * @return ���ɹ�,��fail() == true
	 */
	const ByteStream& operator >> (uint8& ch) const;

	/**
	 * ����һ��int16
	 * @param s ��Ŷ�����int16
	 * @return ���ɹ�,��fail() == true
	 */
	const ByteStream& operator >> (int16& s) const;

	/**
	 * ����һ��uint16
	 * @param s ��Ŷ�����uint16
	 * @return ���ɹ�,��fail() == true
	 */
	const ByteStream& operator >> (uint16& s) const;

	/**
	 * ����һ��int32
	 * @param l ��Ŷ�����int32
	 * @return ���ɹ�,��fail() == true
	 */
	const ByteStream& operator >> (int32& l) const;

	/**
	 * ����һ��int32
	 * @param l ��Ŷ�����int32
	 * @return ���ɹ�,��fail() == true
	 */
	const ByteStream& operator >> (uint32& l) const;

	operator bool () const {
		return 0 == failed_;
	}
	bool operator!() const {
		return 0 != failed_;
	}


protected:
	/** ��ֹ����������� */
	ByteStream( const ByteStream& s );
	/** ��ֹ��ֵ���� */
	ByteStream& operator= ( const ByteStream& s );

protected:
	virtual void* Alloc(uint32 dwNewLen);
	virtual void  Free();

protected:
	char*			buffer_;	/**< ʵ�����ڶ�д�Ļ����� */
	bool			is_new_;	/**< buffer_�Ƿ����ö�̬����� */
	uint32	max_len_;	/**< ����������󳤶� */
	uint32	data_len_;	/**< �������е����ݳ��� */
	mutable  uint32	current_pos_;	/**< �������ж�д�ĵ�ǰλ�� */
	mutable  uint32	failed_;	/**< ָʾ��д�����Ƿ�ɹ� */
	//int m_nMode;
};

} // namespace base


#endif
	
