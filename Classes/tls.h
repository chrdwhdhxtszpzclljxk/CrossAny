#ifndef _TSERVER2_TLS_H_
#define _TSERVER2_TLS_H_
#include <stdio.h>
#include <stdint.h>

namespace xiny120 {
	// ֻ���ڱ��߳�����һ��������ʹ�ã����ܱ��浽�´�ʹ�ã������� gmtime
	char* _tlsget0(); void _tlsfree0(); int64_t _tlscap0(int64_t size);
	char* _tlsget1(); void _tlsfree1(); int64_t _tlscap1(int64_t size);
}

#endif