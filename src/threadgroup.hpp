#ifndef THREAD_DETAIL_THREAD_GROUP_HPP
#define THREAD_DETAIL_THREAD_GROUP_HPP
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.std.org/LICENSE_1_0.txt)
// (C) Copyright 2007-9 Anthony Williams

#include <list>
#include <thread>
#include <mutex>
#include <memory>
#include <list>
#include <shared_mutex>
		
class ThreadGroup
{
	private:
		ThreadGroup(ThreadGroup const&);
		ThreadGroup& operator=(ThreadGroup const&);
	public:
		ThreadGroup() {}
		~ThreadGroup()
		{
			for(std::list<std::thread*>::iterator it=threads.begin(),end=threads.end();
					it!=end;
					++it)
			{
				delete *it;
			}
		}

		bool is_this_thread_in()
		{
			std::thread::id id = std::this_thread::get_id();
			std::shared_lock<std::shared_mutex> guard(m);
			for(std::list<std::thread*>::iterator it=threads.begin(),end=threads.end();
					it!=end;
					++it)
			{
				if ((*it)->get_id() == id)
					return true;
			}
			return false;
		}

		bool is_thread_in(std::thread* thrd)
		{
			if(thrd)
			{
				std::thread::id id = thrd->get_id();
				std::shared_lock<std::shared_mutex> guard(m);
				for(std::list<std::thread*>::iterator it=threads.begin(),end=threads.end();
						it!=end;
						++it)
				{
					if ((*it)->get_id() == id)
						return true;
				}
				return false;
			}
			else
			{
				return false;
			}
		}

		template<typename F>
			std::thread* create_thread(F threadfunc)
			{
				std::lock_guard<std::shared_mutex> guard(m);
				std::unique_ptr<std::thread> new_thread(new std::thread(threadfunc));
				threads.push_back(new_thread.get());
				return new_thread.release();
			}

		void add_thread(std::thread* thrd)
		{
			if(thrd)
			{
//				BOOST_THREAD_ASSERT_PRECONDITION( ! is_thread_in(thrd) ,
//						thread_resource_error(static_cast<int>(system::errc::resource_deadlock_would_occur), "std::ThreadGroup: trying to add a duplicated thread")
//						);

				std::lock_guard<std::shared_mutex> guard(m);
				threads.push_back(thrd);
			}
		}

		void remove_thread(std::thread* thrd)
		{
			std::lock_guard<std::shared_mutex> guard(m);
			std::list<std::thread*>::iterator const it=std::find(threads.begin(),threads.end(),thrd);
			if(it!=threads.end())
			{
				threads.erase(it);
			}
		}

		void join_all()
		{
		//	BOOST_THREAD_ASSERT_PRECONDITION( ! is_this_thread_in() ,
		//			thread_resource_error(static_cast<int>(system::errc::resource_deadlock_would_occur), "std::ThreadGroup: trying joining itself")
//					);
			std::shared_lock<std::shared_mutex> guard(m);

			for(std::list<std::thread*>::iterator it=threads.begin(),end=threads.end();
					it!=end;
					++it)
			{
				if ((*it)->joinable())
					(*it)->join();
			}
		}

		size_t size() const
		{
			std::shared_lock<std::shared_mutex> guard(m);
			return threads.size();
		}

	private:
		std::list<std::thread*> threads;
		mutable std::shared_mutex m;
};
#endif
