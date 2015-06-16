#include "node.h"
#include "appbase.h"
#include "log.h"

NS_CROSSANY_BEGIN

node::node() : mtouchbegin(false), mparent(nullptr), mfocus(false){

}

node::node(node* _p) : mtouchbegin(false), mparent(_p), mfocus(false){
}

node::~node(){ }

void node::draw(){
	customdraw();
	node::nodez::iterator z; node::nodelist::iterator l;
	for (z = mnodes.begin(); z != mnodes.end(); z++){
		node::nodelist* nlist = (*z);
		for (l = nlist->begin(); l != nlist->end(); l++){
			(*l)->draw();
		}
	}
};
 void node::customresize(const size& _s){ /*msize = _s;*/ };
 void node::resize(const size& _s){
	customresize(_s);
	node::nodez::iterator z; node::nodelist::iterator l;
	for (z = mnodes.begin(); z != mnodes.end(); z++){
		node::nodelist* nlist = (*z);
		for (l = nlist->begin(); l != nlist->end(); l++){
			(*l)->resize(_s);
		}
	}
}
 void node::addChild(node* _node, int32_t _z){
	 _node->setparent(this);
	mnodes.resize(_z + 1);
	if (mnodes[_z] == nullptr) mnodes[_z] = new nodelist();
	mnodes[_z]->push_back(_node);
 }

 void node::ontouchbegin(const msg*){
	 if (appbase::mfocus != this){
		 if (appbase::mfocus != nullptr) appbase::mfocus->onsetfocus(false);
		 appbase::mfocus = this;
		 appbase::mfocus->onsetfocus(true);
	 }
 }

 void node::ontouchend(const msg*){
	 if (mtouchbegin){
		 //crossany::log("ok...");
		 crossany::log::otprint("test");
	 }
	 mtouchbegin = false;
 }

 void node::onsetfocus(const bool& _focus){
	 mfocus = _focus;
	 appbase::updateui();
 }

 void node::ontouchmove(const msg*){
 }

 NS_CROSSANY_END