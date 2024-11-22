#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cctype>
#include <cmath>
#include "Stack.h"

using namespace std;

class Translator {

	enum {
		STATE_INIT,
		STATE_OPERAND,
		STATE_ERROR,
		STATE_NUM_DOUBLE,
		STATE_VAR,
		STATE_NUM_INT
	} STATES;

	string user_input;
	vector<pair<string, int>> int_variables;
	vector<pair<string, double>> double_variables;

	void assignment(string var_name, string var_value);

	vector<string> get_terms(string expr);

	int priority(string term);

	string compute_value(string expr);

	bool lvalue_analysis(string lvalue);

	bool expression_analysis(string expr);

	void output_result(string expr);

	bool check_variable_term(string term);

public:
	void execute();
};