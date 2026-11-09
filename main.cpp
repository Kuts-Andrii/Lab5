#include <chrono>
#include <future>
#include <iomanip>
#include <iostream>
#include <string>
#include <syncstream>
#include <thread>

namespace {

    using Seconds = std::chrono::seconds;

    constexpr Seconds kSlowDuration{7};
    constexpr Seconds kQuickDuration{1};

    void compute(const std::string& name, Seconds duration)
    {
        std::this_thread::sleep_for(duration);
        std::osyncstream(std::cout) << name << '\n';
    }

    void slow(const std::string& name)
    {
        compute(name, kSlowDuration);
    }

    void quick(const std::string& name)
    {
        compute(name, kQuickDuration);
    }

    void work()
    {
        const auto start = std::chrono::steady_clock::now();

        // A2 runs in its own thread
        auto a2 = std::async(std::launch::async, [] { slow("A2"); });
        // A3, A4 and C run in another thread
        auto c = std::async(std::launch::async, [] {
            quick("A3");
            quick("A4");
            quick("C");
        });

        // A1, B and D run in the main thread, B waits for A2 and the work ends after C
        slow("A1");
        a2.get();
        quick("B");
        quick("D");
        c.get();

        const std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
        std::osyncstream(std::cout) << "Time: " << std::fixed << std::setprecision(2) << elapsed.count() << " s\nWork is done!\n";
    }

}

int main()
{
    work();
    return 0;
}