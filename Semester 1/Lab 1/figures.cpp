#include "figures.h"

bool IsEqualDoubles(double d1, double d2) {
	return fabs(d1 - d2) < EPS;
}

Line::Line(const Point& p_1, const Point& p_2) {
	if (IsEqualDoubles(p_1.first, p_2.first) && IsEqualDoubles(p_1.second, p_2.second)) {
		throw std::invalid_argument("Points are equal");
	}

	if (IsEqualDoubles(p_1.first, p_2.first)) {
		a = 1;
		b = 0;
		c = p_1.first;
	}
	else if (IsEqualDoubles(p_1.second, p_2.second)) {
		a = 0;
		b = 1;
		c = p_1.second;
	}
	else {
		a = p_2.first - p_1.first;
		b = p_1.second - p_2.second;
		c = IsEqualDoubles(p_1.first * p_2.second,p_1.second * p_2.first) ? 0 : p_1.first * p_2.second - p_1.second * p_2.first;
	}
}

double Line::DistanceToPoint(const Point& p) const {
	return fabs(a * p.first + b * p.second + c) / sqrt(a * a + b * b);
}

Line Line::GetPerpendicularLine(const Point& p) const {
	return Line(b, -a, a * p.second - b * p.first);
}

double Line::GetA() const {
	return a;
}

double Line::GetB() const {
	return b;
}

double Line::GetC() const {
	return c;
}

Circle::Circle(const Point& new_centre, double new_radius) {
	if (IsEqualDoubles(new_radius, 0) || new_radius < 0) {
		throw std::invalid_argument("Radius must be greater than 0");
	}

	centre = new_centre;
	radius = new_radius;
}

Point Circle::GetCentre() const {
	return centre;
}

double Circle::GetRadius() const {
	return radius;
}

double Line::CalculateY(double x) const {
	if (b == 0) {
		return 1;
	}
	return (-c - a * x) / b;
}


double DistanceBetweenPoints(const Point& p_1, const Point& p_2) {
	return sqrt((p_1.first - p_2.first) * (p_1.first - p_2.first) + (p_1.second - p_2.second) * (p_1.second - p_2.second));
}

Point IntersectionOfLines(const Line& line_1, const Line& line_2) {
	double determinant = line_1.GetA() * line_2.GetB() - line_1.GetB() * line_2.GetA();
	if (IsEqualDoubles(determinant, 0)) {
		return DEFAULT_POINT;
	}

	return { (line_1.GetB() * line_2.GetC() - line_2.GetB() * line_1.GetC()) / determinant,
			 (line_2.GetA() * line_1.GetC() - line_1.GetA() * line_2.GetC()) / determinant };
}



std::pair<Point, Point> IntersectionOfCircles(const Circle& circle_1, const Circle& circle_2) {
	std::pair<Point, Point> result = { DEFAULT_POINT,DEFAULT_POINT };
	double distance_between_centres = DistanceBetweenPoints(circle_1.GetCentre(), circle_2.GetCentre());

	if (distance_between_centres <= circle_1.GetRadius() + circle_2.GetRadius() &&
		distance_between_centres >= fabs(circle_1.GetRadius() - circle_2.GetRadius())) {

		const double first_radius = circle_1.GetRadius();
		const double second_radius = circle_2.GetRadius();
		const Point first_centre = circle_1.GetCentre();
		const Point second_centre = circle_2.GetCentre();

		double ex = (second_centre.first - first_centre.first) / distance_between_centres;
		double ey = (second_centre.second - first_centre.second) / distance_between_centres;

		double x = (first_radius * first_radius - second_radius * second_radius + distance_between_centres * distance_between_centres) / (2 * distance_between_centres);
		double y = sqrt(first_radius * first_radius - x * x);

		result.first = {
			first_centre.first + x * ex - y * ey,
			first_centre.second + x * ey + y * ex
		};

		result.second = {
			first_centre.first + x * ex + y * ey,
			first_centre.second + x * ey - y * ex
		};
	}

	return result;
}


Point ReflectPoint(const Point& to_reflect ,const Line& line) {
	Point intersection = IntersectionOfLines(line, line.GetPerpendicularLine(to_reflect));
	Point direction = { intersection.first - to_reflect.first, intersection.second - to_reflect.second };

	return {
		to_reflect.first + 2 * direction.first,
		to_reflect.second + 2 * direction.second
	};

}

Circle ReflectCircle(const Circle& to_reflect, const Line& line) {
	return { ReflectPoint(to_reflect.GetCentre(),line),to_reflect.GetRadius() };
}

Line ReflectLine(const Line& to_reflect, const Line& line) {
	Point p_1 = ReflectPoint({ 0,to_reflect.CalculateY(0) }, line);
	Point p_2 = ReflectPoint({ 1,to_reflect.CalculateY(1) }, line);

	return {p_1,p_2};
}

Point InversionOfPoint(const Point& to_inverse, const Circle& circle) {
	const Point centre = circle.GetCentre();
	const double radius = circle.GetRadius();
	double divider = (to_inverse.first - centre.first) * (to_inverse.first - centre.first) + (to_inverse.second - centre.second) * (to_inverse.second - centre.second);

	return {
		centre.first + (radius * radius * (to_inverse.first - centre.first)) / divider,
		centre.second + (radius * radius * (to_inverse.second - centre.second)) / divider,
	};
}
