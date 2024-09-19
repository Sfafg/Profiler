#include "Profiler.h"
#include "Profiler.cpp"
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

void ChildFunction()
{
    PROFILE_FUNCTION();
}

void ParentFunction()
{
    PROFILE_FUNCTION();

    for (int i = 0; i < 100'000; i++)
        ChildFunction();

}

int main()
{
    Profiler::SetHightPriority();
    while (true)
    {
        Profiler::BeginFrame();
        ParentFunction();
        Profiler::EndFrame();
    }
}