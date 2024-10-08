#include "asteroid.h"


Asteroid::Asteroid(Asteroid_type _type, Vector2 _position, Vector2 _velocity)
{
	//sprite = sprite_settings(_type),
	position = _position; 
	velocity = _velocity;
	angle = 0.0f;
	alive = true;
	type = _type;
	points = get_perlin_noise_1d(64, 12, 1.0f, -0.5f, 0.5f);
	set_radius();
}

static inline void DrawAsteroid(Vector2 center, std::vector<float> _points, float _radius/*, float rotation*/) noexcept
{
	const int segments = narrow_cast<int>( _points.size() );
	if (segments < 3) return;

	std::vector<Vector2> points (segments + 2);
	points[0] = center;
	const float angleStep = (2 * PI) / segments;

	for (int i = 0; i < segments; i++)
	{
		const float angle = i * angleStep;
		points[i + 1] = { center.x + (_radius + _points[i]) * cosf(-angle), center.y + (_radius + _points[i]) * sinf(-angle) };
	}
	points[segments + 1] = points[1];
	DrawTriangleFan(points.data(), segments + 2, WHITE);

}

//Sprite Asteroid::sprite_settings(Asteroid_type _type)
//{
//	Sprite asteroid_sprite = screen.LoadSprite("assets/asteroid_texture.png");
//	const int texture_unit = 40;
//	asteroid_sprite.scale = { 4 };
//
//	switch (_type)
//	{
//
//	case Asteroid_type::huge:
//
//		asteroid_sprite.texture.src = { 0,40,80,80 };
//		asteroid_sprite.origin = { 40,35 };
//
//		break;
//
//	case Asteroid_type::big:
//
//		asteroid_sprite.texture.src = { 80,40,40,40 };
//		asteroid_sprite.origin = { 20,18 };
//
//		break;
//
//	case Asteroid_type::small:
//
//		asteroid_sprite.texture.src = { 80,80,40,40 };
//		asteroid_sprite.origin = { 15,8 };
//
//		break;
//
//	}
//	return asteroid_sprite;
//}

void Asteroid::set_radius() //TODO: put in settings
{
	switch (type)
	{

	case Asteroid_type::huge:

		radius = 125;
		break;

	case Asteroid_type::big:

		radius = 60;
		break;

	case Asteroid_type::small:

		radius = 25;
		break;

	}
}

Asteroid_type Asteroid::get_type() const noexcept
{
	return type;
}

int Asteroid::get_score() const noexcept
{
	switch (get_type())
	{

	case Asteroid_type::huge:

		return 100;

	case Asteroid_type::big:

		return 50;

	case Asteroid_type::small:

		return 25;
	}
	return 0;
}

void Asteroid::update() //TODO: cap asteroid velocity
{
	position.x += velocity.x * GetFrameTime();
	position.y -= velocity.y * GetFrameTime();
	angle++;
	
	world_wrap();
}

void Asteroid::draw() const noexcept
{

	DrawAsteroid(get_hitbox().center, points, radius);
	//DrawCircleV(get_hitbox().center, get_hitbox().radius, WHITE);

}
