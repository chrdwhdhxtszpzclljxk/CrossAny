#include "tls.h"

namespace xiny120 {
	const int64_t _tls_len = 1024 * 1024 * 5;
	__declspec(thread)	char* __tls0 = NULL, *__tls1 = NULL;

	/* 只能在本线程中在一个流程中使用，不能保存到下次使用！类似于 gmtime*/
	char* _tlsget0(){ if (__tls0 == NULL) __tls0 = new char[_tls_len]; return __tls0; }
	void _tlsfree0(){ if (__tls0 != NULL) delete[] __tls0; }
	int64_t _tlscap0(int64_t size){ return _tls_len / size; } // 容纳数据的个数
	char* _tlsget1(){ if (__tls1 == NULL) __tls1 = new char[_tls_len]; return __tls1; }
	void _tlsfree1(){ if (__tls1 != NULL) delete[] __tls1; }
	int64_t _tlscap1(int64_t size){ return _tls_len / size; } // 容纳数据的个数
}