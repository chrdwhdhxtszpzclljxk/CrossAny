#ifndef __CROSSANY_NODE_H_
#define __CROSSANY_NODE_H_
#include "macro.h"
#include <list>
#include <vector>
#include <stdint.h>
#include "coordinate.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#endif
//NS_CROSSANY_BEGIN
#pragma warning(disable:4251)
namespace crossany{

	class msg;
	class CROSSANY_API node{
	public:
		typedef std::list < node* > nodelist; // 本z-order的所有node列表
		typedef std::vector < nodelist* > nodez; // 不同层次z-order的列表的集合
		node();
		node(node* parent);
		virtual ~node();
		virtual void customdraw(){};
		virtual void draw();
		virtual void customresize(const size& _s);
		virtual void resize(const size& _s);
		virtual void addChild(node* _node, int32_t _z = 0);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		virtual int32_t customevent(const UINT&, const pos2&);
		virtual int32_t onevent(const UINT&, const WPARAM&, const LPARAM&);
#endif
		virtual void ontouchbegin(const msg*){};
		virtual void ontouchend(const msg*){};
		virtual void ontouchmove(const msg*){};
	protected:
		rect mrc;
		bool mtouchbegin;
	private:
		nodez mnodes;
		X_VARP(node*, parent);


	};

}
//NS_CROSSANY_END

#endif