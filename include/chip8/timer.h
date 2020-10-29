#ifndef __CHIP8_TIMER_H__
#define __CHIP8_TIMER_H__

#include <chrono>

namespace Chip8 {
    class Timer {
    private:
        bool isStarted;
        std::chrono::milliseconds timeout;
        std::chrono::milliseconds last_timestamp;
        Timer() = delete;

    public:
        Timer(int64_t ms_timeout);
        void start();
        void wait();
        bool is_finished();
    };
} // namespace Chip8

#endif