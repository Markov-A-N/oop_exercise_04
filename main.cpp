#include <iostream>
#include <cstring>
#include <exception>
#include "rectangle.h"
#include "square.h"
#include "triangle.h"
#include "vector.h"
#include "templates.h"

template<typename T>
using vertex_t = std::pair<T, T>;

template<typename T>
void process() {
	T object;
	std::cout << "Input points: ";
	try {
		Read(std::cin, object);
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return;
	}
	Print(std::cout, object);
	std::cout << std::endl<< Area(object) << std::endl;
	std::cout << Center(object) << std::endl;
}

int main() {
	std::string command;
	std::cout << "Figure / Tuple" << std::endl;
	std::cout << "______________________________________" << std::endl;
	while (std::cin >> command) {
		std::string object_type;
		if (command == "Figure") {
			std::cout << "______________________________________" << std::endl;
			std::cout << "Triangle / Square / Rectangle" << std::endl;
			std::cout << "______________________________________" << std::endl;
			std::cin >> object_type;
			std::cout << "______________________________________" << std::endl;
			if (object_type == "Triangle") {
				process<Triangle<double>>();
			}
			else if (object_type == "Square") {
				process<Square<double>>();
			}
			else if (object_type == "Rectangle") {
				process<Rectangle<double>>();
			}
			else {
				std::cout << "Invalid figure" << std::endl;
				std::cin.clear();
				std::cin.ignore(30000, '\n');
				std::cout << "______________________________________" << std::endl;
				std::cout << "Figure / Tuple" << std::endl;
				std::cout << "______________________________________" << std::endl;
				continue;
			}
		}
		else if (command == "Tuple") {
			std::cout << "______________________________________" << std::endl;
			std::cout << "Triangle / Square / Rectangle" << std::endl;
			std::cout << "______________________________________" << std::endl;
			std::cin >> object_type;
			std::cout << "______________________________________" << std::endl;
			if (object_type == "Triangle") {
				process<std::tuple<vertex_t<double>, vertex_t<double>, 
									vertex_t<double>>>();
			}
			else if (object_type == "Square") {
				process<std::tuple<vertex_t<double>, vertex_t<double>>>();
			}
			else if (object_type == "Rectangle") {
				process<std::tuple<vertex_t<double>, vertex_t<double>,
									vertex_t<double>, vertex_t<double>>>();
			}
			else {
				std::cout << "Invalid figure" << std::endl;
				std::cin.clear();
				std::cin.ignore(30000, '\n');
				std::cout << "______________________________________" << std::endl;
				std::cout << "Figure / Tuple" << std::endl;
				std::cout << "______________________________________" << std::endl;
				continue;
			}
		}
		else {
			std::cout << "Invalid command" << std::endl;
			std::cin.clear();
			std::cin.ignore(30000, '\n');
			std::cout << "______________________________________" << std::endl;
			continue;
		}
		std::cout << "______________________________________" << std::endl;
		std::cout << "Figure / Tuple" << std::endl;
		std::cout << "______________________________________" << std::endl;
	}

	return 0;
}