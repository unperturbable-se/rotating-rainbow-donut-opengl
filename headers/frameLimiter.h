#pragma once
#include <chrono>
#include <thread>

namespace custom
{
 class FrameLimiter
 {
   float fps;
   std::chrono::high_resolution_clock::time_point beginning;
   public:
   FrameLimiter(float fps) : fps(fps),beginning(std::chrono::high_resolution_clock::now()){}
   ~FrameLimiter()
   {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - beginning);
    auto timeRemaining = 1.0 / fps - duration.count();
    if (timeRemaining > 0) std::this_thread::sleep_for(std::chrono::duration<double>(timeRemaining));
   }
 };
};