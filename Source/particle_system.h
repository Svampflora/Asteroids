#pragma once
#include "utilities.h"
#include <vector>

struct Particle
{
	Vector2 position = { 0.0f, 0.0f };
	Vector2 velocity = { 0.0f, 0.0f };
	float time_remaining = 0.0f;
	
	Particle() noexcept {};
	Particle(Vector2 _position, Vector2 _velocity, float _life_time) noexcept;

	bool is_alive() const noexcept
	{
		if (time_remaining > 0)
		{
			return true;
		}
		return false;
	}

	void update(float _delta_time) noexcept
	{
		position.x += velocity.x;
		position.y -= velocity.y;

		if (is_alive())
		{
			time_remaining -= _delta_time;
		}
	}
};


class Particle_system
{
	std::vector<Particle> particles;
	Color start_color;
	Color end_color;
	Vector2 position;
	float speed;
	float life_time;
	int index;

	void update_index() noexcept
	{
		index++;
		if (index >= particles.size())
		{
			index = 0;
		}
	}

public:
	Particle_system(Color _start_color, Color _end_color, size_t _max_particles, float _life_time, float _speed) noexcept :
		particles{ _max_particles, Particle{} }
	{
		start_color = _start_color;
		end_color = _end_color;
		position = { 0.0f, 0.0f };
		life_time = _life_time;
		speed = _speed;
		index = 0;
	};
	void eject(const float& _angle, const float& _force, const int& _spread) noexcept
	{
		const Vector2 eject_direction = { sinf((_angle / 180) * 3.14f), cosf((_angle / 180.f) * 3.14f) };
		const Vector2 spread = { GetRandomValueF(-_spread, _spread) , GetRandomValueF(-_spread, _spread) };
		const Vector2 velocity = { eject_direction.x * (_force + spread.x), eject_direction.y * (_force + spread.y) };

		particles[index] = { position, velocity, life_time };
		update_index();
	};

	void update(float _delta_time) noexcept
	{
		for (auto& particle : particles)
		{
			particle.update(_delta_time);
			
		}
	}
	void update(float _delta_time, Vector2 _position) noexcept
	{
		position = _position;
		update(_delta_time);

	};

	void draw() const
	{
		constexpr float start_size = 10.0f;
		for (auto& particle : particles)
		{
			if (particle.is_alive())
			{
				const float life_fraction = (particle.time_remaining / life_time);
				const float size = Lerp(0.0f, start_size, life_fraction);//negative_curve(life_fraction);
				DrawCircleV(particle.position, size, LerpColor(start_color, end_color, life_fraction));

			}
		}
	};

	//void draw(Font _font, std::string _text) const
	//{
	//	for (auto& particle : particles)
	//	{
	//		if (particle.Is_alive())
	//		{
	//			const float life_fraction = (particle.time_remaining / life_time);
	//			DrawTextEx(_font, _text.data(), particle.position, 1.0f, 1.0f, LerpColor(start_color, end_color, life_fraction));

	//		}
	//	}
	//};
};