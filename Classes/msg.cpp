
#include "msg.h"

NS_CROSSANY_BEGIN
msg::msg(const pos2& _pos) :pos(_pos), t(std::chrono::system_clock::time_point::clock::now()){
}


msg::~msg()
{
}

NS_CROSSANY_END