#include "includes.hpp"

#include "Automat.hpp"

Automat::Automat() {
	nodes.push_back(Node(NONE));
}

Automat::Automat(size_t size) {
	for (size_t i = 0; i < size; ++i) {
		nodes.push_back(Node(NONE));
	}
}

bool Automat::nextStateExist(int curr_state, char C) const {
	return nodes[curr_state].next.count(C);
}

void Automat::createNextState(int curr_state, char C, type status) {
	nodes[curr_state].next[C] = nodes.size();
	nodes.push_back(Node(status));
}

bool Automat::transitionExists(int curr_state, char C) const {
	return nodes[curr_state].next.count(C);
}

void Automat::createNewState(type status) {
	nodes.push_back(Node(status));
}

void Automat::setStateStatus(int curr_state, type status) {
	if (curr_state < 0 || curr_state >= nodes.size()) {
		throw std::out_of_range("The requested state is not in the automat!");
	}
	nodes[curr_state].status = status;
}

void Automat::addTransition(int curr_state, int next_state, char C) {
	if (curr_state < 0 || curr_state >= nodes.size()) {
		throw std::out_of_range("The requested state is not in the automat!");
	}
	if (next_state < 0 || next_state >= nodes.size()) {
		throw std::out_of_range("The requested state is not in the automat!");
	}
	if (nextStateExist(curr_state, C)) {
		throw std::out_of_range("Such a transition already exists in the automat!");
	}
	nodes[curr_state].next[C] = next_state;
}

int Automat::getNextState(int curr_state, char C) const {
	if (!nextStateExist(curr_state, C)) {
		throw std::out_of_range("The requested state is not in the automat!");
	}
	return (*nodes[curr_state].next.find(C)).second;
}

int Automat::getStatus(int curr_state) const {
	return nodes[curr_state].status;
}