#pragma once
#include <vector>
#include "entity.h"
#include <iostream>
#include "projectile.h"
#include "noise.h"

enum class Asteroid_type {small, big, huge };

class Asteroid : public Entity
{
	Asteroid_type type;
	std::vector<float> points;

	float set_radius() noexcept;
public:
	Asteroid(Asteroid_type _type, Vector2 _position, Vector2 _velocity);


	Asteroid_type get_type() const noexcept;
	int get_score() const noexcept;
	void update() override;
	void draw() const noexcept override;

};

class Asteroid_factory
{
	Vector2 get_spawn_position(Vector2 _player_position, float min_distance) noexcept
	{
		const float restricted_range = 2 * min_distance;
		Vector2 spawn_position{ GetRandomValueF(0.0f, GetScreenWidthF() - restricted_range),
								GetRandomValueF(0.0f, GetScreenHeightF() - restricted_range) };

		if (spawn_position.x >= GetScreenWidthF() - (_player_position.x - min_distance))
		{
			spawn_position.x += restricted_range;
		}
		if (spawn_position.y >= GetScreenHeightF() - (_player_position.y - min_distance))
		{
			spawn_position.y += restricted_range;
		}
		return spawn_position;
	}

	Asteroid_type smaller_type(Asteroid_type type) const
	{
		switch (type)
		{
		case Asteroid_type::huge:

			return Asteroid_type::big;

		case Asteroid_type::big:

			return Asteroid_type::small;
		}

		std::cout << "invalid asteroid type" << std::endl;
		throw;
	}

public:

	std::vector<Asteroid> make_huge_ones(Vector2 _player_position, int _amount) //TODO: redo: set random position, check for player, displace
	{
		std::vector<Asteroid> asteroids;
		constexpr int max_speed = 200;
		constexpr int min_distance_from_player = 125 + 20; //TODO: inject or rake from settings
		asteroids.reserve(_amount);
		for (auto i = 0; i < _amount; i++) //TODO: old loop and casting
		{
			const Vector2 position = get_spawn_position(_player_position, min_distance_from_player);
			
			const Vector2 velocity{ GetRandomValueF(0, 2 * max_speed) - max_speed , GetRandomValueF(0, 2 * max_speed) - max_speed };

			Asteroid asteroid(Asteroid_type::huge, position, velocity);
			asteroids.emplace_back(asteroid);
		}
		return asteroids;
	}

	std::vector<Asteroid> make(Asteroid _old_asteroid, int _amount)
	{
		std::vector<Asteroid> asteroids;
		for (auto i = 0; i < _amount; i++)
		{
			//TODO: put increase_factor in settings
			constexpr float increase_factor = 1.5f;
			const Vector2 velocity = { increase_factor * GetRandomValueF(0.0f, _old_asteroid.get_velocity().x), increase_factor * GetRandomValueF(0.0f, _old_asteroid.get_velocity().y) };

			Asteroid asteroid(smaller_type(_old_asteroid.get_type()), _old_asteroid.get_position(), velocity);
			asteroids.emplace_back(asteroid);
		}
		return asteroids;
	}
};