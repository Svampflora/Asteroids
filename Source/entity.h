#pragma once

#include "utilities.h"

class Projectile;

class Entity
{
protected:
	Vector2 position{0.0f, 0.0f};
	Vector2 velocity{ 0.0f, 0.0f };
	float angle{ 0.0f };
	float radius{ 0.0f };
	bool alive{ 0 };
public:

	Circle get_hitbox() const noexcept;
	Vector2 get_position() const noexcept;
	Vector2 get_velocity() const noexcept;
	bool is_alive() const noexcept;
	void die() noexcept;
	void set_velocity(Vector2 _velocity) noexcept;
	void world_wrap() noexcept;
	void resolve_clipping(Entity _other);
	virtual void update();
	virtual void draw() const noexcept;
	virtual void collide_with(Entity _other);
	virtual ~Entity() = default;
};
