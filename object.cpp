#include<cstdio>
#include"object.h"
using namespace dynamic;
void Object::procedure(Object *p,std::function<bool(const Message&)> func){
	while(1){
		puts("Object::procedure");
		std::unique_lock<std::mutex> lock(p->m_mutex);
		p->m_cv.wait(lock,[&p]{return !p->empty();});
		auto msg=p->pop();
		if(msg.m_msg=="QUIT")
			break;
		func(msg);
	}
}