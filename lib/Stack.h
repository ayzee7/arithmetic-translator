#pragma once
#include <vector>

template <class T, class TCont = std::vector<T>>
class Stack {
	TCont data;
	
public:
	Stack() {}

	void push(T elem) {
		data.push_back(elem);
	}

	T pop() {
		T res = top();
		data.pop_back();
		return res;
	}

	T& top() {
		return data[data.size() - 1];
	}

	void clear() {
		data.clear();
	}

	size_t size() {
		return data.size();
	}

	bool empty() {
		return data.empty();
	}
};