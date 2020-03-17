#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>

class Timer
{
    using watch_t = std::chrono::steady_clock;
    using timepoint_t = watch_t::time_point;

public:
    ~Timer() noexcept
    {
        auto end = watch_t::now();
        std::cout << "Timer stopped, ";
        if (working)
            time += std::chrono::duration_cast <std::chrono::microseconds> (end - m_begin);
        std::cout << time.count();
        std::cout << " microseconds passed." << std::endl;
    }
    void pause()
    {
        auto end = watch_t::now();
        working = false;
        time += std::chrono::duration_cast <std::chrono::microseconds> (end - m_begin);
        std::cout << "Timer paused, " << time.count() << " microseconds passed." << std::endl;

    }
    void resume()
    {
        working = true;
        m_begin = watch_t::now();
        std::cout << "Timer resumed" << std::endl;
    }

private:
    timepoint_t m_begin{watch_t::now()};
    std::chrono::microseconds time{0};
    bool working{true};
};

int main()
{
    {
        Timer t;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        t.pause();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        t.resume();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        t.pause();
    }
    system("pause");
    return 0;
}
