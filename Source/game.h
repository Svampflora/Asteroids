#pragma once
#include "settings.h"
#include "window.h"
#include "start_screen.h"
#include "play_screen.h"
#include "end_screen.h"

class Game
{
	Window window{ "Asteroids", SCREEN_WIDTH, SCREEN_HEIGHT };
	std::unique_ptr<State> current_state = std::make_unique<Start_screen>();
	Score_data scoreData{};

public:
	void Update();
	void Render() const noexcept;
};