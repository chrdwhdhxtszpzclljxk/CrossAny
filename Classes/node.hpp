#include "node.h"
#include "appbase.h"
#include "log.h"

NS_CROSSANY_BEGIN

node::node() : mtouchbegin(false), mparent(nullptr), mfocus(false),mfloat(left), mfill(false){
}

node::node(node* _p) : mtouchbegin(false), mparent(_p), mfocus(false),mfloat(left), mfill(false) {
}

node::~node(){ }

void node::customdraw() {
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
}

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
 void node::customresize(const size& _s){ 
	 mrc.setsize(_s);
 };

 void node::resize(const size& _s){
	customresize(_s);
	node::nodez::iterator z; node::nodelist::iterator l;
	for (z = mnodes.begin(); z != mnodes.end(); z++){
		/*
		node::nodelist* nlist = (*z);
		node::nodelist fl, fr,ff; // fl: float to left. fr: float to right, ff; fill parent
		for (l = nlist->begin(); l != nlist->end(); l++){
			node* p = *l;
			if (p->mfloat == left) fl.push_back(p);
			else fr.push_back(p);
			if (p->mfill) ff.push_back(p);
			//(*l)->resize(_s);
		}
		*/
	}
}
 void node::addChild(node* _node, int32_t _z){
	 _node->setparent(this);
	mnodes.resize(_z + 1);
	if (mnodes[_z] == nullptr) mnodes[_z] = new nodelist();
	mnodes[_z]->push_back(_node);
 }

 int32_t node::ontouchbegin(const msg*){
	 if (appbase::mfocus != this){
		 if (appbase::mfocus != nullptr) appbase::mfocus->onsetfocus(false);
		 appbase::mfocus = this;
		 appbase::mfocus->onsetfocus(true);
	 }
	 return 1;
 }

 int32_t node::ontouchend(const msg*){
	 if (mtouchbegin){
		 //crossany::log("ok...");
		 crossany::log::otprint("test");
	 }
	 mtouchbegin = false;
	 return 1;
 }

 void node::onsetfocus(const bool& _focus){
	 mfocus = _focus;
	 appbase::updateui();
 }

 int32_t node::ontouchmove(const msg*){
	 return 1;
 }

 NS_CROSSANY_END