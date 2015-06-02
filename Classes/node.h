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


	class CROSSANY_API node{
	public:
	typedef std::list < node* > nodelist; // 本z-order的所有node列表
	typedef std::vector < nodelist* > nodez; // 不同层次z-order的列表的集合
		node();
		virtual ~node();
		virtual void customdraw(){};
		virtual void draw(){
			customdraw();
			node::nodez::iterator z; node::nodelist::iterator l;
			for (z = mnodes.begin(); z != mnodes.end(); z++){
				node::nodelist* nlist = (*z);
				for (l = nlist->begin(); l != nlist->end(); l++){
					(*l)->draw();
				}
			}
		};
		virtual void customresize(const size& _s){ msize = _s; };
		virtual void resize(const size& _s){
			customresize(_s);
			node::nodez::iterator z; node::nodelist::iterator l;
			for (z = mnodes.begin(); z != mnodes.end(); z++){
				node::nodelist* nlist = (*z);
				for (l = nlist->begin(); l != nlist->end(); l++){
					(*l)->resize(_s);
				}
			}
		}
		virtual void addChild(node* _node, int32_t _z = 0){
			mnodes.resize(_z + 1);
			if (mnodes[_z] == nullptr) mnodes[_z] = new nodelist();
			mnodes[_z]->push_back(_node);
		}


	protected:
		size msize;
	private:
		nodez mnodes;
		
	};

}
//NS_CROSSANY_END

#endif