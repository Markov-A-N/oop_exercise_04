#ifndef D_TEMPLATES_H
#define D_TEMPLATES_H 1

#include <tuple>
#include <utility>
#include <type_traits>
#include <exception>


#include "vector.h"

template<typename T>
using vertex_t = std::pair<T, T>;

template<typename T>
struct is_vertex : std::false_type {};

template<typename T>
struct is_vertex<std::pair<T, T>> : std::true_type {};

template<class T>
struct is_figurelike_tuple : std::false_type {};

template<class Head, class... Tail>
struct is_figurelike_tuple<std::tuple<Head, Tail...>> :
std::conjunction<is_vertex<Head>,
        std::is_same<Head, Tail>...> {};

template<typename T>
inline constexpr bool is_figurelike_tuple_v = is_figurelike_tuple<T>::value;

template<typename T, typename = void>
struct has_method_area : std::false_type {};

template<typename T>
struct has_method_area<T, decltype(std::declval<const T&>().Area())> : 
	std::true_type {};

template<typename T>
inline constexpr bool has_method_area_v = has_method_area<T>::value;

template<typename T>
std::enable_if_t<has_method_area_v<T>, double>
Area(const T& object) {
	return object.Area();
}

template<typename T, typename = void>
struct has_method_center : std::false_type {};

template<typename T>
struct has_method_center<T, decltype(std::declval<const T&>().Center())> :
	std::true_type {};

template<typename T>
inline constexpr bool has_method_center_v = has_method_center<T>::value;

template<typename T>
std::enable_if_t<has_method_center_v<T>, vertex_t<double>>
Center(const T& object) {
	return object.Center();
}

template<typename T, typename = void>
struct has_method_print : std::false_type {};

template<typename T>
struct has_method_print<T, decltype(std::declval<const T&>().Print())> :
	std::true_type {};

template<typename T>
inline constexpr bool has_method_print_v = has_method_print<T>::value;

template<typename T>
std::enable_if_t<has_method_print_v<T>, std::ostream &>
Print(std::ostream &os, const T& object) {
	return Print(os, object);
}

template<typename T, typename = void>
struct has_method_read : std::false_type {};

template<typename T>
struct has_method_read<T, decltype(std::declval<const T&>().Read())> :
	std::true_type {};

template<typename T>
inline constexpr bool has_method_read_v = has_method_read<T>::value;

template<typename T>
std::enable_if_t<has_method_read_v<T>, std::istream &>
Read(std::istream &is, T& object) {
	return Read(is, object);
}

template<size_t Id, typename T>
double compute_area(const T &tuple) {
	if constexpr(Id >= std::tuple_size_v<T>) {
		return 0;
	}
	else {
		const auto dx1 = std::get<Id - 0>(tuple).first - std::get<0>(tuple).first;
		const auto dy1 = std::get<Id - 0>(tuple).second - std::get<0>(tuple).second;
		const auto dx2 = std::get<Id - 1>(tuple).first - std::get<0>(tuple).first;
		const auto dy2 = std::get<Id - 1>(tuple).second - std::get<0>(tuple).second;
		const double local_area = std::abs(dx1 * dy2 - dy1 * dx2) * 0.5;
		return local_area + compute_area<Id + 1>(tuple);
	}
}

template<typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, double>
Area(const T& object) {
	if constexpr (std::tuple_size_v<T> < 3){
		return 0;
	}
	else{
		return compute_area<2>(object);
	}
}

template<size_t Id, typename T>
double recursive_center_x(const T &tuple) {
	if constexpr (Id >= std::tuple_size_v<T>) {
		return 0;
	}
	else {
		return (std::get<Id>(tuple).first / std::tuple_size_v<T>) + recursive_center_x<Id + 1>(tuple);
	}
}

template<size_t Id, typename T>
double recursive_center_y(const T &tuple) {
	if constexpr (Id >= std::tuple_size_v<T>) {
		return 0;
	}
	else {
		return (std::get<Id>(tuple).second / std::tuple_size_v<T>) + recursive_center_y<Id + 1>(tuple);
	}
}


template<size_t Id, typename T>
vertex_t<double> compute_center(const T &tuple) {
	if constexpr (Id >= std::tuple_size_v<T>) {
		return 0;
	}
	else {
		return {recursive_center_x<Id>(tuple), recursive_center_y<Id>(tuple)} ;
	}
}

template<typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, vertex_t<double>>
Center(const T& object) {
	return compute_center<0>(object);
}

template<size_t Id, typename T>
void recursive_print(std::ostream &os, const T &tuple) {
	if constexpr (Id >= std::tuple_size_v<T>) {
		return;
	}
	else {
		os << std::get<Id>(tuple) << " ";
		recursive_print<Id + 1>(os, tuple);
	}
}

template<typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
Print(std::ostream &os, const T& object) {
	recursive_print<0>(os, object);
}

template<typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
Check_triangle(T& object) {
	double AB = Length(std::get<0>(object), std::get<1>(object)),
			BC = Length(std::get<1>(object), std::get<2>(object)),
			AC = Length(std::get<0>(object), std::get<2>(object));
	if (AB >= BC + AC || BC >= AB + AC || AC >= AB + BC) {
		throw std::logic_error("Vertices must not be on the same line.");
	}
}

template<typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, bool>
Check_rectangle(T& object) {
	Vector<decltype(std::get<0>(object).first)> AB = {std::get<0>(object), std::get<1>(object)},
			BC = {std::get<1>(object), std::get<2>(object)},
			CD = {std::get<2>(object), std::get<3>(object)},
			DA = {std::get<3>(object), std::get<0>(object)};
	if (!is_parallel(DA, BC) || !is_parallel(AB, CD)) {
		throw std::logic_error("Vertices must be entered clockwise or counterclockwise");
	}
	if (AB * BC || BC * CD || CD * DA || DA * AB) {
		throw std::logic_error("The sides should be perpendicular");
	} 
	if (!Length(AB) || !Length(BC) || !Length(CD) || !Length(DA)) {
		throw std::logic_error("The sides must be greater than zero");
	}

	return true;
}

template<typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
Check(T& object) {
	if constexpr (std::tuple_size_v<T> == 3) {
		Check_triangle(object);
	}
	else if (std::tuple_size_v<T> == 4) {
		Check_rectangle(object);
	}
}

template<size_t Id, typename T>
void recursive_read(std::istream &is, T &tuple) {
	if constexpr (Id >= std::tuple_size_v<T>) {
		return;
	}
	else {
		is >> std::get<Id>(tuple);
		recursive_read<Id + 1>(is, tuple);
	}
}

template<typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
Read(std::istream &is, T& object) {
	recursive_read<0>(is, object);
	Check(object);
}


#endif // D_TEMPLATES_H