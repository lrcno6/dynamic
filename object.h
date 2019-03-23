#ifndef _OBJECT_H_
#define _OBJECT_H_
#include<string>
#include<vector>
#include<list>
#include<map>
#include<functional>
namespace dynamic{
	struct ObjectPointer;
	struct Object{
		size_t ref_cnt;
		std::list<ObjectPointer> parents;
		std::map<std::string,ObjectPointer> members;
		std::function<std::pair<ObjectPointer,bool>(const ObjectPointer&,const std::string&,const std::vector<ObjectPointer>&)> proc;
		Object():ref_cnt(0){}
		virtual ~Object()=default;
		ObjectPointer get_member(const std::string&)const;
		std::pair<ObjectPointer,bool> procedure(const std::string&,const std::vector<ObjectPointer>& =std::vector<ObjectPointer>());
	};
	class ObjectPointer{
		public:
			template<class type=Object> // type must be Object or a subclass of Object, or it causes undefined behavior
			static ObjectPointer create(const std::function<std::pair<ObjectPointer,bool>(const ObjectPointer&,const std::string&,const std::vector<ObjectPointer>&)> &proc){
				ObjectPointer p;
				p.New<type>();
				p->proc=proc;
				return p;
			}
			template<class type=Object> // type must be Object or a subclass of Object, or it causes undefined behavior
			static ObjectPointer create(std::function<std::pair<ObjectPointer,bool>(const ObjectPointer&,const std::string&,const std::vector<ObjectPointer>&)> &&proc){
				ObjectPointer p;
				p.New<type>();
				p->proc=proc;
				return p;
			}
			ObjectPointer(Object *p=nullptr)noexcept:m_pointer(p){
				if(p!=nullptr)
					p->ref_cnt++;
			}
			ObjectPointer(const ObjectPointer &other)noexcept:m_pointer(other.m_pointer){
				if(m_pointer!=nullptr)
					m_pointer->ref_cnt++;
			}
			ObjectPointer(ObjectPointer &&other)noexcept:m_pointer(other.m_pointer){
				other.m_pointer=nullptr;
			}
			~ObjectPointer(){
				release();
			}
			ObjectPointer& operator=(const ObjectPointer &other){
				release();
				if((m_pointer=other.m_pointer)!=nullptr)
					m_pointer->ref_cnt++;
				return *this;
			}
			ObjectPointer& operator=(ObjectPointer &&other){
				release();
				m_pointer=other.m_pointer;
				other.m_pointer=nullptr;
				return *this;
			}
			template<class type=Object> // type must be the actual type of the object pointed to by m_pointer or the parent class of the actual type, or it causes undefined behavior
			type& operator*()const{
				return *(type*)m_pointer;
			}
			template<class type=Object> // type must be the actual type of the object pointed to by m_pointer or the parent class of the actual type, or it causes undefined behavior
			type* operator->()const{
				return (type*)m_pointer;
			}
			explicit operator bool()const noexcept{
				return m_pointer!=nullptr;
			}
			template<class type=Object> // type must be Object or a subclass of Object, or it causes undefined behavior
			ObjectPointer& New(){
				release();
				m_pointer=new type;
				m_pointer->ref_cnt=1;
				return *this;
			}
			void release(){
				if(m_pointer!=nullptr){
					if(--m_pointer->ref_cnt==0)
						delete m_pointer;
					m_pointer=nullptr;
				}
			}
		private:
			Object *m_pointer;
	};
}
#endif