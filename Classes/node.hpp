#include "node.h"
#include "appbase.h"
#include "log.h"

NS_CROSSANY_BEGIN

//CROSSANY_API int32_t node::mh = 0;

node::node() : mtouchbegin(false), mparent(nullptr), mfocus(false),mfloat(left), mfill(false), mborder(1),mwt(fillp),mht(fillp){
}

node::node(node* _p) : mtouchbegin(false), mparent(_p), mfocus(false),mfloat(left), mfill(false), mborder(1), mwt(fillp), mht(fillp) {
}

node::~node(){ }


void node::adj_w_h(int32_t& w, int32_t& h) {
	if (w < 4)
		w = 4;
	if (w < 8)
		w = 8;
	else if (w < 16)
		w = 16;
	else if (w < 32)
		w = 32;
	else if (w < 64)
		w = 64;
	else if (w < 128)
		w = 128;
	else if (w < 256)
		w = 256;
	else if (w < 512)
		w = 512;
	else if (w < 1024)
		w = 1024;

	if (h < 4)
		h = 4;
	if (h < 8)
		h = 8;
	else if (h < 16)
		h = 16;
	else if (h < 32)
		h = 32;
	else if (h < 64)
		h = 64;
	else if (h < 128)
		h = 128;
	else if (h < 256)
		h = 256;
	else if (h < 512)
		h = 512;
	else if (h < 1024)
		h = 1024;
}


void node::customdraw() {
	//glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	if (mborder > 0) {
		glColor3f(0.0, 0.0, 1.0);
		glPointSize(5);
		glBegin(GL_LINE_LOOP);
		glVertex2d(mrc.getx0() - 1, mrc.gety0() - 1);
		glVertex2d(mrc.getx1() - 1, mrc.gety1() + 1);
		glVertex2d(mrc.getx2() + 1, mrc.gety2() + 1);
		glVertex2d(mrc.getx3() + 1, mrc.gety3() - 1);
		//log::otprint("(%f,%f),(%f,%f),(%f,%f),(%f,%f)", mrc.getx0(), mrc.gety0(), mrc.getx1(), mrc.gety1(),
		//	mrc.getx2(), mrc.gety2(), mrc.getx3(), mrc.gety3());
		glEnd();
	}
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
	 //mrc.setsize(_s);
	 pos2 pos = mpos;
	 pos.sety(appbase::geth() - mpos.gety() - msize.geth());
	 if(mwt == fillp && mht == fillp)	 msize = _s;
	 mrc.set(pos, msize);
	 mrcr.set(mpos, msize);
 };

 void node::resize(const size& _s){
	customresize(_s);
	node::nodez::iterator z; node::nodelist::iterator l;
	for (z = mnodes.begin(); z != mnodes.end(); z++){
		node::nodelist* nlist = (*z);
		node::nodelist fl, fr,ff; // fl: float to left. fr: float to right, ff; fill parent
		for (l = nlist->begin(); l != nlist->end(); l++){
			node* p = *l;
			if (p->mfloat == left) fl.push_back(p);
			else fr.push_back(p);
			if (p->mfill) ff.push_back(p);
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