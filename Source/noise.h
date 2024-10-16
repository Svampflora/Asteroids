#pragma once
#include <algorithm> 
#include <numeric>
#include <random>
#include <vector>
#include <cmath> 


static inline std::vector<int> get_noise_1d(int _count)
{
    std::vector<int> noise(_count);
    std::iota(noise.begin(), noise.end(), -narrow_cast<int>(_count * 0.5f));

    std::random_device rd;
    std::mt19937 rng(rd());

    std::shuffle(noise.begin(), noise.end(), rng);
    return noise;
}



static inline std::vector<float> get_perlin_noise_1d(int _count, int _octaves)
{
    std::vector<int> seed_noise = get_noise_1d(_count);
    std::vector<float> perlin_noise(_count);

    for (int x = 0; x < _count; x++)
    {
        float noise = 0.0f;
        float scale = 1.0f;
        float scale_accumulate = 0.0f;

        for (int octave = 0; octave < _octaves; octave++)
        {

            int pitch = _count / (1 << octave);
            if (pitch == 0) pitch = 1;

            const int sample_1 = (x / pitch) * pitch;
            const int sample_2 = (sample_1 + pitch) % _count;

            const float blend = static_cast<float>(x - sample_1) / pitch;

            const float sample = (1.0f - blend) * seed_noise[sample_1] + blend * seed_noise[sample_2];
            noise += sample * scale;

            scale_accumulate += scale;
            scale *= 0.5f;
        }

        perlin_noise[x] = noise / scale_accumulate;
    }

    return perlin_noise;
}

static inline constexpr float lerp(float a, float b, float t) 
{
    return a + t * (b - a);
}

static inline float map_range(float value, float inMin, float inMax, float outMin, float outMax)
{
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

static inline std::vector<float> get_perlin_noise_1d(int _count, int _octaves, float scale, float minValue, float maxValue)
{
    std::vector<int> seed_noise = get_noise_1d(_count);
    std::vector<float> perlin_noise(_count);

    for (int x = 0; x < _count; x++)
    {
        //TODO: settings
        float noise = 0.0f;
        float scale_accumulate = 0.0f;
        float amplitude = 1.0f;

        float frequency = scale;

        for (int octave = 0; octave < _octaves; octave++)
        {
            int pitch = _count >> octave;
            if (pitch == 0) pitch = 1;

            const int sample_1 = (x / pitch) * pitch;
            const int sample_2 = (sample_1 + pitch) % _count;

            const float blend = (x - sample_1) / static_cast<float>(pitch);
            const float sample = lerp(static_cast<float>(seed_noise[sample_1]), static_cast<float>(seed_noise[sample_2]), blend);

            noise += sample * amplitude;
            scale_accumulate += amplitude;
            amplitude *= 0.5f; //TODO: settings octave amplitude reduction
            frequency *= 2.0f; //TODO: settings frequency increase for each octave
        }

        const float normalized_noise = noise / scale_accumulate;

        perlin_noise[x] = map_range(normalized_noise, -1.0f, 1.0f, minValue, maxValue);
    }

    return perlin_noise;
}

