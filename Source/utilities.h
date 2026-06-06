#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <raylib.h>
#include <raymath.h>
#pragma warning(pop)

#include <cmath>
#include <utility>
#include <vector>

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

typedef struct vec2 {
	float x, y;

	vec2 operator+(const ::vec2& other) const noexcept
	{
		return { x + other.x, y + other.y };
	}

	vec2& operator+=(const ::vec2& other) noexcept
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	vec2 operator-(const ::vec2& other) const noexcept
	{
		return { x - other.x, y - other.y };
	}

	vec2& operator-=(const ::vec2& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	float cross(const ::vec2& other) const noexcept
	{
		return x * other.y - y * other.x;
	}

	float dot(const ::vec2& other) const noexcept
	{
		return x * other.x + y * other.y;
	}

	vec2 perpendicular() const noexcept
	{
		return { -y, x };
	}
}vec2;

typedef struct Range{
	float min, max;

	bool overlaps(const Range& other) const noexcept
	{
		return !(other.min > max || min > other.max);
	}
}Range;

typedef struct Circle {
	Vector2 center;                
	float radius;                
} Circle;

typedef struct Polygon
{
	std::vector<Vector2> vertices;

	Vector2 position() const noexcept
	{
		return vertices.front();
	}
}Polygon;

static inline constexpr float area(Circle circle) noexcept
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

		float cross(const ::Vector2& other) const noexcept
		{
			return x * other.y - y * other.x;
		}
		
		float dot(const ::Vector2& other) const noexcept
		{
			return x * other.x + y * other.y;
		}

		Vector2 perpendicular()  const noexcept
		{
			return { -y, x };
		}
	};

}

static inline float dot_product(const Vector2& first, const Vector2& second) noexcept
{
	return first.x * second.x + first.y * second.y;
}

static inline Range project(const Polygon& polygon, const Vector2& axis) noexcept //TODO: numeric_limit scetchy
{
	float min = std::numeric_limits<float>::max();
	float max = std::numeric_limits<float>::lowest();

	for (const auto& vertex : polygon.vertices) 
	{
		const float projection = dot_product(vertex, axis);
		min = std::min(min, projection);
		max = std::max(max, projection);
	}

	return { min, max };
}

static inline Vector2 lerp_position(const Vector2& start, const Vector2& end, const float& alpha) noexcept {
	Vector2 result{};
	result.x = static_cast<float>((1 - alpha) * end.x + alpha * start.x);
	result.y = static_cast<float>((1 - alpha) * end.y + alpha * start.y);

	return result;
}

static inline Color lerp_color(const Color& start, const Color& end, const float& alpha) noexcept {
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

inline bool SAT_collision(const Polygon& polygon1, const Polygon& polygon2)
{
	auto get_edges = [](const Polygon& polygon) 
		{
		std::vector<Vector2> edges;
		for (size_t i = 0; i < polygon.vertices.size(); ++i) 
		{
			const Vector2 v1 = polygon.vertices.at(i);
			const Vector2 v2 = polygon.vertices.at((i + 1) % polygon.vertices.size());
			
			edges.push_back(Vector2Subtract(v2, v1));
		}
		return edges;
		};

	std::vector<Vector2> edges = get_edges(polygon1); //TODO: add resolution parameter?
	const auto& polygon2_edges = get_edges(polygon2);
	edges.insert(edges.end(), polygon2_edges.begin(), polygon2_edges.end());

	for (const auto& edge : edges) 
	{	
		const Vector2 axis = { -edge.y, edge.x  };
		const Range projection1 = project(polygon1, axis);
		const Range projection2 = project(polygon2, axis);

		if (!projection1.overlaps(projection2)) 
		{
			return false;
		}
	}

	return true;
}

static constexpr Color FLAME_START = { 25, 116, 207, 50 }; //TODO: settings.h
static constexpr Color FLAME_END = { 233, 31, 99, 0 };



