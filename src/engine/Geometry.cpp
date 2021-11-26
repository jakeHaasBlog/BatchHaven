
#include "Geometry.h"

namespace {
	bool getRectRectIntersection(const Geo::Rectangle& rect1, const Geo::Rectangle& rect2, std::vector<std::array<float, 2>>* poi = nullptr) {

		if (!poi) {
			if (rect1.x < rect2.x + rect2.width &&
				rect1.x + rect1.width > rect2.x &&
				rect1.y < rect2.y + rect2.height &&
				rect1.y + rect1.height > rect2.y)
			{
				return true;
			}
			return false;
		}
		else {
			bool intersecting = false;

			if (rect2.x <= rect1.x && rect1.x <= rect2.x + rect2.width) {
				if (rect1.y - rect1.height <= rect2.y && rect2.y <= rect1.y) {
					intersecting = true;
					poi->push_back({ rect1.x, rect2.y });
				}
				if (rect1.y - rect1.height <= rect2.y - rect2.height && rect2.y - rect2.height <= rect1.y) {
					intersecting = true;
					poi->push_back({ rect1.x, rect2.y - rect2.height });
				}
			}

			if (rect2.x <= rect1.x + rect1.width && rect1.x + rect1.width <= rect2.x + rect2.width) {
				if (rect1.y - rect1.height <= rect2.y && rect2.y <= rect1.y) {
					intersecting = true;
					poi->push_back({ rect1.x + rect1.width, rect2.y });
				}
				if (rect1.y - rect1.height <= rect2.y - rect2.height && rect2.y - rect2.height <= rect1.y) {
					intersecting = true;
					poi->push_back({ rect1.x + rect1.width, rect2.y - rect2.height });
				}
			}

			if (rect2.y - rect2.height <= rect1.y && rect1.y <= rect2.y) {
				if (rect1.x <= rect2.x && rect2.x <= rect1.x + rect1.width) {
					intersecting = true;
					poi->push_back({ rect2.x, rect1.y });
				}
				if (rect1.x <= rect2.x + rect2.width && rect2.x + rect2.width <= rect1.x + rect1.width) {
					intersecting = true;
					poi->push_back({ rect2.x + rect2.width, rect1.y });
				}
			}

			if (rect2.y - rect2.height <= rect1.y - rect1.height && rect1.y - rect1.height <= rect2.y) {
				if (rect1.x <= rect2.x && rect2.x <= rect1.x + rect1.width) {
					intersecting = true;
					poi->push_back({ rect2.x, rect1.y - rect1.height });
				}
				if (rect1.x <= rect2.x + rect2.width && rect2.x + rect2.width <= rect1.x + rect1.width) {
					intersecting = true;
					poi->push_back({ rect2.x + rect2.width, rect1.y - rect1.height });
				}
			}

			return intersecting;
		}
	}

	bool getLineCircleIntersection(const Geo::LineSeg& line, const Geo::Circle& circle, std::vector<std::array<float, 2>>* poi) {

		float r = circle.radius;

		float a = -(line.y2 - line.y1);
		float b = line.x2 - line.x1;
		float c = -a * (line.x1 - circle.x) - b * (line.y1 - circle.y);

		float epsilon = 0.000001f;

		bool intersecting = false;

		float x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
		if (c * c > r * r * (a * a + b * b) + epsilon)
			return false;
		else if (abs(c * c - r * r * (a * a + b * b)) < epsilon) {
			if ((fmin(line.x1, line.x2) - epsilon <= x0 + circle.x && x0 + circle.x <= fmax(line.x1, line.x2) + epsilon))
				if ((fmin(line.y1, line.y2) - epsilon <= y0 + circle.y && y0 + circle.y <= fmax(line.y1, line.y2) + epsilon)) {
					if (poi) poi->push_back({ x0 + circle.x, y0 + circle.y });
					intersecting = true;
				}
		}
		else {
			float d = r * r - c * c / (a * a + b * b);
			float mult = sqrt(d / (a * a + b * b));
			float ax, ay, bx, by;
			ax = x0 + b * mult;
			bx = x0 - b * mult;
			ay = y0 - a * mult;
			by = y0 + a * mult;

			if ((fmin(line.x1, line.x2) - epsilon <= ax + circle.x && ax + circle.x <= fmax(line.x1, line.x2) + epsilon))
				if ((fmin(line.y1, line.y2) - epsilon <= ay + circle.y && ay + circle.y <= fmax(line.y1, line.y2) + epsilon)) {
					if (poi) poi->push_back({ ax + circle.x, ay + circle.y });
					intersecting = true;
				}
			if ((fmin(line.x1, line.x2) - epsilon <= bx + circle.x && bx + circle.x <= fmax(line.x1, line.x2) + epsilon))
				if ((fmin(line.y1, line.y2) - epsilon <= by + circle.y && by + circle.y <= fmax(line.y1, line.y2) + epsilon)) {
					if (poi) poi->push_back({ bx + circle.x, by + circle.y });
					intersecting = true;
				}
		}

		if (circle.containsPoint(line.x1, line.y1) || circle.containsPoint(line.x2, line.y2))
			intersecting = true;

		return intersecting;

	}

	bool getRectCircleIntersection(const Geo::Rectangle& rect, const Geo::Circle& circle, std::vector<std::array<float, 2>>* poi) {
		if (!poi) {
			float deltaX = circle.x - fmax(rect.x, fmin(circle.x, rect.x + rect.width));
			float deltaY = circle.y - fmin(rect.y, fmax(circle.y, rect.y - rect.height));
			return (deltaX * deltaX + deltaY * deltaY) < (circle.radius * circle.radius) || rect.containsPoint(circle.x, circle.y);
		}
		else {
			bool intersected = false;
			Geo::LineSeg line2 = { rect.x, rect.y, rect.x + rect.width, rect.y };
			if (getLineCircleIntersection(line2, circle, poi)) {
				intersected = true;
			}

			line2 = { rect.x, rect.y - rect.height, rect.x + rect.width, rect.y - rect.height };
			if (getLineCircleIntersection(line2, circle, poi)) {
				intersected = true;
			}

			line2 = { rect.x, rect.y, rect.x, rect.y - rect.height };
			if (getLineCircleIntersection(line2, circle, poi)) {
				intersected = true;
			}

			line2 = { rect.x + rect.width, rect.y, rect.x + rect.width, rect.y - rect.height };
			if (getLineCircleIntersection(line2, circle, poi)) {
				intersected = true;
			}

			if (rect.containsPoint(circle.x, circle.y))
				intersected = true;

			return intersected;
		}
	}

	bool getLineLineIntersection(const Geo::LineSeg& line1, const Geo::LineSeg& line2, std::vector<std::array<float, 2>>* poi) {

		float p[2] = { line1.x1, line1.y1 };
		float t;
		float r[2] = { line1.x2 - line1.x1, line1.y2 - line1.y1 };
		// p + tr

		float q[2] = { line2.x1, line2.y1 };
		float u;
		float s[2] = { line2.x2 - line2.x1, line2.y2 - line2.y1 };
		// q + us

		float rXs = r[0] * s[1] - r[1] * s[0];
		float qMinusP[2] = { q[0] - p[0], q[1] - p[1] };

		float qMinisPCrossS = qMinusP[0] * s[1] - qMinusP[1] * s[0];
		float qMinusPCrossR = qMinusP[0] * r[1] - qMinusP[1] * r[0];

		t = qMinisPCrossS / (r[0] * s[1] - s[0] * r[1]);
		u = qMinusPCrossR / rXs;

		if (rXs != 0.0f && 0.0f <= t && t <= 1.0f && 0 <= u && u <= 1.0f) {
			if (poi) {
				poi->push_back({ p[0] + t * r[0], p[1] + t * r[1] });
			}
			return true;
		}
		else {
			return false;
		}

	}

	bool getLineRectIntersection(const Geo::Rectangle& rect, const Geo::LineSeg& line, std::vector<std::array<float, 2>>* poi) {

		if (!poi) {
			if (rect.containsPoint(line.x1, line.y1)) return true;
			if (rect.containsPoint(line.x1, line.y1)) return true;

			Geo::LineSeg line2 = { rect.x, rect.y, rect.x + rect.width, rect.y };
			if (getLineLineIntersection(line, line2, poi)) {
				return true;
			}

			line2.x2 = rect.x;
			line2.y2 = rect.y - rect.height;
			if (getLineLineIntersection(line, line2, poi)) {
				return true;
			}

			line2.x1 = rect.x + rect.width;
			line2.y1 = rect.y - rect.height;
			if (getLineLineIntersection(line, line2, poi)) {
				return true;
			}

			line2.x1 = rect.x + rect.width;
			line2.y1 = rect.y;
			if (getLineLineIntersection(line, line2, poi)) {
				return true;
			}

			return false;
		}
		else {

			bool intersection = false;

			if (rect.containsPoint(line.x1, line.y1)) intersection = true;
			if (rect.containsPoint(line.x1, line.y1)) intersection = true;

			Geo::LineSeg line2 = { rect.x, rect.y, rect.x + rect.width, rect.y };
			if (getLineLineIntersection(line, line2, poi)) {
				intersection = true;
			}

			line2.x2 = rect.x;
			line2.y2 = rect.y - rect.height;
			if (getLineLineIntersection(line, line2, poi)) {
				intersection = true;
			}

			line2.x1 = rect.x + rect.width;
			line2.y1 = rect.y - rect.height;
			if (getLineLineIntersection(line, line2, poi)) {
				intersection = true;
			}

			line2.x1 = rect.x + rect.width;
			line2.y1 = rect.y;
			line2.x2 = rect.x + rect.width;
			line2.y2 = rect.y - rect.height;
			if (getLineLineIntersection(line, line2, poi)) {
				intersection = true;
			}

			return intersection;
		}

	}

}

Geo::Rectangle::Rectangle(float _x, float _y, float _width, float _height)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
}

Geo::Rectangle::Rectangle()
{
	x = 0.0f;
	y = 0.0f;
	width = 1.0f;
	height = 1.0f;
}

bool Geo::Rectangle::getIntersection(const Geo::LineSeg& line, std::vector<std::array<float, 2>>* poi) const
{
	return getLineRectIntersection(*this, line, poi);
}

bool Geo::Rectangle::getIntersection(const Geo::Rectangle& rect, std::vector<std::array<float, 2>>* poi) const
{
	return getRectRectIntersection(*this, rect, poi);
}

bool Geo::Rectangle::getIntersection(const Geo::Circle& circle, std::vector<std::array<float, 2>>* poi) const
{
	return getRectCircleIntersection(*this, circle, poi);
}

bool Geo::Rectangle::containsPoint(float _x, float _y) const
{
	if (x <= _x && _x <= x + width) {
		if (y - height <= _y && _y <= y) {
			return true;
		}
	}
	return false;
}

Geo::Circle::Circle(float _x, float _y, float _radius)
{
	x = _x;
	y = _y;
	radius = _radius;
}

Geo::Circle::Circle()
{
	x = 0.0f;
	y = 0.0f;
	radius = 0.5f;
}

bool Geo::Circle::getIntersection(const Geo::Circle& circle, std::vector<std::array<float, 2>>* poi)
{
	float dSquared = pow(circle.x - x, 2) + pow(circle.y - y, 2);

	bool intersecting = dSquared <= pow(radius + circle.radius, 2);
	if (!poi || !intersecting) {
		return intersecting;
	}
	else {
		float d = sqrt(dSquared);
		float b = (-pow(circle.radius, 2) + pow(radius, 2) - dSquared) / (-2 * d);
		float c = sqrt(pow(circle.radius, 2) - pow(b, 2));

		float EBunit[2] = { ((x - circle.x) / d), ((y - circle.y) / d) };
		float EB[2] = { EBunit[0] * b, EBunit[1] * b };
		float B[2] = { circle.x + EB[0], circle.y + EB[1] };

		float BD[2] = { -EBunit[1] * c, EBunit[0] * c };
		poi->push_back({ B[0] + BD[0], B[1] + BD[1] });
		poi->push_back({ B[0] - BD[0], B[1] - BD[1] });

		return true;
	}
	return false;
}

bool Geo::Circle::getIntersection(const Geo::Rectangle& rect, std::vector<std::array<float, 2>>* poi)
{
	return getRectCircleIntersection(rect, *this, poi);
}

bool Geo::Circle::getIntersection(const Geo::LineSeg& line, std::vector<std::array<float, 2>>* poi)
{
	return getLineCircleIntersection(line, *this, poi);
}

bool Geo::Circle::containsPoint(float _x, float _y) const
{
	return pow(_x - x, 2) + pow(_y - y, 2) <= radius * radius;
}

Geo::LineSeg::LineSeg(float _x1, float _y1, float _x2, float _y2)
{
	x1 = _x1;
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;
}

Geo::LineSeg::LineSeg()
{
}

bool Geo::LineSeg::getIntersection(const Geo::Circle& circle, std::vector<std::array<float, 2>>* poi)
{
	return getLineCircleIntersection(*this, circle, poi);
}

bool Geo::LineSeg::getIntersection(const Geo::LineSeg& line, std::vector<std::array<float, 2>>* poi)
{
	return getLineLineIntersection(*this, line, poi);
}

bool Geo::LineSeg::getIntersection(const Geo::Rectangle& rect, std::vector<std::array<float, 2>>* poi)
{
	return getLineRectIntersection(rect, *this, poi);
}
