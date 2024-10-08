#include "space_ship.h"



Particle::Particle(Vector2 _position, Vector2 _velocity, float _life_time) noexcept :
	position{ _position },
	velocity{ _velocity },
	time_remaining{ _life_time }
{}

Space_ship::Space_ship() noexcept:
	particle_system(FLAME_START, FLAME_END, 50, 1.0f, 1.0f),
	cooldown(0.3f)
{
	position = { GetScreenWidthF() / 2, GetScreenHeightF() / 2 };
	velocity = { 0.0f, 0.0f };
	angle = 0.0f;
	radius = 20.0f;
	alive = true;
	current_input = {};
	angle_velocity = 0.0f;
}

float Space_ship::get_angle() const noexcept
{
	return angle;
}

bool Space_ship::get_shooting() const noexcept
{
	return current_input.shooting;
}

bool Space_ship::get_teleporting() const noexcept
{
	return current_input.teleporting;
}

void Space_ship::input() noexcept
{
	current_input = Input{ IsKeyDown(KEY_UP), IsKeyDown(KEY_LEFT), IsKeyDown(KEY_RIGHT), cooldown.is_key_pressed(KEY_SPACE), false};
}

void Space_ship::movement() noexcept
{
	//TODO: move to settings
	constexpr float accelerate_factor = 10.0f;
	constexpr float decelerate_factor = 0.99f;
	constexpr float max_angle_velocity = 200.0f;


	if (current_input.thrust)
	{
		velocity.x += accelerate_factor * sinf((angle / 180.0f) * PI);
		velocity.y += accelerate_factor * cosf((angle / 180.0f) * PI);
		particle_system.eject(angle + 180.0f, 2.0f, 2);
	}
	else
	{
		velocity.x *= decelerate_factor;
		velocity.y *= decelerate_factor;
	}

   	if (current_input.left_turn && angle_velocity > -max_angle_velocity)
	{
		angle_velocity -= accelerate_factor;
		particle_system.eject(angle - 90.0f, 2.0f, 2);
	}
	else
	{
		angle_velocity *= decelerate_factor;
	}

	if (current_input.right_turn && angle_velocity < max_angle_velocity)
	{
		angle_velocity += accelerate_factor;
		particle_system.eject(angle + 90.0f, 2.0f, 2);
	}
	else
	{
		angle_velocity *= decelerate_factor;
	}

	const float delta_time = GetFrameTime();
	position.x += velocity.x * delta_time;
	position.y -= velocity.y * delta_time;
	angle += angle_velocity * delta_time;


	world_wrap();
}

void Space_ship::update()
{
	input();
	movement();
	const Vector2 exhaust_position{ position.x + radius * -sinf((angle / 180) * PI), position.y - radius * -cosf((angle / 180) * PI) };
	particle_system.update(GetFrameTime(), exhaust_position);
}

void Space_ship::draw(const Texture2D& texture) const noexcept
{
	particle_system.draw();

	const Rectangle source_coordinates{ 0,0,40,40 }; //TODO: inject
	const Rectangle destination_coordinates{ position.x, position.y, 2 * radius, 2 * radius,};
	const Vector2 origin{ radius, radius };
	DrawTexturePro(texture, source_coordinates, destination_coordinates, origin, angle, WHITE);
	//DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), radius, Color{ 200, 0, 0, 200 });
}
