#include "play_screen.h"
#include "end_screen.h"
#include "start_screen.h"
#include <algorithm>


//template<typename T, typename Func>
//void CheckConditionAndPerformAction(T value, Func action)
//{
//	if (value)
//	{
//		action();
//	}
//}

template <typename T>
void draw_entities(const std::vector<T>& _entities) noexcept
{
	for (const T& entity : _entities)
	{
		if (entity.is_alive())
		{
			entity.draw();
		}
	}
}

template <typename T>
void draw_entities(const std::vector<T>& _entities, const Texture& _texture) noexcept
{
	for (const T& entity : _entities)
	{
		if (entity.is_alive())
		{
			entity.draw(_texture);
		}
	}
}

template <typename T>
void update_entities(std::vector<T>& _entities)  
{
	for (T& entity : _entities)
	{
		if (entity.is_alive())
		{
			entity.update();
		}
	}
}

template <typename Container, typename Predicate>
void remove_if(Container& container, Predicate predicate)
{
	container.erase(
		std::remove_if(container.begin(), container.end(), predicate),
		container.end());
}

template <typename ObjectType>
void Play_screen::collisions(std::vector<ObjectType>& objects)
{
	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator)
	{
		std::for_each(iterator + 1, objects.end(), [&](ObjectType& other_object)
			{
				if (CheckCollisionCircles(iterator->get_hitbox(), other_object.get_hitbox()))
				{
					const ObjectType temp = *iterator;
					iterator->collide_with(other_object);
					other_object.collide_with(temp);
				}
			});
	}
}

//template <typename ObjectType, typename OtherType>
//void Play_screen::collisions(std::vector<ObjectType>& objects, std::vector<OtherType>& other_objects)
//{
//	for (ObjectType& object : objects)
//	{
//		for (OtherType& other_object : other_objects)
//		{
//			if (CheckCollisionCircles(object.get_hitbox(), other_object.get_hitbox()))
//			{
//				object.collide_with(other_object);
// 				other_object.collide_with(object);
//
//			}
//		}
//	}
//}


void Play_screen::collisions(std::vector<Asteroid>& _asteroids, std::vector<Projectile>& _projectiles)
{
	for (Asteroid& _asteroid : _asteroids)
	{
		for (Projectile& _projectile : _projectiles)
		{
			if (CheckCollisionCircles(_asteroid.get_hitbox(), _projectile.get_hitbox()))
			{
				score += _asteroid.get_score();
				headsup_display.add_score_particle(_asteroid.get_position(), _asteroid.get_score());
				_asteroid.collide_with(_projectile);
				//_projectile.collide_with(_asteroid);
				_asteroid.die();
				_projectile.die();

				if (_asteroid.get_type() != Asteroid_type::small)
				{
					std::vector<Asteroid> smaller_asteroids = asteroid_factory.make(_asteroid, 2);
					asteroids.insert(asteroids.end(), smaller_asteroids.begin(), smaller_asteroids.end());
				}
			}
		}
	}
}

template <typename ObjectType, typename OtherType>
void Play_screen::collisions(std::vector<ObjectType>& objects, OtherType& single_object)
{
	for (ObjectType& object : objects)
	{
		if (CheckCollisionCircles(object.get_hitbox(), single_object.get_hitbox()))
		{
			const ObjectType temp = object;
			object.collide_with(single_object);
			single_object.collide_with(temp);
		}
	}
}


Play_screen::Play_screen() :
	resourses{},
	player{},
	projectiles{},
	headsup_display{},
	health{ 0 },
	score{ 0 },
	asteroid_factory{}
{
	asteroids = asteroid_factory.make_huge_ones(player.get_position(), 3);
	
	//alien_projectiles;
	//pew;
	
}


std::unique_ptr<State> Play_screen::update()
{
	if (IsKeyPressed(KEY_Q))
	{
		return std::unique_ptr<Start_screen>();
	}
	//if (is_game_over())
	//{
	//	return std::make_unique<End_screen>();
	//}


	check_shooting();
	player.update();
	update_entities(projectiles);
	update_entities(asteroids);
	handle_collisions();
	headsup_display.update(GetFrameTime());

	remove_dead_objects();

	return nullptr;
}

void Play_screen::draw() const noexcept
{
	draw_entities(projectiles);
	draw_entities(asteroids);
	player.draw(resourses.get_texture_map());
	headsup_display.draw_score_particles();
	headsup_display.draw_current_score(score);

}

bool Play_screen::is_game_over()
{
	return false;
}

void Play_screen::set_up()
{
}

void Play_screen::input() noexcept
{

}

void Play_screen::remove_dead_objects() 
{

	remove_if(projectiles, [](const auto& projectile) noexcept { return !projectile.is_alive(); });
	remove_if(asteroids, [](const auto& asteroid) noexcept { return !asteroid.is_alive(); });

}

void Play_screen::handle_collisions()
{
	collisions(asteroids);
	collisions(asteroids, player);
	collisions(asteroids, projectiles);

}

void Play_screen::check_shooting() 
{
	if (player.get_shooting())
	{
		projectiles.push_back(Projectile(player.get_position(), player.get_angle()));
		PlaySound(resourses.get_pew());
	}
}



