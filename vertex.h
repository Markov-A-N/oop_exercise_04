#ifndef VERTEX_H
#define VERTEX_H 1

template<typename T>
struct vertex {
	using vertex_t = std::pair<T, T>;
};

template<typename T>
std::istream &operator>>(std::istream &is, std::pair<T, T> &v) {
	is >> v.first >> v.second;

	return is;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::pair<T,T> &v) {
	os << "[" << v.first << ", " << v.second << "]";

	return os;
}

#endif // VERTEX_H