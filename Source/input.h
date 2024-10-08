#pragma once
#include <chrono>
#include "raylib.h"

class Cooldown 
{
    float seconds_of_cooldown;
    std::chrono::time_point<std::chrono::high_resolution_clock> last_pressed;
public:

    Cooldown(float _cooldown_duration) noexcept : 
        seconds_of_cooldown(_cooldown_duration), 
        last_pressed(std::chrono::high_resolution_clock::now()) 
    {}

    bool is_key_pressed(int key) noexcept
    {
        const auto now = std::chrono::high_resolution_clock::now();
        const float elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_pressed).count() / 1000.0f;

        if (IsKeyPressed(key) && elapsed >= seconds_of_cooldown) 
        {
            last_pressed = now;
            return true;
        }
        return false;
    }
};