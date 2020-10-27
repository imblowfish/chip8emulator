#ifndef __CHIP8_TIMER_H__
#define __CHIP8_TIMER_H__

#include <chrono>

class Timer {
private:
    std::chrono::milliseconds timeout;
    std::chrono::milliseconds last_timestamp;
    Timer() = delete;
public:
    Timer(int64_t ms_timeout);
    void start();
    bool is_finished();
};

#endif