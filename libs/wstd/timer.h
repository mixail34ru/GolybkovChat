#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

namespace wstd {

class timer {
public:
	using interval_t = std::chrono::milliseconds;
	using handler_t = std::function<void(void)>;

	using handler_except_t
		= std::function<void(std::exception_ptr, timer*)>;
	static constexpr auto default_except_handler
		= [](std::exception_ptr, timer*) {};

	timer();

	timer(
		const interval_t& interval,
		const handler_t& handler,
		bool is_immediatly = false,
		const handler_except_t handler_except = default_except_handler
	);

	timer(timer&& other) noexcept;
	timer& operator = (timer&& other) noexcept;

	~timer() noexcept;

	void start(
		const interval_t& interval,
		const handler_t& handler,
		bool is_immediatly = false,
		const handler_except_t& handler_except = default_except_handler
	);

	void stop();

	bool status() const;

private:
	std::thread _thread;
	std::atomic_bool _is_running;

	timer(const timer& other) = delete;
	timer& operator = (const timer& other) = delete;

}; //class timer
//-------------------------------------------------------------------

} //namespace wstd

#endif //TIMER_H