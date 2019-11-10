#ifndef SQUARE_H
#define SQUARE_H 1

#include <utility>
#include <iostream>

#include "vector.h"

template<typename T>
struct Square {
	using vertex_t = std::pair<T,T>;
	vertex_t vertices[4];
};

template<typename T>
typename Square<T>::vertex_t Center(const Square<T> &s);

template<typename T>
double Area(const Square<T> &s);

template<typename T>
std::ostream &Print(std::ostream &os, const Square<T> &s);

template<typename T>
std::istream &Read(std::istream &is, Square<T> &s);

template<typename T>
std::istream &operator>>(std::istream &is, Square<T> &s);

template<typename T>
std::ostream &operator<<(std::ostream &os, const Square<T> &s);

template<typename T>
typename Square<T>::vertex_t Center(const Square<T> &s) {
	T x, y;
	x = (s.vertices[0].first + s.vertices[1].first + s.vertices[2].first + s.vertices[3].first) / 4;
	y = (s.vertices[0].second + s.vertices[1].second + s.vertices[2].second + s.vertices[3].second) / 4;

	return std::make_pair(x, y);
}

template<typename T>
double Area(const Square<T> &s) {
	double res = 0;
	for (int i = 0; i <= 2; i++) {
		res += (s.vertices[i].first * s.vertices[i + 1].second -
				s.vertices[i + 1].first * s.vertices[i].second); 
	}
	res += (s.vertices[2].first * s.vertices[0].second -
			s.vertices[0].first * s.vertices[2].second);
	res = 0.5 * std::abs(res);

	return res;
}

template<typename T>
std::ostream &Print(std::ostream &os, const Square<T> &s) {
	for (int i = 0; i < 4; i++) {
		os << s.vertices[i];
		if (i != 3) {
			os << " ";
		} 
	}

	return os;
}

template<typename T>
std::istream &Read(std::istream &is, Square<T> &s) {
	for (int i = 0; i < 4; i++) {
		is >> s.vertices[i].first >> s.vertices[i].second; 
	}
	Vector<T> AB = {s.vertices[0], s.vertices[1]}, 
		   BC = {s.vertices[1], s.vertices[2]},
		   CD = {s.vertices[2], s.vertices[3]},
		   DA = {s.vertices[3], s.vertices[0]};
	if (!is_parallel(DA, BC)) {
		std::swap(s.vertices[0], s.vertices[1]);
		AB = {s.vertices[0], s.vertices[1]}; 
	    BC = {s.vertices[1], s.vertices[2]};
	    CD = {s.vertices[2], s.vertices[3]};
	    DA = {s.vertices[3], s.vertices[0]};
	}
	if (!is_parallel(AB, CD)) {
		std::swap(s.vertices[1], s.vertices[2]);
		AB = {s.vertices[0], s.vertices[1]}; 
	    BC = {s.vertices[1], s.vertices[2]};
	    CD = {s.vertices[2], s.vertices[3]};
	    DA = {s.vertices[3], s.vertices[0]};
	}
	if (AB * BC || BC * CD || CD * DA || DA * AB) {
		throw std::logic_error("The sides of the square should be perpendicular");
	} 
	if (Length(AB) != Length(BC) || Length(BC) != Length(CD) || Length(CD) != Length(DA) || Length(DA) != Length(AB)) {
		throw std::logic_error("The sides of the square should be equal");
	}
	if (!Length(AB) || !Length(BC) || !Length(CD) || !Length(DA)) {
		throw std::logic_error("The sides of the square must be greater than zero");
	}
		   

	return is;
}

template<typename T>
std::istream &operator>>(std::istream &is, Square<T> &s) {
	return Read(is, s);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Square<T> &s) {
	return Print(os, s);
}

#endif // SQUARE_H