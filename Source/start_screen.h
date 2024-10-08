#pragma once
#include"State.h"

class Start_screen : public State
{
	Font font_1;
	Font font_2;

	void draw_title() const noexcept;
	void draw_instructions() const noexcept;
	
public:
	Start_screen() noexcept;
	std::unique_ptr<State> update() override;
	void draw() const noexcept override;
};
