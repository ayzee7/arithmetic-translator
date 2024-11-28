#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <exception>
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

	double assignment(string var_name, string var_value, bool is_test);

	double output_result(string expr, bool is_test);

	void lvalue_analysis(string lvalue);

	void expression_analysis(string expr);

	string compute_value(string expr);

	vector<string> get_terms(string expr);

	int priority(string term);

	bool check_variable_term(string term);

public:
	void execute();

	double test_execute(string input);
};