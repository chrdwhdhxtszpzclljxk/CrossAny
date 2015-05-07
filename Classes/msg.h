#ifndef __CROSSANY_NODE_H_
#define __CROSSANY_NODE_H_
#include "macro.h"
#include "coordinate.h"
#include <stdint.h>
#include <chrono>

//NS_CROSSANY_BEGIN
namespace crossany{

	class CROSSANY_API msg{
	private:
		msg(const pos2&);
		~msg();
		
		pos2 pos;
		std::chrono::system_clock::time_point t;
	public:
		static msg* create(const pos2&);
	};
}
//NS_CROSSANY_END

#endif