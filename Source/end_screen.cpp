#include "end_screen.h"
#include "start_screen.h"
#include <fstream>
#include <iostream>


std::unique_ptr<State> End_screen::update()
{
	if (IsNewHighScore())
	{
		Enter_name();
		return nullptr;
	}

	if (IsKeyReleased(KEY_ENTER))
	{
		Save_leaderboard();
		return std::make_unique<Start_screen>();
	}
	return nullptr;
}

void End_screen::draw() const noexcept
{
	if (IsNewHighScore())
	{
		Draw_textbox();
	}
	else
	{
		Draw_leaderboard();
	}
}

bool End_screen::IsNewHighScore() const noexcept
{
	return (current_score.score > leaderboard.back().score);
}

void End_screen::Enter_name() //TODO: make shorter
{
	mouse_on_text = CheckCollisionPointRec(GetMousePosition(), text_box);

	if (mouse_on_text)
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		Input_text();
	}
	else
	{
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}

	frame_counter = mouse_on_text ? frame_counter + 1 : 0;

	if (letter_count > 0 && letter_count < 9 && IsKeyReleased(KEY_ENTER))
	{
		Insert_score(name);
	}
}

void End_screen::Input_text()
{
	int key;
	while ((key = GetCharPressed()) > 0)
	{
		if ((key >= 32) && (key <= 125) && (letter_count < 9))
		{
			const char character_key = narrow_cast<char>(key);
			name.push_back(character_key);
			letter_count++;
		}
	}

	if (IsKeyPressed(KEY_BACKSPACE) && letter_count > 0)
	{
		name.pop_back();
		letter_count--;
	}
}
void End_screen::Insert_score(std::string _name)
{
	for (auto it = leaderboard.begin(); it != leaderboard.end(); ++it)
	{
		if (current_score.score > it->score)
		{
			Score_data newData{ _name, current_score.score };
			leaderboard.insert(it, newData);
			leaderboard.pop_back();

			current_score.score = 0;
			break;
		}
	}
}

void End_screen::Load_leaderboard() noexcept //TODO: empty
{

}

void End_screen::Save_leaderboard() //TODO: does not save to file
{
	std::fstream file{ "Leaderboard" };

	if (!file)
	{
		std::cout << "file not found \n";

	}
	else
	{
		std::cout << "file found \n";
	}
}

void End_screen::Draw_textbox() const noexcept //TODO: magic values
{
	const Color borderColor = mouse_on_text ? RED : DARKGRAY;
	constexpr float thickness = 2.0f;
	DrawRectangleLinesEx(text_box, thickness, borderColor);
	DrawTextF(name.c_str(), text_box.x + 5.0f, text_box.y + 8.0f, 40, MAROON);
	DrawText(TextFormat("INPUT CHARS: %i/%i", letter_count, 8), 600, 600, 20, YELLOW);

	constexpr int maxLetterCount = 9;
	if (mouse_on_text && letter_count < maxLetterCount)
	{
		if ((frame_counter / 20) % 2 == 0)
		{
			DrawTextF("_", text_box.x + 8 + MeasureText(name.c_str(), 40), text_box.y + 12.0f, 40, MAROON);
		}
	}
	else if (mouse_on_text)
	{
		DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
	}

	if (letter_count > 0 && letter_count < 9)
	{
		DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
	}
}

void End_screen::Draw_leaderboard() const noexcept //TODO: magic values
{
	DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);
	int yOffset = 140;
	for (const auto& entry : leaderboard)
	{
		DrawText(entry.name.c_str(), 50, yOffset, 40, YELLOW);
		DrawText(TextFormat("%i", entry.score), 350, yOffset, 40, YELLOW);
		yOffset += 40;
	}
}