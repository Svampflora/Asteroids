#include "start_screen.h"
#include "play_screen.h"


Start_screen::Start_screen() noexcept :
font_1{ LoadFont("assets/pixelmix/pixelmix.ttf") },
font_2{ LoadFont("assets/pixelmix/pixelmix_bold.ttf") }
{}


std::unique_ptr<State> Start_screen::update()
{
	if (IsKeyReleased(KEY_SPACE))
	{
		return std::make_unique<Play_screen>();
	}
	return nullptr;
}

void Start_screen::draw() const noexcept
{
	draw_title();
	draw_instructions();
}

void Start_screen::draw_title() const noexcept
{
	const Color title_color = { 50,60,255,255 }; //TODO: inject
	const std::string title = std::string("ASTEROIDS"); //TODO: inject
	const Vector2 title_position{ 0.2f * GetScreenWidthF() , 0.3f * GetScreenHeightF()};
	
	constexpr int fade_repititions = 5;
	for (float i = 0; i < fade_repititions; i++)
	{
		const float fade_alpha = (i / fade_repititions) / 1;
		const Color trail_color = LerpColor(title_color, { title_color.r, title_color.b, title_color.b, 0U }, fade_alpha);
		const Vector2 trail_position = LerpPosition(title_position, {title_position.x, title_position.y + 0.1f * GetScreenHeightF() }, fade_alpha);
		DrawTextEx(font_2, title.data(), trail_position, 200.0f, 1.0f, trail_color);
	}
	DrawTextEx(font_2, title.data(), title_position, 200.0f, 1.0f, WHITE);
	
}

void Start_screen::draw_instructions() const noexcept
{
	const std::string instruction = std::string("- press SPACE to start -");
	const Vector2 instruction_position{ 0.4f * GetScreenWidthF() , 0.6f * GetScreenHeightF() };
	DrawTextEx(font_2, instruction.data(), instruction_position, 20.0f, 1.0f, WHITE);
}