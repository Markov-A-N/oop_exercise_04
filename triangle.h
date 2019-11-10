#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <utility>
#include <iostream>

#include "vector.h"
#include "vertex.h"

template<typename T>
struct Triangle {
	using vertex_t = std::pair<T,T>;
	vertex_t vertices[3];
};

template<typename T>
typename Triangle<T>::vertex_t Center(const Triangle<T> &t);

template<typename T>
double Area(const Triangle<T> &t);

template<typename T>
std::ostream &Print(std::ostream &os, const Triangle<T> &t);

template<typename T>
std::istream &Read(std::istream &is, Triangle<T> &t);

template<typename T>
std::istream &operator>>(std::istream &is, Triangle<T> &t);

template<typename T>
std::ostream &operator<<(std::ostream &os, const Triangle<T> &t);

template<typename T>
typename Triangle<T>::vertex_t Center(const Triangle<T> &t) {
	T x, y;
	x = (t.vertices[0].first + t.vertices[1].first + t.vertices[2].first) / 3;
	y = (t.vertices[0].second + t.vertices[1].second + t.vertices[2].second) / 3;

	return std::make_pair(x, y);
}

template<typename T>
double Area(const Triangle<T> &t) {
	double res = 0;
	for (int i = 0; i <= 1; i++) {
		res += (t.vertices[i].first * t.vertices[i + 1].second -
				t.vertices[i + 1].first * t.vertices[i].second); 
	}
	res += (t.vertices[2].first * t.vertices[0].second -
			t.vertices[0].first * t.vertices[2].second);
	res = 0.5 * std::abs(res);

	return res;
}

template<typename T>
std::ostream &Print(std::ostream &os, const Triangle<T> &t) {
	for (int i = 0; i < 3; i++) {
		os << t.vertices[i];
		if (i != 2) {
			os << " ";
		} 
	}

	return os;
}

template<typename T>
std::istream &Read(std::istream &is, Triangle<T> &t) {
	for (int i = 0; i < 3; i++) {
		is >> t.vertices[i].first >> t.vertices[i].second;
	}
	double AB = Length(t.vertices[0], t.vertices[1]), 
		   BC = Length(t.vertices[1], t.vertices[2]),
		   AC = Length(t.vertices[0], t.vertices[2]);
	if (AB >= BC + AC || BC >= AB + AC || AC >= AB + BC) {
		throw std::logic_error("Vertices must not be on the same line.");
	}

	return is;
}

template<typename T>
std::istream &operator>>(std::istream &is, Triangle<T> &t) {
	return Read(is, t);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Triangle<T> &t) {
	return Print(os, t);
}

#endif // TRIANGLE_H