#include "projectile.h"


static Vector2 direction(float _angle) noexcept
{
	return Vector2 { sinf((_angle / 180) * PI), cosf((_angle / 180.f) * PI) };
}

Projectile::Projectile(Vector2 _position, float _angle)
{
	position = _position;
	angle = _angle;
	velocity = Vector2Scale(direction(angle), 800.0f);
	radius = 1;
	alive = true;
}

bool Projectile::out_of_bounds() const noexcept
{
	
	if (position.x < 0 || position.x >= GetScreenWidth())
	{
		return true;
	}
	else if (position.y < 0 || position.y >= GetScreenHeight())
	{
		return true;
	}

	return false;
}

void Projectile::update()
{
	if (alive)
	{
		position.x += velocity.x * GetFrameTime();
		position.y -= velocity.y * GetFrameTime();
	}


	if (out_of_bounds())
	{
		alive = false;
	}
}


void Projectile::draw() const noexcept
{
	constexpr float thickness = 5.0f;
	constexpr float length = 20.0f;
	if (alive)
	{
		const Vector2 tail_end_position{ position.x + length * -sinf((angle / 180) * PI), position.y - length * -cosf((angle / 180) * PI) };
		DrawLineEx(position, tail_end_position, thickness, RED);
		
	}

}

void Projectile::draw_o() noexcept
{
	DrawText("O", narrow_cast<int>(position.x - 5), narrow_cast<int>(position.y - 10), 1, BLUE);

}