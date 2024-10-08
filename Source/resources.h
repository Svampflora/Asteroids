#pragma once

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "vector"
#include <string>
#include <string_view>
#include <stdexcept>
#include <format>

using namespace std::literals::string_view_literals;

class Texture_Container
{
    Texture2D texture;
public:
    Texture_Container(std::string_view path);
    Texture_Container(const Texture_Container& other) = delete;
    Texture_Container& operator=(const Texture_Container& other) = delete;
    Texture_Container(Texture_Container&& other) noexcept;
    Texture_Container& operator=(Texture_Container&& other) noexcept;
    ~Texture_Container();
    const Texture2D& get() const noexcept;
};

class Sound_Container
{
    Sound sound;
public:
    Sound_Container(std::string_view path);
    Sound_Container(const Sound_Container& other) = delete;
    Sound_Container& operator=(const Sound_Container& other) = delete;
    Sound_Container(Sound_Container&& other) noexcept;
    Sound_Container& operator=(Sound_Container&& other) noexcept;
    ~Sound_Container();
    const Sound& get() const noexcept;
};

class Animator
{
    std::vector<Texture_Container> frames;
    size_t current_frame = 0;
    float frames_per_second = 3.0f;
    float timer = 0;

public:
    Animator(std::vector<std::string_view> file_paths);

    void update(float deltaTime) noexcept;
    const Texture2D& get_frame() const noexcept;
};

class Resources //TODO: rule of six
{
    Texture_Container texture_map = Texture_Container("assets/asteroid_texture.png"sv );
    Sound_Container pew = Sound_Container("assets/Space_ship.ogg");

public:
    Resources();
    ~Resources();

    const Texture2D& get_texture_map() const noexcept;
    const Sound& get_pew() const noexcept;

};