#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <raylib.h>
#include <raymath.h>
#pragma warning(pop)

#include <cmath>
#include <utility>

template <typename T, typename U>
inline T narrow_cast(U&& u) noexcept
{
	return static_cast<T>(std::forward<U>(u));
}

inline static constexpr float half_of(float _whole) noexcept
{
	return _whole * 0.5f;
}

inline static constexpr Vector2 origin(Rectangle _rectangle) noexcept
{
	return { _rectangle.x + half_of(_rectangle.width), _rectangle.y + half_of(_rectangle.height) };
}

inline static constexpr Vector2 origin_upward(Rectangle _rectangle) noexcept
{
	return { _rectangle.x + half_of(_rectangle.width), _rectangle.y - half_of(_rectangle.height) };
}

static inline float GetScreenWidthF() noexcept
{
	return static_cast<float>(GetScreenWidth());
}

static inline float GetScreenHeightF() noexcept
{
	return static_cast<float>(GetScreenHeight());
}

static inline float GetRandomValueF(int min, int max) noexcept
{
	return static_cast<float>(GetRandomValue(min, max));
}

static inline float GetRandomValueF(float min, float max) noexcept
{
	return GetRandomValueF(narrow_cast<int>(min), narrow_cast<int>(max));
}

static inline void DrawCircleF(float centerX, float centerY, float radius, Color color ) noexcept
{
	DrawCircle(static_cast<int>(centerX), static_cast<int>(centerY), radius, color);
}

static inline void DrawTextF(const char* text, float posX, float posY, int fontSize, Color color) noexcept
{
	DrawText(text, static_cast<int>(posX), static_cast<int>(posY), fontSize, color);
}


typedef struct Circle {
	Vector2 center;                
	float radius;                
} Circle;

static inline constexpr float Area(Circle circle) noexcept
{
	return PI * circle.radius * circle.radius;
}

namespace raylib
{
	class Vector2 : public ::Vector2
	{
	public:
		Vector2 operator+(const ::Vector2& other) const noexcept
		{
			return { x + other.x, y + other.y };
		}

		Vector2& operator+=(const ::Vector2& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2 operator-(const ::Vector2& other) const noexcept 
		{
			return { x - other.x, y - other.y };
		}

		Vector2& operator-=(const ::Vector2& other) noexcept 
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
	};

}


static inline Vector2 LerpPosition(const Vector2& start, const Vector2& end, const float& alpha) noexcept {
	Vector2 result{};
	result.x = static_cast<float>((1 - alpha) * end.x + alpha * start.x);
	result.y = static_cast<float>((1 - alpha) * end.y + alpha * start.y);

	return result;
}

static inline Color LerpColor(const Color& start, const Color& end, const float& alpha) noexcept {
	Color result{};
	result.r = static_cast<unsigned char>((1 - alpha) * end.r + alpha * start.r);
	result.g = static_cast<unsigned char>((1 - alpha) * end.g + alpha * start.g);
	result.b = static_cast<unsigned char>((1 - alpha) * end.b + alpha * start.b);
	result.a = static_cast<unsigned char>((1 - alpha) * end.a + alpha * start.a);
	return result;
}

static inline bool CheckCollisionCircles(const Circle& c1, const Circle& c2) noexcept
{
	return CheckCollisionCircles(c1.center, c1.radius, c2.center, c2.radius);
}

static constexpr Color FLAME_START = { 25, 116, 207, 50 };
static constexpr Color FLAME_END = { 233, 31, 99, 0 };

static inline float negative_curve(const float x) noexcept
{
	return ((powf(x, 2.0f) * 4.0f)) + ((x * 4.0f));
	//return ( - 4.0f * (x * x)) + (4.0f * x);
}

