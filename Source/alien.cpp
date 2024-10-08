#include "alien.h"

//Alien::Alien()
//{
//	sprite = screen.LoadSprite("assets/asteroid_texture.png");
//	alive = false;
//	position = { screen.GetWindowWidth() - 1.0f, -40 };
//	angle = 0;
//	velocity = { 0.0f, 0.0f };
//	shooting = false;
//	radius = 40;
//	range = screen.GetWindowHeight() / 2;
//}
//
//void Alien::Spawn()
//{
//	alive = true;
//	position = { (float)GetScreenWidth() - 1.0f, (float)-radius };
//}
//
//void Alien::IsHit()
//{
//	alive = false;
//	position.y = (float)GetScreenHeight();
//}
//
//void Alien::update()
//{
//	if (alive)
//	{
//
//		velocity.x = (float)-0.5;
//	
//
//		if (position.y < GetScreenHeight() / 20)
//		{
//			velocity.y = (float)-0.5;
//		}
//		else velocity.y = 0;
//
//		position.x += velocity.x;
//		position.y -= velocity.y;
//
//		//++++++++++WorldWrapping+++++++++++
//
//		if (position.x < 0)
//			position.x = position.x + GetScreenWidth();
//		if (position.x >= GetScreenWidth())
//			position.x = 0;
//
//		//if (position_Y < 0)
//		//	position_Y = position_Y + screen.GetWindowWidth();
//		//if (position_Y >= screen.GetWindowWidth())
//		//	position_Y = 0;
//
//		if (position.x < GetScreenWidth())
//		{
//			shooting = true;
//		}
//	}
//}
//
//void Alien::draw()
//{
//	sprite.texture.src = { 80,0,40,40 };
//	sprite.origin = { 20,20 };
//	sprite.scale = { 2 };
//	sprite.angle = angle;
//	sprite.position = { (float)position.x, (float)position.y };
//
//	
//	DrawSprite(sprite);
//	//screen.DrawCircle(((int)position_X - (int)radius), ((int)position_Y - (int)radius), (int)radius, 200, 0, 0, 200);
//}