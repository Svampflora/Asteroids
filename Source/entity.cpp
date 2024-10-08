#include "entity.h"



bool Entity::is_alive() const noexcept
{
	return alive;
}

void Entity::die() noexcept
{
	alive = false;
}

Vector2 Entity::get_position() const noexcept
{
	return position;
}

Vector2 Entity::get_velocity() const noexcept
{
	return velocity;
}

void Entity::set_velocity(Vector2 _velocity) noexcept
{
	
	velocity = _velocity;
	
}

void Entity::world_wrap() noexcept //TODO: add radius to mask jumping
{
	position.x = narrow_cast<float>(fmod(fmod(position.x, GetScreenWidth()) + GetScreenWidth(), GetScreenWidth()));
	position.y = narrow_cast<float>(fmod(fmod(position.y, GetScreenHeight()) + GetScreenHeight(), GetScreenHeight()));
}

void Entity::update()
{
}

void Entity::draw() const noexcept
{
	//DrawCircleV(position, radius, PURPLE);
}

void Entity::collide_with(Entity _other)
{
	const Vector2 v_diff = Vector2Subtract(velocity, _other.velocity);
	const Vector2 delta = Vector2Subtract(position, _other.get_hitbox().center);
	const float dist_squared = Vector2DotProduct(delta, delta);
	const float dot_product = Vector2DotProduct(v_diff, delta);

	//area stand in for mass
	const float mass = Area(get_hitbox());
	const float other_mass = Area(_other.get_hitbox());

	const float mass_ratio = (2 * other_mass) / (mass + other_mass);
	const float scale_factor = mass_ratio * dot_product / dist_squared;
	const Vector2 velocity_change = Vector2Scale(delta, scale_factor);

	resolve_clipping(_other);
	velocity = Vector2Subtract(velocity, velocity_change);
}

void Entity::resolve_clipping(Entity _other)
{
	const Vector2 delta = Vector2Subtract(position, _other.get_hitbox().center);
	const float distance = Vector2Length(delta);
	const float penetration_depth = (radius + _other.get_hitbox().radius) - distance;
	if (penetration_depth > 0)
	{
		constexpr float buffer = 0.0f;
		const Vector2 direction = Vector2Normalize(delta);
		position = Vector2Add(position, Vector2Scale(direction, penetration_depth + buffer));
	}
	
}

Circle Entity::get_hitbox() const noexcept
{
	return { position, radius };
}
