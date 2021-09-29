#pragma once
#include <utility>
#include <stdexcept>
const double EPS = 0.0000001;

using Point = std::pair<double, double>;

const Point DEFAULT_POINT = { std::numeric_limits<double>::max(), std::numeric_limits<double>::max() };

bool IsEqualDoubles(double d1, double d2);

class Line {
public:
	Line(double new_a, double new_b, double new_c)
		: a(new_a), b(new_b), c(new_c) {};

	Line(const Point& p_1, const Point& p_2);
	double DistanceToPoint(const Point& p) const;
	Line GetPerpendicularLine(const Point& p) const;

	double GetA() const;
	double GetB() const;
	double GetC() const;

	double CalculateY(double x) const;
private:
	double a, b, c;
};

class Circle {
public:
	Circle(const Point& new_centre, double new_radius);
	Point GetCentre() const;
	double GetRadius() const;

private:
	Point centre;
	double radius;
};

double DistanceBetweenPoints(const Point& p_1, const Point& p_2);

Point IntersectionOfLines(const Line& line_1, const Line& line_2);
std::pair<Point, Point> IntersectionOfCircles(const Circle& circle_1, const Circle& circle_2);

Point ReflectPoint(const Point& to_reflect, const Line& line);
Circle ReflectCircle(const Circle& to_reflect, const Line& line);
Line ReflectLine(const Line& to_reflect, const Line& line);

Point InversionOfPoint(const Point& to_inverse, const Circle& circle);
