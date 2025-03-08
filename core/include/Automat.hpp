#pragma once

#include <vector>
#include <map>

struct Automat {
	struct Node {
		std::map<char, int> next;
		type status;
		Node(type status) : status(status) {};
	};

	std::vector<Node> nodes;

	Automat();
	Automat(size_t size);

	bool nextStateExist(int curr_state, char C) const;
	void createNextState(int curr_state, char C, type status);
	bool transitionExists(int curr_state, char C) const;

	void createNewState(type status);
	void setStateStatus(int curr_state, type status);
	void addTransition(int curr_state, int next_state, char C);
	int getNextState(int curr_state, char C) const;
	int getStatus(int curr_state) const;
};