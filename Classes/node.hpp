
node::node() : mtouchbegin(false){ }
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
	mnodes.resize(_z + 1);
	if (mnodes[_z] == nullptr) mnodes[_z] = new nodelist();
	mnodes[_z]->push_back(_node);
}