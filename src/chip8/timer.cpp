#include <cstdint>

#include "chip8/timer.h"

Timer::Timer(int64_t ms_timeout) : isStarted(false) {
    timeout =  static_cast<std::chrono::milliseconds>(ms_timeout);
}

void Timer::start() {
    using namespace std::chrono;
        last_timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    isStarted = true;
}

void Timer::wait() {
    if(!isStarted) {
        return;
    }
    while(!is_finished());
}

bool Timer::is_finished() {
    using namespace std::chrono;
    milliseconds now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    milliseconds diff = now - last_timestamp;
    if(now - last_timestamp > timeout) {
        isStarted = false;
        return true;
    }
    return false;
}