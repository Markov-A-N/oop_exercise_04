#ifndef VECTOR_H
#define VECTOR_H 1

#include <utility>
#include <cmath>
#include <iostream>

#include "vertex.h"

template<typename T> 
struct Vector {
	using vertex_t = std::pair<T, T>;
	T p1, p2;

	Vector(T x_cord, T y_cord) : p1{x_cord}, p2{y_cord} {};
	Vector(vertex_t &p1, vertex_t &p2) : p1{p2.first - p1.first},
				p2{p2.second - p1.second} {};
	double operator*(const Vector<T> &a) const {
		return (p1 * a.p1) + (p2 * a.p2);
	}
	Vector<T> &operator=(const Vector<T> &a) {
		p1 = a.p1;
		p2 = a.p2;
		return *this;
	}
};

template<typename T>
double Length(const Vector<T> &vector) {
	return sqrt(vector.p1 * vector.p1 + vector.p2 * vector.p2);
}

template<typename T>
double Length(const std::pair<T, T> &A, 
			  const std::pair<T, T> &B) {
	return sqrt(pow((B.first - A.first), 2) + 
				pow((B.second - A.second), 2));
}

template<typename T>
bool is_parallel(const Vector<T> &A, const Vector<T> &B) {
	return (A.p1 * B.p2) - (A.p2 * B.p1) == 0;
}

#endif //VECTOR_H