#include"object.h"
using namespace dynamic;
ObjectPointer Object::get_member(const std::string &id)const{
	auto it=members.find(id);
	if(it!=members.end())
		return it->second;
	for(const auto &i:parents){
		auto p=i->get_member(id);
		if(p)
			return p;
	}
	return nullptr;
}
std::pair<ObjectPointer,bool> Object::procedure(const std::string &msg,const std::vector<ObjectPointer> &args){
	std::pair<ObjectPointer,bool> p(nullptr,false);
	if(proc){
		p=proc(this,msg,args);
		if(p.second)
			return p;
	}
	for(const auto &i:parents)
		if(i){
			p=i->procedure(msg,args);
			if(p.second)
				return p;
		}
	return {nullptr,false};
}