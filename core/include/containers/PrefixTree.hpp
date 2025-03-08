#pragma once

#include "includes.hpp"

template<class TValue> class PrefixTree {
protected:
	struct Node {
		map<char, int> next;
		TValue data;
		bool is_terminal = false;
	};

	vector<Node> nodes;

	void createNextState(int curr_state, char C) {
		nodes[curr_state].next[C] = (int)nodes.size();
		nodes.push_back(Node());
	}

	bool nextStateExist(int curr_state, char C) const {
		return (nodes[curr_state].next.find(C) != nodes[curr_state].next.end());
	}

	int getNextState(int curr_state, char C) const {
		if (!nextStateExist(curr_state, C)) {
			throw std::out_of_range("The requested state is not in the prefix tree!");
		}
		return (*nodes[curr_state].next.find(C)).second;
	}

public:

	PrefixTree() {
		nodes.push_back(Node());
	}

	void insert(const string& S, const TValue &data) {
		int curr_state = 0;
		for (char C : S) {
			if (!nextStateExist(curr_state, C)) {
				createNextState(curr_state, C);
			}
			curr_state = getNextState(curr_state, C);
		}
		nodes[curr_state].data = data;
		nodes[curr_state].is_terminal = true;
	}

	bool isExist(const string& S) const {
		int curr_state = 0;
		for (char C : S) {
			if (!nextStateExist(curr_state, C)) {
				return false;
			}
			curr_state = getNextState(curr_state, C);
		}
		return nodes[curr_state].is_terminal;
	}

	TValue getData(const string& S) const {
		int curr_state = 0;
		for (char C : S) {
			if (!nextStateExist(curr_state, C)) {
				throw std::out_of_range("The requested word is not in the prefix tree!");
			}
			curr_state = getNextState(curr_state, C);
		}
		return nodes[curr_state].data;
	}
};