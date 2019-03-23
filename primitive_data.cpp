#include<iostream>
#include"primitive_data.h"
using namespace dynamic;
ObjectPointer dynamic::integer(intmax_t x){
	return PrimitiveData<intmax_t>::create("integer",[](const ObjectPointer &pthis,const std::string &msg,const std::vector<ObjectPointer> &args)->std::pair<ObjectPointer,bool>{
		auto translate=[](const ObjectPointer &p){
			return p.operator-><PrimitiveData<intmax_t>>();
		};
		auto p=translate(pthis);
		if(msg=="assign"){
			if(args.size()>0)
				p->data=translate(args[0])->data;
			return {pthis,true};
		}
		if(msg=="add"){
			intmax_t sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum+=p->data;
			}
			return {integer(sum),true};
		}
		if(msg=="sub"){
			intmax_t sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum-=p->data;
			}
			return {integer(sum),true};
		}
		if(msg=="mul"){
			intmax_t sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum*=p->data;
			}
			return {integer(sum),true};
		}
		if(msg=="div"){
			intmax_t sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum/=p->data;
			}
			return {integer(sum),true};
		}
		if(msg=="mod"){
			intmax_t sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum%=p->data;
			}
			return {integer(sum),true};
		}
		if(msg=="inc" || msg=="add_eq"){
			auto &sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum+=p->data;
			}
			return {pthis,true};
		}
		if(msg=="dec" || msg=="sub_eq"){
			auto &sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum-=p->data;
			}
			return {pthis,true};
		}
		if(msg=="mul_eq"){
			intmax_t &sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum*=p->data;
			}
			return {pthis,true};
		}
		if(msg=="div_eq"){
			intmax_t &sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum/=p->data;
			}
			return {pthis,true};
		}
		if(msg=="mod_eq"){
			intmax_t &sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum%=p->data;
			}
			return {pthis,true};
		}
		if(msg=="minus")
			return {integer(-p->data),true};
		if(msg=="and"){
			intmax_t sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum&=p->data;
			}
			return {integer(sum),true};
		}
		if(msg=="or"){
			intmax_t sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum|=p->data;
			}
			return {integer(sum),true};
		}
		if(msg=="xor"){
			intmax_t sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum^=p->data;
			}
			return {integer(sum),true};
		}
		if(msg=="not")
			return {integer(~p->data),true};
		if(msg=="and_eq"){
			intmax_t &sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum&=p->data;
			}
			return {pthis,true};
		}
		if(msg=="or_eq"){
			intmax_t &sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum|=p->data;
			}
			return {pthis,true};
		}
		if(msg=="xor_eq"){
			intmax_t &sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum^=p->data;
			}
			return {pthis,true};
		}
		if(msg=="lshift"){
			intmax_t sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum<<=p->data;
			}
			return {integer(sum),true};
		}
		if(msg=="rshift"){
			intmax_t sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum>>=p->data;
			}
			return {integer(sum),true};
		}
		if(msg=="lshift_eq"){
			intmax_t &sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum<<=p->data;
			}
			return {pthis,true};
		}
		if(msg=="rshift_eq"){
			intmax_t &sum=p->data;
			for(const auto &i:args){
				auto p=translate(i);
				if(p!=nullptr && p->type=="integer")
					sum>>=p->data;
			}
			return {pthis,true};
		}
		if(msg=="scan"){
			std::cin>>p->data;
			return {pthis,true};
		}
		if(msg=="print"){
			std::cout<<p->data<<' ';
			return {pthis,true};
		}
		if(msg=="println"){
			std::cout<<p->data<<std::endl;
			return {pthis,true};
		}
		return {nullptr,false};
	},std::move(x));
}