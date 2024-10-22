#pragma once
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#if _M_CEE  // If using C++/CLR compiling flag
	#include "../std/mutex.h"
#else //_M_CEE
	#include <mutex>
    #include <condition_variable>
#endif //_M_CEE

#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <atomic>

namespace wstd {

class thread_pool {
public:
	thread_pool(unsigned int thread_count = std::thread::hardware_concurrency()) {
		setup_pool(thread_count);
	}//-----------------------------------------------------------------


	~thread_pool() noexcept {
		stop();
	}//----------------------------------------------------------------


	template<typename F>
	void add_job(F job) {
		if (_is_pool_terminated) return;
		{
			std::unique_lock lock(_queue_mtx);
			_job_queue.push(std::function<void()>(job));
		}
		_condition.notify_one();
	}//-----------------------------------------------------------------


	template<typename F, typename... Arg>
	void add_job(const F& job, const Arg&... args) {
		add_job([job, args...] { job(args...); });
	}//----------------------------------------------------------------


	void drop_unstarted_job() {
		std::queue<std::function<void()>> empty;
		{
			std::lock_guard lock(_queue_mtx);
			std::swap(_job_queue, empty);
		}
	}//----------------------------------------------------------------


	void restart(unsigned int thread_count) {
		stop();
		drop_unstarted_job();
		setup_pool(thread_count);
	}//----------------------------------------------------------------


	void stop() {
		_is_pool_terminated = true;
		_condition.notify_all();

		for (auto& thread : _pool) {
			if (thread.joinable()) thread.join();
		}
	}//----------------------------------------------------------------


	unsigned int thread_count() const {
		return _pool.size();
	}//----------------------------------------------------------------


	bool status() const {
		return _is_pool_terminated;
	}//----------------------------------------------------------------


private:
	std::vector<std::thread> _pool;
	std::queue<std::function<void()>> _job_queue;
	std::mutex _queue_mtx;
	std::condition_variable _condition;
	std::atomic_bool _is_pool_terminated;
	std::atomic_bool _is_thread_created;


	thread_pool(const thread_pool& other) = delete;
	thread_pool& operator = (const thread_pool& other) = delete;


	void setup_pool(unsigned int thread_count) {
		_pool.clear();
		_pool.reserve(thread_count);

		_is_pool_terminated = false;
		for (unsigned int i = 0; i < thread_count; ++i) {
			_is_thread_created = false;

			_pool.emplace_back(&thread_pool::loop, this);
			while (!_is_thread_created) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
	}//----------------------------------------------------------------


	void loop() {
		std::function<void()> job;
		_is_thread_created = true;

		while (!_is_pool_terminated) {
			{
				std::unique_lock lock(_queue_mtx);
				_condition.wait(lock, [this]() {
					return !_job_queue.empty() || _is_pool_terminated;
					});
				if (_is_pool_terminated)
					return;
				job = _job_queue.front();
				_job_queue.pop();
			}
			job();
		}
	}//----------------------------------------------------------------

}; //class thread_pool
//-------------------------------------------------------------------

} //namespace wstd

#endif //THREAD_POOL_H
