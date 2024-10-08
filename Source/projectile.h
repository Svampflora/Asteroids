#pragma once

#include "entity.h"
#include <iostream>


class Projectile : public Entity
{

	bool out_of_bounds() const noexcept;
public:

	Projectile(Vector2 _position, float _angle);
	void update() override;
	void draw() const noexcept override;
	void draw_o() noexcept;
};




