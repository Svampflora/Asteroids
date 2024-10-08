#pragma once

#include <ranges>
#include "State.h"
#include "space_ship.h"
#include "asteroid.h"
#include "alien.h"
#include "projectile.h"
#include "resources.h"
#include "input.h"
#include "hud.h"


class Play_screen : public State
{
	Resources resourses;
	Space_ship player;
	Asteroid_factory asteroid_factory;
	std::vector <Projectile> projectiles;
	//std::vector <Projectile> alien_projectiles;
	std::vector <Asteroid> asteroids;
	HUD headsup_display;
	int health;
	int score;

	template <typename ObjectType>
	void collisions(std::vector<ObjectType>& objects);
	//template <typename ObjectType, typename OtherType>
	//void collisions(std::vector<ObjectType>& objects, std::vector<OtherType>& other_objects);
	template <typename ObjectType, typename OtherType>
	void collisions(std::vector<ObjectType>& objects, OtherType& single_object);
	void collisions(std::vector<Asteroid>& _asteroids, std::vector<Projectile>& _projectiles);

	bool is_game_over();
	void set_up();
	void input() noexcept;
	void remove_dead_objects();
	void handle_collisions();
	void check_shooting();


public:
	
	Play_screen();
	std::unique_ptr<State> update() override;
	void draw() const noexcept override;
};