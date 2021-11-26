#pragma once

#pragma once

#include <array>
#include <vector>

namespace Geo {

	class Rectangle;
	class Circle;
	class LineSeg;

	class Rectangle {
	public:
		Rectangle(float x, float y, float width, float height);
		Rectangle();

	public:
		float x, y, width, height;
		
		bool getIntersection(const Geo::LineSeg& line, std::vector<std::array<float, 2>>* poi = nullptr) const;
		bool getIntersection(const Geo::Rectangle& rect, std::vector<std::array<float, 2>>* poi = nullptr) const;
		bool getIntersection(const Geo::Circle& circle, std::vector<std::array<float, 2>>* poi = nullptr) const;

		bool containsPoint(float x, float y) const;

	};

	class Circle {
	public:
		Circle(float x, float y, float radius);
		Circle();


	public:
		float x, y, radius;

		bool getIntersection(const Geo::Circle& circle, std::vector<std::array<float, 2>>* poi = nullptr);
		bool getIntersection(const Geo::Rectangle& rect, std::vector<std::array<float, 2>>* poi = nullptr);
		bool getIntersection(const Geo::LineSeg& line, std::vector<std::array<float, 2>>* poi = nullptr);

		bool containsPoint(float _x, float _y) const;
	};

	class LineSeg {
	public:
		LineSeg(float x1, float y1, float x2, float y2);
		LineSeg();
	public:
		float x1, y1;
		float x2, y2;

		bool getIntersection(const Geo::Circle& circle, std::vector<std::array<float, 2>>* poi = nullptr);
		bool getIntersection(const Geo::LineSeg& line, std::vector<std::array<float, 2>>* poi = nullptr);
		bool getIntersection(const Geo::Rectangle& rect, std::vector<std::array<float, 2>>* poi = nullptr);

	};
}