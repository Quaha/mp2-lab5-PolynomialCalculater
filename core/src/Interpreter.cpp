#include "includes.hpp"

#include "PrefixTree.hpp"
#include "Automat.hpp"
#include "Interpreter.hpp"
#include "functions.hpp"
#include "Data.hpp"
#include "ProgramMemory.hpp"

void processTypesOfSymbols(Interpreter::LexicalAnalyzer& analyzer) {

	// Allowed symbols
	for (char C = 'a'; C <= 'z'; ++C) {
		analyzer.allowed_symbols.insert(C);
	}
	for (char C = 'A'; C <= 'Z'; ++C) {
		analyzer.allowed_symbols.insert(C);
	}
	for (char C = '0'; C <= '9'; ++C) {
		analyzer.allowed_symbols.insert(C);
	}
	analyzer.allowed_symbols.insert('_');
	analyzer.allowed_symbols.insert('(');
	analyzer.allowed_symbols.insert(')');
	analyzer.allowed_symbols.insert(';');
	analyzer.allowed_symbols.insert(',');

	analyzer.allowed_symbols.insert('+');
	analyzer.allowed_symbols.insert('-');
	analyzer.allowed_symbols.insert('*');
	analyzer.allowed_symbols.insert('/');
	analyzer.allowed_symbols.insert('=');

	analyzer.allowed_symbols.insert('.');

	// Degits symbols
	for (char C = '0'; C <= '9'; ++C) {
		analyzer.digits_symbols.insert(C);
	}

	// Names symbols
	for (char C = 'a'; C <= 'z'; ++C) {
		analyzer.names_symbols.insert(C);
	}
	for (char C = 'A'; C <= 'Z'; ++C) {
		analyzer.names_symbols.insert(C);
	}
	analyzer.names_symbols.insert('_');

	// Separating symbols (They are not counted among the allowed ones)
	analyzer.separating_characters.insert(' ');
	analyzer.separating_characters.insert('`');

	// Operators symbols
	analyzer.operators_symbols.insert('+');
	analyzer.operators_symbols.insert('-');
	analyzer.operators_symbols.insert('*');
	analyzer.operators_symbols.insert('/');
	analyzer.operators_symbols.insert('=');
}

void buildLexicalAnalyzerAutomat(Interpreter::LexicalAnalyzer& analyzer) {
	//Automat states

	analyzer.tokens_aut.setStateStatus(0, NONE);

	analyzer.tokens_aut.setStateStatus(10, OPERATOR);

	analyzer.tokens_aut.setStateStatus(20, VARIABLE);
	analyzer.tokens_aut.setStateStatus(21, VARIABLE);

	analyzer.tokens_aut.setStateStatus(30, FUNCTION);

	analyzer.tokens_aut.setStateStatus(40, REAL);
	analyzer.tokens_aut.setStateStatus(41, REAL);
	analyzer.tokens_aut.setStateStatus(42, ERROR);
	analyzer.tokens_aut.setStateStatus(43, REAL);

	analyzer.tokens_aut.setStateStatus(50, ERROR);
	analyzer.tokens_aut.setStateStatus(51, ERROR);
	analyzer.tokens_aut.setStateStatus(52, ERROR);
	analyzer.tokens_aut.setStateStatus(53, ERROR);
	analyzer.tokens_aut.setStateStatus(54, ERROR);
	analyzer.tokens_aut.setStateStatus(55, ERROR);
	analyzer.tokens_aut.setStateStatus(56, ERROR);
	analyzer.tokens_aut.setStateStatus(57, ERROR);
	analyzer.tokens_aut.setStateStatus(58, ERROR);
	analyzer.tokens_aut.setStateStatus(59, POLYNOMIAL);
	analyzer.tokens_aut.setStateStatus(60, POLYNOMIAL);

	analyzer.tokens_aut.setStateStatus(99, ERROR);

	{ // 0
		analyzer.tokens_aut.addTransition(0, 41, '0');
		for (char C = '1'; C <= '9'; C++) {
			analyzer.tokens_aut.addTransition(0, 40, C);
		}
		analyzer.tokens_aut.addTransition(0, 30, '(');
		analyzer.tokens_aut.addTransition(0, 30, ',');
		analyzer.tokens_aut.addTransition(0, 30, ')');

		for (char C: analyzer.names_symbols) {
			analyzer.tokens_aut.addTransition(0, 20, C);
		}

	}

	{ // 10

	}

	{ // 20
		for (char C : analyzer.names_symbols) {
			analyzer.tokens_aut.addTransition(20, 20, C);
		}
		for (char C : analyzer.digits_symbols) {
			analyzer.tokens_aut.addTransition(20, 20, C);
		}
		analyzer.tokens_aut.addTransition(20, 30, '(');
	}

	{ // 30

	}


	// General errors transitions
	for (int i = 0; i < analyzer.tokens_aut.nodes.size(); i++) {
		for (char C : analyzer.allowed_symbols) {
			if (!analyzer.tokens_aut.transitionExists(i, C)) {
				analyzer.tokens_aut.addTransition(i, 99, C);
			}
		}
	}

}

Interpreter::LexicalAnalyzer::LexicalAnalyzer(): tokens_aut(100) {
	processTypesOfSymbols(*this);
	buildLexicalAnalyzerAutomat(*this);
}

vector<Data> Interpreter::LexicalAnalyzer::divideIntoTokens(const string& line) const {
	string correct_line = "";
	for (char C : line) {
		if (separating_characters.count(C)) {
			continue;
		}
		else if (!allowed_symbols.count(C)) {
			throw std::runtime_error("ERROR: a forbidden symbol has been used!");
		}
		else {
			correct_line.push_back(C);
		}
	}
	correct_line.push_back(';');

	vector<Data> tokens(0);

	int curr_state = 0;
	string stack;
	
	for (int curr_position = 0; curr_position < correct_line.size(); ++curr_position) {
		char C = correct_line[curr_position];

		int next_state = tokens_aut.getNextState(curr_state, C);

		int curr_status = tokens_aut.getStatus(curr_state);
		int next_status = tokens_aut.getStatus(next_state);


		if (next_status == ERROR) {
			type curr_status = tokens_aut.getStatus(curr_state);
			if (curr_status == NONE) {
				throw std::runtime_error("ERROR: a lexical error!");
			}
			else if (curr_status == INTEGER ||
					 curr_status == REAL ||
					 curr_status == SPECIAL_SYMBOL ||
					 curr_status == OPERATOR){
				
				tokens.push_back(Data(curr_status, stack));
			}
			else if (curr_status == VARIABLE) {
				
				if (!global_memory->program_data.isExist(stack)) {
					tokens.push_back(Data(VARIABLE, stack));
				}
				else {
					type variable_type = global_memory->program_data.getData(stack).getType();
					if (variable_type == INTEGER) {
						tokens.push_back(Data(INTEGER_VARIABLE, stack));
					}
					else if (variable_type == REAL) {
						tokens.push_back(Data(REAL_VARIABLE, stack));
					}
					else {
						throw std::runtime_error("ERROR: invalid variable type!");
					}
				}
			}
			else if (curr_status == FUNCTION) {
				if (!global_memory->function_data.isExist(stack)) {
					throw std::runtime_error("ERROR: a nonexistent function was found!");
				}
				else {
					tokens.push_back(Data(FUNCTION, stack));
				}
			}
			else if (curr_status == ERROR) {
				throw std::runtime_error("ERROR: something went wrong!");
			}
			else {
				throw std::runtime_error("ERROR: unknown type in lexical analyzer!");
			}
			stack.clear();
			curr_state = 0;
			curr_position--;
		}
		else {
			curr_state = next_state;
			stack.push_back(C);
		}

		if (C == ';') break;

	}
	return tokens;
}

Interpreter::SerialAnalyzer::SerialAnalyzer() {

	allowed.resize(STATUSES_COUNT);
	for (int i = 0; i < STATUSES_COUNT; i++) {
		allowed[i].resize(STATUSES_COUNT, true);
	}

	vector<type> values_statuses = { INTEGER, REAL, INTEGER_VARIABLE, REAL_VARIABLE, VARIABLE };
	for (int i = 0; i < values_statuses.size(); i++) {
		for (int j = 0; j < values_statuses.size(); j++) {
			allowed[i][j] = false;
		}
	}

	allowed[OPERATOR][OPERATOR] = false;

	for (int i = 0; i < values_statuses.size(); i++) {
		allowed[i][FUNCTION] = false;
	}

}

void Interpreter::SerialAnalyzer::checkTokens(const vector<Data>& tokens) const {
	for (int i = 0; i < (int)tokens.size() - 1; i++) {
		if (!allowed[tokens[i].getType()][tokens[i + 1].getType()]) {
			throw std::runtime_error("ERROR: wrong sequence of tokens!");
		}
	}
}

void processFunctionData() {
	global_memory->function_data.setWord("(", std::make_shared<function_type>(__LEFT__BRACKET__OPERATOR__));
	global_memory->function_data.setWord("sum(", std::make_shared<function_type>(sum));
	global_memory->function_data.setWord("+", std::make_shared<function_type>(__PLUS__OPERATOR__));
	global_memory->function_data.setWord("-", std::make_shared<function_type>(__MINUS__OPERATOR__));
	global_memory->function_data.setWord("*", std::make_shared<function_type>(__MULTIPLY__OPERATOR__));
	global_memory->function_data.setWord("/", std::make_shared<function_type>(__DIVISION__OPERATOR__));
	global_memory->function_data.setWord("=", std::make_shared<function_type>(__EQUAL__OPERATOR__));

	global_memory->objects_priority.setWord("(", 0);
	global_memory->objects_priority.setWord("sum(", 0);
	global_memory->objects_priority.setWord("+", 100);
	global_memory->objects_priority.setWord("-", 100);
	global_memory->objects_priority.setWord("*", 200);
	global_memory->objects_priority.setWord("/", 200);
	global_memory->objects_priority.setWord("=", -100);

	global_memory->objects_priority.setWord(")", -100);
	global_memory->objects_priority.setWord(",", -100);
}

Interpreter::Interpreter() {
	global_memory = std::make_unique<MemoryManager>();

	processFunctionData();

}

void perform_stack(vector<Data>& values, vector<Data>& actions, vector<int>& stack_of_priorities, vector<int>& stack_of_counts, int curr_p) {
	while (!stack_of_priorities.empty() && stack_of_priorities.back() >= curr_p && !actions.empty() && actions.back().getType() == OPERATOR) {
		shared_ptr<function_type> function = global_memory->function_data.getData(actions.back().getData());
		actions.pop_back();
		stack_of_priorities.pop_back();

		vector<Data> parameters(0);

		if (values.empty()) {
			throw std::runtime_error("ERROR: incorrect input!");
		}

		parameters.push_back(values.back());
		values.pop_back();

		if (stack_of_counts.empty()) {
			throw std::runtime_error("ERROR: incorrect input!");
		}

		stack_of_counts.back()--;

		if (stack_of_counts.back() < 0) {
			throw std::logic_error("ERROR: something went wrong!");
		}

		if (stack_of_counts.back() > 0) {
			parameters.push_back(values.back());
			values.pop_back();
			stack_of_counts.back()--;
		}

		reverse(parameters.begin(), parameters.end());

		Data res = (*function)(parameters);
		values.push_back(res);
		stack_of_counts.back()++;
	}
}

Data Interpreter::execute(const string& line) {

	vector<Data> tokens = lexical_analyzer.divideIntoTokens(line);
	serial_analyzer.checkTokens(tokens);

	vector<Data> values(0);
	vector<Data> actions(0);
	vector<int> stack_of_priorities(0);
	vector<int> stack_of_counts(1, 0);

	for (int i = 0; i < tokens.size(); i++) {

		Data curr_token = tokens[i];

		if (curr_token.data == ")") {
			int b = 4;
		}

		if (curr_token.getType() == INTEGER ||
			curr_token.getType() == REAL ||
			curr_token.getType() == VARIABLE ||
			curr_token.getType() == INTEGER_VARIABLE ||
			curr_token.getType() == REAL_VARIABLE) {
			values.push_back(curr_token);

			if (stack_of_counts.empty()) {
				throw std::runtime_error("ERROR: incorrect input!");
			}

			stack_of_counts.back()++;
		}

		else if (curr_token.getType() == SPECIAL_SYMBOL) {
			int curr_priority = global_memory->objects_priority.getData(curr_token.getData());
			perform_stack(values, actions, stack_of_priorities, stack_of_counts, curr_priority);

			if (curr_token.getData() == ")") {
				vector<Data> parameters(0);

				if (values.empty()) {
					throw std::runtime_error("ERROR: incorrect input!");
				}
				if (stack_of_counts.empty()) {
					throw std::runtime_error("ERROR: incorrect input!");
				}
				if (actions.empty()) {
					throw std::runtime_error("ERROR: incorrect input!");
				}

				parameters.push_back(values.back());
				values.pop_back();
				stack_of_counts.pop_back();
				while (actions.back().getData() == ",") {
					actions.pop_back();

					if (values.empty()) {
						throw std::runtime_error("ERROR: incorrect input!");
					}
					if (stack_of_counts.empty()) {
						throw std::runtime_error("ERROR: incorrect input!");
					}
					if (actions.empty()) {
						throw std::runtime_error("ERROR: incorrect input!");
					}

					parameters.push_back(values.back());
					values.pop_back();
					stack_of_counts.pop_back();
					stack_of_priorities.pop_back();
				}
				reverse(parameters.begin(), parameters.end());

				if (actions.empty()) {
					throw std::runtime_error("ERROR: incorrect input!");
				}

				shared_ptr<function_type> function = global_memory->function_data.getData(actions.back().getData());
				actions.pop_back();
				stack_of_priorities.pop_back();
				Data result = (*function)(parameters);
				values.push_back(result);
				stack_of_counts.back()++;
			}
			if (curr_token.getData() == ",") {
				actions.push_back(curr_token);
				stack_of_priorities.push_back(curr_priority);
				stack_of_counts.push_back(0);
			}
		}

		else if (curr_token.getType() == FUNCTION) {
			int curr_priority = global_memory->objects_priority.getData(curr_token.getData());
			stack_of_priorities.push_back(curr_priority);
			stack_of_counts.push_back(0);
			actions.push_back(curr_token);
		}

		else if (curr_token.getType() == OPERATOR) {
			int curr_priority = global_memory->objects_priority.getData(curr_token.getData());
			perform_stack(values, actions, stack_of_priorities, stack_of_counts, curr_priority);
			if (stack_of_counts.back() == 0) {
				curr_priority = 1000;
			}
			stack_of_priorities.push_back(curr_priority);
			actions.push_back(curr_token);
		}

		else {
			throw std::invalid_argument("ERROR: unknown token type!");
		}
	}

	perform_stack(values, actions, stack_of_priorities, stack_of_counts, -1000);

	if (!actions.empty() || values.size() != 1) {
		throw std::runtime_error("ERROR: something went wrong!");
	}

	return convertToValue(values[0]);
	return Data();
}
