#ifndef RECTANGLE_H
#define RECTANGLE_H 1

#include <utility>
#include <iostream>

#include "vector.h"
#include "vertex.h"

template<typename T>
struct Rectangle {
	using vertex_t = std::pair<T,T>;
	vertex_t vertices[4];
};

template<typename T>
typename Rectangle<T>::vertex_t Center(const Rectangle<T> &r);

template<typename T>
double Area(const Rectangle<T> &r);

template<typename T>
std::ostream &Print(std::ostream &os, const Rectangle<T> &r);

template<typename T>
std::istream &Read(std::istream &is, Rectangle<T> &r);

template<typename T>
std::istream &operator>>(std::istream &is, Rectangle<T> &r);

template<typename T>
std::ostream &operator<<(std::ostream &os, const Rectangle<T> &r);

template<typename T>
typename Rectangle<T>::vertex_t Center(const Rectangle<T> &r) {
	T x, y;
	x = (r.vertices[0].first + r.vertices[1].first + r.vertices[2].first + r.vertices[3].first) / 4;
	y = (r.vertices[0].second + r.vertices[1].second + r.vertices[2].second + r.vertices[3].second) / 4;

	return std::make_pair(x, y);
}

template<typename T>
double Area(const Rectangle<T> &r) {
	double res = 0;
	for (int i = 0; i <= 2; i++) {
		res += (r.vertices[i].first * r.vertices[i + 1].second -
				r.vertices[i + 1].first * r.vertices[i].second); 
	}
	res += (r.vertices[2].first * r.vertices[0].second -
			r.vertices[0].first * r.vertices[2].second);
	res = 0.5 * std::abs(res);

	return res;
}

template<typename T>
std::ostream &Print(std::ostream &os, const Rectangle<T> &r) {
	for (int i = 0; i < 4; i++) {
		os << r.vertices[i];
		if (i != 3) {
			os << " ";
		} 
	}

	return os;
}

template<typename T>
std::istream &Read(std::istream &is, Rectangle<T> &r) {
	for (int i = 0; i < 4; i++) {
		is >> r.vertices[i].first >> r.vertices[i].second; 
	}
	Vector<T> AB = {r.vertices[0], r.vertices[1]}, 
		   BC = {r.vertices[1], r.vertices[2]},
		   CD = {r.vertices[2], r.vertices[3]},
		   DA = {r.vertices[3], r.vertices[0]};
	if (!is_parallel(DA, BC)) {
		std::swap(r.vertices[0], r.vertices[1]);
		AB = {r.vertices[0], r.vertices[1]}; 
	    BC = {r.vertices[1], r.vertices[2]};
	    CD = {r.vertices[2], r.vertices[3]};
	    DA = {r.vertices[3], r.vertices[0]};
	}
	if (!is_parallel(AB, CD)) {
		std::swap(r.vertices[1], r.vertices[2]);
		AB = {r.vertices[0], r.vertices[1]}; 
	    BC = {r.vertices[1], r.vertices[2]};
	    CD = {r.vertices[2], r.vertices[3]};
	    DA = {r.vertices[3], r.vertices[0]};
	}
	if (AB * BC || BC * CD || CD * DA || DA * AB) {
		throw std::logic_error("The sides of the Rectangle should be perpendicular");
	} 
	if (!Length(AB) || !Length(BC) || !Length(CD) || !Length(DA)) {
		throw std::logic_error("The sides of the Rectangle must be greater than zero");
	}
		   

	return is;
}

template<typename T>
std::istream &operator>>(std::istream &is, Rectangle<T> &r) {
	return Read(is, r);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Rectangle<T> &r) {
	return Print(os, r);	
}

#endif // RECTANGLE_H