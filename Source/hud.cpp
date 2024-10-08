#include "hud.h"
#include <algorithm>

ID::ID(std::string n, int p) :
	name(n),
	points(p)
{
}

Vector2 get_screen_unit() noexcept
{
	return { GetScreenWidthF() * 0.1f, GetScreenHeightF() * 0.1f };
}

void HUD::update_particles(float _delta_time) noexcept
{
	for (auto& particle : score_particles)
	{
		particle.update(_delta_time);
		if (!particle.is_alive())
		{
			particle = score_particles.back();
			score_particles.pop_back();
		}
	}
}

HUD::HUD() :
	font{ LoadFont("assets/pixelmix/pixelmix.ttf") },
	high_scores{},
	score_particles{}
{
}

//void HUD::draw_current_health(const int _health)
//{
//
//}

void HUD::update(float _delta_time)
{
	update_particles(_delta_time);

}

void HUD::draw_current_score(const int _score) const noexcept
{
	std::string text = "SCORE: " + std::to_string(_score);

	const Vector2 position = { 0.8f * GetScreenWidth(), 0.1f * GetScreenHeight() };
	//DrawText(text.data(), position_x, position_y, 2, WHITE);
	DrawTextEx(font, text.data(), position, 25.0f, 1.0f, WHITE);
}

void HUD::draw_score_particles() const noexcept
{
		for (auto& particle : score_particles)
	{
		if (particle.is_alive())
		{
			//TODO: define score particle lifetime 1.5f
			const float life_fraction = (particle.time_remaining / 1.5f);
			const std::string text = std::to_string(particle.score);
			DrawTextEx(font, text.data(), particle.position, 20.0f, 1.0f, LerpColor(WHITE, {WHITE.r, WHITE.g, WHITE.b, 0}, life_fraction));

		}
	}
}

void HUD::add_score_particle(Vector2 _position, int _score)
{
	score_particles.push_back(Score{ _position, _score, 1.5f });
}
