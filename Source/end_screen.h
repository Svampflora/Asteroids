#pragma once
#include"State.h"
#include <vector>


struct Score_data
{
	std::string name{ "" };
	unsigned int score{ 0 };
};

class End_screen : public State
{
	std::vector<Score_data> leaderboard{ {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	Score_data current_score{};
	Rectangle text_box = { 600, 500, 225, 50 };
	std::string name{""};
	int letter_count = 0;
	int frame_counter = 0;
	bool mouse_on_text = false; //TODO: remove flag

	void Draw_textbox() const noexcept;
	void Draw_leaderboard() const noexcept;
	void Load_leaderboard() noexcept;
	void Enter_name();
	void Input_text();
	void Insert_score(std::string name);
	void Save_leaderboard();
	bool IsNewHighScore() const noexcept; //TODO: replace with algorithm
public:
	std::unique_ptr<State> update() override;
	void draw() const noexcept override;
};