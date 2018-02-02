#ifndef UTIL_H
#define UTIL_H

#include <chrono>
#include <tuple>

namespace onechchy {

    std::chrono::time_point<std::chrono::steady_clock>& preTime();

    void setPreTime(std::chrono::time_point<std::chrono::steady_clock> time_point);

    std::chrono::time_point<std::chrono::steady_clock>& nowTime();

    void setNowTime(std::chrono::time_point<std::chrono::steady_clock> time_point);
    void start();

    void tick();

    template<class TimeUnit>
    int clock(){
        onechchy::setPreTime(onechchy::nowTime());
        onechchy::setNowTime(std::chrono::steady_clock::now());

        TimeUnit diff = std::chrono::duration_cast<TimeUnit>(onechchy::nowTime() - onechchy::preTime());

        return diff.count();
    }

//    template<class TimeUnit, class Fun, class... Args>
//    decltype(auto) funClock(Fun&& f, Args&&... args)
//    noexcept(noexcept(std::forward<Fun>(f)(std::forward<Args>(args)...)))
//    {
//        auto start = std::chrono::steady_clock::now();
//        auto rtl = std::forward<Fun>(f)(std::forward<Args>(args)...);
//        TimeUnit diff = std::chrono::duration_cast<TimeUnit>(std::chrono::steady_clock::now() - start);
//        return std::make_tuple(diff.count(), rtl);
//    }


    template<class TimeUnit, class Fun, class... Args>
    decltype(auto) funClock(Fun&& f, Args&&... args)
    noexcept(noexcept(std::forward<Fun>(f)(std::forward<Args>(args)...)))
    {
        auto start = std::chrono::steady_clock::now();
        auto rtl = std::forward<Fun>(f)(std::forward<Args>(args)...);
        TimeUnit diff = std::chrono::duration_cast<TimeUnit>(std::chrono::steady_clock::now() - start);
        return std::make_tuple(diff.count(), rtl);
    }

    template<class TimeUnit, class Fun, class... Args>
    decltype(auto) funNClock(Fun&& f, Args&&... args)
    noexcept(noexcept(std::forward<Fun>(f)(std::forward<Args>(args)...)))
    {
        auto start = std::chrono::steady_clock::now();
        std::forward<Fun>(f)(std::forward<Args>(args)...);
        TimeUnit diff = std::chrono::duration_cast<TimeUnit>(std::chrono::steady_clock::now() - start);
        return diff.count();
    }

    template<class TimeUnit, class Fun, class SELF, class... Args>
    decltype(auto) cfunClock(Fun&& f, SELF* self, Args&&... args)
    noexcept(noexcept((self->*(std::forward<Fun>(f)))(std::forward<Args>(args)...)))
    {
        auto start = std::chrono::steady_clock::now();
        auto rtl = (self->*(std::forward<Fun>(f)))(std::forward<Args>(args)...);
        TimeUnit diff = std::chrono::duration_cast<TimeUnit>(std::chrono::steady_clock::now() - start);
        return std::make_tuple(diff.count(), rtl);
    }

    template<class TimeUnit, class Fun, class SELF, class... Args>
    decltype(auto) cfunNClock(Fun&& f, SELF* self, Args&&... args)
    noexcept(noexcept((self->*(std::forward<Fun>(f)))(std::forward<Args>(args)...)))
    {
        auto start = std::chrono::steady_clock::now();
        (self->*(std::forward<Fun>(f)))(std::forward<Args>(args)...);
        TimeUnit diff = std::chrono::duration_cast<TimeUnit>(std::chrono::steady_clock::now() - start);
        return diff.count();
    }
}

#endif // UTIL_H
