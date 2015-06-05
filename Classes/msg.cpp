
#include "msg.h"

NS_CROSSANY_BEGIN
msg::msg(const pos2& _pos,node* _t,node* _f):
pos(_pos), t(std::chrono::system_clock::time_point::clock::now()),
target(_t),from(_f){
}
msg::~msg()
{
}
/*
msg* msg::create(const pos2& _p, node* _t, node* _f){
	msg* ret = new msg(_p, _t, _f);
	return ret;
}
*/
NS_CROSSANY_END