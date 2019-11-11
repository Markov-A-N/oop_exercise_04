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
	T cord;
	if (s.vertices[1].first - s.vertices[0].first != 0 && s.vertices[1].second - s.vertices[0].second != 0) {
		cord = (s.vertices[1].first - s.vertices[0].first) / 2;
		return std::make_pair(cord, cord);
	}
	else if (s.vertices[0].second - s.vertices[1].second == 0) {
		cord = (s.vertices[1].first - s.vertices[0].first) / 2;
		return std::make_pair(cord, s.vertices[0].second);
	}
	else {
		cord = (s.vertices[1].second - s.vertices[0].second) / 2;
		return std::make_pair(s.vertices[0].first, cord);
	}
}

template<typename T>
double Area(const Square<T> &s) {
	return 0.5 * Length(s.vertices[0], s.vertices[1]) * Length(s.vertices[0], s.vertices[1]);
}

template<typename T>
std::ostream &Print(std::ostream &os, const Square<T> &s) {
	if ((s.vertices[1].second - s.vertices[0].second != 0) && ((s.vertices[0].first - s.vertices[1].first) != 0)) {
		os << s.vertices[0] << " " << std::make_pair(s.vertices[0].first, s.vertices[0].second + (s.vertices[1].second - s.vertices[0].second)) << " ";
		os << s.vertices[1] << " " << std::make_pair(s.vertices[1].first, s.vertices[1].second + (s.vertices[0].second - s.vertices[1].second));
	} else if (s.vertices[0].second - s.vertices[1].second == 0) {
		os << s.vertices[0] << " " << std::make_pair(s.vertices[0].first + (s.vertices[1].first - s.vertices[0].first) / 2, 
														s.vertices[0].second + (s.vertices[1].first - s.vertices[0].first)  / 2) << " ";
		os << s.vertices[1] << " " << std::make_pair(s.vertices[0].first + (s.vertices[1].first - s.vertices[0].first) / 2, 
														s.vertices[0].second - (s.vertices[1].first - s.vertices[0].first) / 2) << " ";
	} else if ((s.vertices[0].first - s.vertices[1].first) == 0) {
		os << s.vertices[0] << " " << std::make_pair(s.vertices[0].first - (s.vertices[1].second - s.vertices[0].second) / 2, 
														s.vertices[0].second + (s.vertices[1].second - s.vertices[0].second) / 2) << " ";
		os << s.vertices[1] << " " << std::make_pair(s.vertices[0].first + (s.vertices[1].second - s.vertices[0].second) / 2, 
														s.vertices[0].second + (s.vertices[1].second - s.vertices[0].second) / 2) << " ";
	}

	return os;
}

template<typename T>
std::istream &Read(std::istream &is, Square<T> &s) {
	for (int i = 0; i < 2; i++) {
		is >> s.vertices[i].first >> s.vertices[i].second; 
	}
	if (s.vertices[0].first == s.vertices[1].first && s.vertices[0].second == s.vertices[1].second) {
		throw std::logic_error("Vertices must not match");
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