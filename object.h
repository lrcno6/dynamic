#ifndef _OBJECT_H_
#define _OBJECT_H_
#include<string>
#include<vector>
#include<list>
#include<queue>
#include<map>
#include<functional>
#include<thread>
#include<mutex>
#include<condition_variable>
namespace dynamic{
	struct Object;
	struct Message{
		Object *m_p;
		std::string m_msg;
		std::vector<Object*> m_args;
	};
	struct Object{
		static void procedure(Object*,std::function<bool(const Message&)>);
		std::list<Object*> m_parents;
		std::map<std::string,Object*> m_members;
		std::string m_type;
		std::thread m_thread;
		std::mutex m_mutex,m_queue_mutex;
		std::condition_variable m_cv;
		std::queue<Message> m_msg_queue;
		Object(const std::string &type,std::function<bool(const Message&)> call_back):Object(std::string(type),call_back){}
		Object(std::string &&type,std::function<bool(const Message&)> call_back):m_type(type),m_thread(procedure,this,call_back){}
		~Object(){
			push({this,"QUIT",{}});
			m_thread.join();
		}
		void push(const Message &msg){
			push(Message(msg));
		}
		void push(Message &&msg){
			{
				std::lock_guard<std::mutex> lock(m_queue_mutex);
				m_msg_queue.push(msg);
			}
			std::unique_lock<std::mutex> lock(m_mutex);
			m_cv.notify_one();
		}
		Message pop(){
			Message msg;
			{
				std::lock_guard<std::mutex> lock(m_queue_mutex);
				msg=m_msg_queue.front();
				m_msg_queue.pop();
			}
			return msg;
		}
		bool empty(){
			std::lock_guard<std::mutex> lock(m_queue_mutex);
			return m_msg_queue.empty();
		}
	};
}
#endif