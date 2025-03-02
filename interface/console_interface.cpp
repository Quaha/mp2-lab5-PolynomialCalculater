#include <iostream>

#include "Interpreter.hpp"

int main() {
	
	Interpreter program;

	while (true) {
		try {
			std::string line;
			getline(std::cin, line);

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