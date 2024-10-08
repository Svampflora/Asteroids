#pragma once
//#include "utilities.h"
//#include <vector>
#include "particle_system.h"
#include <string>
#include <fstream>



struct Score : public Particle
{
	int score = 0;

	Score(Vector2 _position, int _score, float _life_time) noexcept :
	score(_score),
	Particle{ _position, {0,1}, _life_time }
	{
	}
};

struct ID
{
	std::string name;
	int points;

	ID(std::string, int);
};

class HUD
{
	Font font;
	std::vector<ID> high_scores;
	std::vector<Score> score_particles;

	void update_particles(float _delta_time) noexcept;

public:

	HUD();
	void update(float _delta_time);
	void add_score_particle(Vector2 _position, int _score);
	//void draw_current_health(const int _health);
	void draw_current_score(const int _score) const noexcept;
	void draw_score_particles() const noexcept;
};
