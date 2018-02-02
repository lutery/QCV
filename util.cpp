#include "util.h"

namespace onechchy {

    std::chrono::time_point<std::chrono::steady_clock>& preTime(){
        static std::chrono::time_point<std::chrono::steady_clock> pretime;
        return pretime;
    }

    void setPreTime(std::chrono::time_point<std::chrono::steady_clock> time_point){
        preTime() = time_point;
    }

    std::chrono::time_point<std::chrono::steady_clock>& nowTime(){
        static std::chrono::time_point<std::chrono::steady_clock> nowtime;
        return nowtime;
    }

    void setNowTime(std::chrono::time_point<std::chrono::steady_clock> time_point){
        nowTime() = time_point;
    }

    void start(){
        onechchy::setNowTime(std::chrono::steady_clock::now());
    }

    void tick(){
        onechchy::setPreTime(onechchy::nowTime());
        onechchy::setNowTime(std::chrono::steady_clock::now());
    }
}
