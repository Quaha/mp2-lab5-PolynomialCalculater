#include <iostream>

#include "Interpreter.hpp"

int main() {

	size_t container_type;

	while (true) {
		try {
			std::cout << "Enter the container type:" << std::endl;
			std::cout << "0 - Ordered Table" << std::endl;
			std::cout << "1 - Unordered Table" << std::endl;
			std::cout << "2 - AVL Tree" << std::endl;
			std::cout << "3 - RB Tree" << std::endl;
			std::cout << "4 - CA Hash Table" << std::endl;
			std::cout << "5 - OA Hash Table" << std::endl;

			std::cin >> container_type;

			if (container_type > 5) {
				throw std::out_of_range("Wrong container type!");
			}

			std::cout << std::endl;

			break;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}


	Interpreter program(container_type);

	while (true) {
		try {
			std::string line;
			getline(std::cin, line);

			if (line.empty()) {
				continue;
			}

			Data result = program.execute(line);
			if (result.data_type == POLYNOMIAL || result.data_type == REAL) {
				std::cout << ">> " << result.data << std::endl;
			}
			else if (result.data_type != NONE) {
				throw std::logic_error("ERROR: something went wrong!");
			}
		}
		catch (const std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}