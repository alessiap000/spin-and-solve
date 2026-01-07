#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
    Timer();

    void start();
    void stop();
    double getSeconds() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

};

#endif // TIMER_H
