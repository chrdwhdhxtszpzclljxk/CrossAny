#ifndef __CROSSANY_MSG_H_
#define __CROSSANY_MSG_H_
#include "macro.h"
#include "coordinate.h"
#include <stdint.h>
#include <chrono>
#include "node.h"

//NS_CROSSANY_BEGIN
namespace crossany{
	
	class msg{
	public:
		msg(const pos2&, node*, node* from);
		~msg();
		
		pos2 pos;
		std::chrono::system_clock::time_point t;
		node* target,*from;
	public:
		//static msg* create(const pos2&,node*,node* from = nullptr);
	};
}
//NS_CROSSANY_END

#endif