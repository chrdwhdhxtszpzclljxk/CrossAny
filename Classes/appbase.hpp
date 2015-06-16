bool appbase::painted;
size appbase::msize;
node* appbase::mfocus = nullptr;
node::nodelist appbase::mtimer;

void appbase::addChild(node* _node, int32_t z ){
	_node->setparent(&orz);
	orz.addChild(_node, z);
}

void appbase::timeradd(const node* _node){
	node::nodelist::iterator iter = std::find(mtimer.begin(), mtimer.end(), _node);
	if (iter == mtimer.end()) mtimer.push_back((node*)_node);
	if (mtimer.size() > 0){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		SetTimer(appbase::hWnd, 3, 100, nullptr);
#endif
	}
}

void appbase::timerremove(const node* _node){
	node::nodelist::iterator iter = std::find(mtimer.begin(), mtimer.end(), _node);
	if (iter != mtimer.end()) mtimer.erase(iter);
	if (mtimer.size() <= 0){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		KillTimer(appbase::hWnd, 3);
#endif
	}
}

void appbase::ontimer(){
	node::nodelist::iterator iter;
	for (iter = mtimer.begin(); iter != mtimer.end(); iter++){
		(*iter)->ontimer();
	}
}