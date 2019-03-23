#ifndef _PRIMITIVE_DATA_H_
#define _PRIMITIVE_DATA_H_
#include<string>
#include<cstdint>
#include"object.h"
namespace dynamic{
	template<typename T>
	struct PrimitiveData:public Object{
		static ObjectPointer create(const std::string &type,const std::function<std::pair<ObjectPointer,bool>(const ObjectPointer&,const std::string&,const std::vector<ObjectPointer>&)> &proc,const T &data=T()){
			ObjectPointer p;
			p.New<PrimitiveData>();
			p->proc=proc;
			p.operator-><PrimitiveData>()->type=type;
			p.operator-><PrimitiveData>()->data=data;
			return p;
		}
		static ObjectPointer create(std::string &&type,std::function<std::pair<ObjectPointer,bool>(const ObjectPointer&,const std::string&,const std::vector<ObjectPointer>&)> &&proc,T &&data=T()){
			ObjectPointer p;
			p.New<PrimitiveData>();
			p->proc=proc;
			p.operator-><PrimitiveData>()->type=type;
			p.operator-><PrimitiveData>()->data=data;
			return p;
		}
		std::string type;
		T data;
		PrimitiveData()=default;
		PrimitiveData(const T &d,const std::string &t):data(d),type(t){}
		PrimitiveData(T &&d,std::string &&t):data(d),type(t){}
	};
	ObjectPointer integer(intmax_t=0);
}
#endif