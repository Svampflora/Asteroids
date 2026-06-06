#include "asteroid.h"


Asteroid::Asteroid(Asteroid_type _type, Vector2 _position, Vector2 _velocity)
{
	position = _position; 
	velocity = _velocity;
	angle = 0.0f;
	alive = true;
	type = _type;
	points = get_perlin_noise_1d(64, 12, 1.0f, -0.5f, 0.5f);
	radius = set_radius();
}

static inline void DrawAsteroid(Vector2 center, std::vector<float> _radii, float _radius/*, float rotation*/) noexcept
{
	const int segments = narrow_cast<int>( _radii.size() );
	if (segments < 3) return;

	std::vector<Vector2> points (segments + 1);
	const float angleStep = (2 * PI) / segments;

	auto angle = 0.0f;
	auto point_it = points.begin() + 1;
	auto radius_it = _radii.begin();

	*points.begin() = center;
	for (; point_it != points.end() && radius_it != _radii.end(); ++point_it, ++radius_it, angle += angleStep)
	{
		*point_it = 
		{
			center.x + (_radius + *radius_it) * cosf(-angle),
			center.y + (_radius + *radius_it) * sinf(-angle)
		};
	}
	*points.rbegin() = *(points.begin() + 1);

	DrawTriangleFan(points.data(), segments + 2, WHITE);
}

float Asteroid::set_radius() noexcept//TODO: settings.h
{
	switch (type)
	{
	case Asteroid_type::huge:

		return 125.0f;

	case Asteroid_type::big:

		return 60.0f;

	case Asteroid_type::small:

		return 25.0f;

	}
	return 0.0f;
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

}
