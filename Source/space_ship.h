#pragma once
#include "entity.h"
#include "resources.h"
#include "input.h"
#include "particle_system.h"

class Space_ship: public Entity
{
	Cooldown cooldown; //TODO: move into Input?
	struct Input
	{
		bool thrust = false;
		bool left_turn = false;
		bool right_turn = false;
		bool shooting = false;
		bool teleporting = false;
	};
	Particle_system particle_system;
	Input current_input;
	float angle_velocity; //TODO: move to Entity

	void input() noexcept;
	void movement() noexcept;
public:

	Space_ship() noexcept;

	float get_angle() const noexcept;
	bool get_shooting() const noexcept;
	bool get_teleporting() const noexcept;
	void update() override;
	void draw(const Texture2D& texture) const noexcept;

};
