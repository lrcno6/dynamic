#include"object.h"
using namespace dynamic;
std::pair<ObjectPointer,bool> Object::procedure(const std::string &msg,const std::vector<ObjectPointer> &args){
	std::pair<ObjectPointer,bool> p(ObjectPointer(),false);
	if(proc)
		p=proc(this,msg,args);
	if(p.second)
		return p;
	for(const auto &i:parents){
		p=i->procedure(msg,args);
		if(p.second)
			return p;
	}
	return {ObjectPointer(),false};
}