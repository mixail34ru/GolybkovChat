#include "timer.h"

using namespace wstd;

timer::timer() : _is_running(false) {
}//------------------------------------------------------------------


timer::timer(
	const interval_t& interval,
	const handler_t& handler,
	bool is_immediatly,
	const handler_except_t handler_except
)
	: _is_running(false) 
{
	start(interval, handler, is_immediatly, handler_except);
}//------------------------------------------------------------------


timer::timer(timer&& other) noexcept :
	_is_running(other._is_running.load()),
	_thread(std::move(other._thread))
{}//-----------------------------------------------------------------


timer& timer::operator = (timer&& other) noexcept {
	if (this != &other) {
		_is_running = other._is_running.load();
		_thread = std::move(other._thread);
	}
	return *this;
}//------------------------------------------------------------------


timer::~timer() noexcept {
	stop();
}//------------------------------------------------------------------


void timer::start(
	const interval_t& interval,
	const handler_t& handler,
	bool do_immediatly,
	const handler_except_t& handler_except)
{
	if (_is_running) stop();

	_thread = std::thread(
		[this, interval, handler, do_immediatly, handler_except] {
			try {
				_is_running = true;

				if (do_immediatly) handler();

				while (_is_running) {
					std::this_thread::sleep_for(interval);
					handler();
				}
			}
			catch (...) { handler_except(std::current_exception(), this); }
		}
	);
}//------------------------------------------------------------------


void timer::stop() {
	_is_running = false;
	if (_thread.joinable()) _thread.join();
}//------------------------------------------------------------------


bool timer::status() const {
	return _is_running;
}//------------------------------------------------------------------