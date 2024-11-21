#include "Translator.h"


void Translator::execute() {
	cout << "To exit, type in \"exit\"." << endl;
	while (true) {
		getline(cin, user_input);
		user_input.erase(remove_if(user_input.begin(), user_input.end(), isspace), user_input.end());	// removing spaces
		if (user_input == "exit") {
			break;
		}
		size_t equal_sign_pos = user_input.find('=');
		if (equal_sign_pos != user_input.npos) {
			assignment(user_input.substr(0, equal_sign_pos), user_input.substr(equal_sign_pos + 1, user_input.size()));
		}
		else {
			output_result(user_input);
		}
	}
}

void Translator::assignment(string var_name, string var_value) {
	if (!lvalue_analysis(var_name)) {		//starts with a letter or underscore
		cout << "Syntax error: invalid variable name." << endl;
		return;
	}
	if (!expression_analysis(var_value)) {
		cout << "Syntax error: invalid expression." << endl;
		return;
	}
	string val = compute_value(var_value);
	if (val == "error") {
		return;
	}
	if (val != "INF") {
		if (val.find('.') != val.npos) {
			double double_value = stod(val);
			auto insert_var = make_pair(var_name, double_value);
			bool flag = true;
			for (auto elem : double_variables) {
				if (elem.first == insert_var.first) {
					flag = false;
					elem.second = insert_var.second;
				}
			}
			for (auto elem = int_variables.begin(); elem != int_variables.end(); ++elem) {
				if ((*elem).first == insert_var.first) {
					int_variables.erase(elem);
					break;
				}
			}
			if (flag) {
				double_variables.push_back(insert_var);
			}
		}
		else {
			int int_value = stoi(val);
			auto insert_var = make_pair(var_name, int_value);
			bool flag = true;
			for (auto elem : int_variables) {
				if (elem.first == insert_var.first) {
					flag = false;
					elem.second = insert_var.second;
				}
			}
			for (auto elem = double_variables.begin(); elem != double_variables.end(); ++elem) {
				if ((*elem).first == insert_var.first) {
					double_variables.erase(elem);
					break;
				}
			}
			if (flag) {
				int_variables.push_back(insert_var);
			}
		}
	}
	else {
		cout << "Runtime error: can't divide by zero." << endl;
	}
	
}

void Translator::output_result(string expr) {
	if (!expression_analysis(expr)) {
		cout << "Syntax error: invalid expression." << endl;
		return;
	}
	string val = compute_value(expr);
	if (val == "error") {
		return;
	}
	if (val != "INF") {
		cout << val << endl;
	}
}

string Translator::compute_value(string expr) {
	Stack<string> operands;
	vector<string> terms = get_terms(expr);
	if (terms[0] == "error") {
		cout << "Syntax error: there is no such variable \'" << terms[1] << "\'." << endl;
		return "error";
	}
	vector<string> polish_form;

	for (auto term : terms) {
		if (isdigit(term[0])) {
			polish_form.push_back(term);
		}
		else if (isalpha(term[0]) || term[0] == '_') {
			for (auto elem : double_variables) {
				if (term == elem.first) {
					polish_form.push_back(to_string(elem.second));
					break;
				}
			}
			for (auto elem : int_variables) {
				if (term == elem.first) {
					polish_form.push_back(to_string(elem.second));
					break;
				}
			}
		}
		else if (term == ")") {
			while (operands.top() != "(") {
				polish_form.push_back(operands.pop());
			}
			operands.pop();
		}
		else if (term == "(") {
			operands.push(term);
		}
		else {
			if (operands.empty()) {
				operands.push(term);
			}
			else {
				while (priority(operands.top()) >= priority(term) && operands.top() != "(") {
					polish_form.push_back(operands.pop());
				}
				operands.push(term);
			}
		}
	}
	while (!operands.empty()) {
		polish_form.push_back(operands.pop());
	}

	bool is_double = false;
	for (auto elem : polish_form) {
		if (elem.find('.') != elem.npos) {
			is_double = true;
		}
	}

	string res;
	
	if (is_double) {
		Stack<double> stack;
		for (auto elem : polish_form) {
			if (isdigit(elem[0])) {
				stack.push(stod(elem));
			}
			else {
				double second = stack.pop();
				double first = stack.pop();
				char operand = *(elem.data());
				switch (operand) {
				case '+':
					stack.push(first + second);
					break;
				case '-':
					stack.push(first - second);
					break;
				case '*':
					stack.push(first * second);
					break;
				case '/':
					if (second == 0.0) {
						return "INF";
					}
					stack.push(first / second);
					break;
				}
			}
		}
		res = res + to_string(stack.top());
	}
	else {
		Stack<int> stack;
		for (auto elem : polish_form) {
			if (isdigit(elem[0])) {
				stack.push(stod(elem));
			}
			else {
				int second = stack.pop();
				int first = stack.pop();
				char operand = *(elem.data());
				switch (operand) {
				case '+':
					stack.push(first + second);
					break;
				case '-':
					stack.push(first - second);
					break;
				case '*':
					stack.push(first * second);
					break;
				case '/':
					if (second == 0) {
						return "INF";
					}
					stack.push(first / second);
					break;
				}
			}
		}
		res = res + to_string(stack.top());
	}
	return res;
}

int Translator::priority(string term) {
	int ret = 0;
	if (term == "+" || term == "-") {
		ret = 0;
	}
	if (term == "*" || term == "/") {
		ret = 1;
	}
	return ret;
}

vector<string> Translator::get_terms(string expr) {
	int state = 0;
	vector<string> terms;
	string term;
	for (char c : expr) {
		switch (state) {
		case 0:
			if (c == '(') {
				terms.push_back(string() + c);
			}
			else if (isdigit(c)) {		//is a number
				term.push_back(c);
				state = 6;
			}
			else if (isalpha(c) || c == '_') {		//is a variable
				term.push_back(c);
				state = 5;
			}
			break;
		case 1:
			if (c == ')') {
				if (!term.empty())
					terms.push_back(term);
				term.clear();
				terms.push_back(string() + c);
				state = 1;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				if (!term.empty())
					terms.push_back(term);
				term.clear();
				terms.push_back(string() + c);
				state = 0;
			}
			break;
		case 4:
			if (isdigit(c)) {
				term.push_back(c);
				state = 4;
			}
			else if (c == ')') {
				if (!term.empty())
					terms.push_back(term);
				term.clear();
				terms.push_back(string() + c);
				state = 1;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				if (!term.empty())
					terms.push_back(term);
				term.clear();
				terms.push_back(string() + c);
				state = 0;
			}
			break;
		case 5:
			if (isalpha(c) || c == '_' || isdigit(c)) {
				term.push_back(c);
				state = 5;
			}
			else if (c == ')') {
				if (check_variable_term(term)) {
					if (!term.empty())
						terms.push_back(term);
					term.clear();
					terms.push_back(string() + c);
					state = 1;
				}
				else {
					terms.clear();
					terms.push_back("error");
					terms.push_back(term);
					return terms;
				}
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				if (check_variable_term(term)) {
					if (!term.empty())
						terms.push_back(term);
					term.clear();
					terms.push_back(string() + c);
					state = 0;
				}
				else {
					terms.clear();
					terms.push_back("error");
					terms.push_back(term);
					return terms;
				}
			}
			break;
		case 6:
			if (c == ')') {
				if (!term.empty())
					terms.push_back(term);
				term.clear();
				terms.push_back(string() + c);
				state = 1;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				if (!term.empty())
					terms.push_back(term);
				term.clear();
				terms.push_back(string() + c);
				state = 0;
			}
			else if (isdigit(c)) {
				term.push_back(c);
				state = 6;
			}
			else if (c == '.') {
				term.push_back(c);
				state = 4;
			}
			break;
		}
	}
	if (!term.empty()) {
		if (isalpha(term[0]) || term[0] == '_') {
			if (check_variable_term(term))
				terms.push_back(term);
			else {
				terms.clear();
				terms.push_back("error");
				terms.push_back(term);
				return terms;
			}
		}
		else
			terms.push_back(term);
	}
	return terms;
}

bool Translator::check_variable_term(string term) {
	for (auto elem : double_variables) {
		if (elem.first == term) {
			return true;
		}
	}
	for (auto elem : int_variables) {
		if (elem.first == term) {
			return true;
		}
	}
	return false;
}

bool Translator::lvalue_analysis(string lvalue) {
	if (!(isalpha(lvalue[0]) || lvalue[0] == '_')) {
		return false;

	}
	for (char c : lvalue) {
		if (!(isalpha(c) || isdigit(c) || c == '_')) {
			return false;
		}
	}
	return true;
}


bool Translator::expression_analysis(string expr) {
	int state = 0;
	int bracket_counter = 0;
	for (char c : expr) {
		switch (state) {
		case INIT:
			//if (c == '\0') {
			//	state = BRACKET_CHECK;
			//}
			if (c == '(') {
				bracket_counter++;
			}
			else if (isdigit(c)) {		//is a number
				state = NUM_INT;
			}
			else if (isalpha(c) || c == '_') {		//is a variable
				state = VAR;
			}
			else {
				state = ERROR;
			}
			break;
		case OPERAND:
			//if (c == '\0') {
			//	state = BRACKET_CHECK;
			//}
			if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = ERROR;
				}
				else {
					state = OPERAND;
				}
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = INIT;
			}
			else {
				state = ERROR;
			}
			break;
		case NUM_DOUBLE:
			if (isdigit(c)) {
				state = NUM_DOUBLE;
			}
			//else if (c == '\0') {
			//	state = BRACKET_CHECK;
			//}
			else if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = ERROR;
				}
				else {
					state = OPERAND;
				}
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = INIT;
			}
			else {
				state = ERROR;
			}
			break;
		case VAR:
			if (isalpha(c) || c == '_' || isdigit(c)) {
				state = VAR;
			}
			//else if (c == '\0') {
			//	state = BRACKET_CHECK;
			//}
			else if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = ERROR;
				}
				else {
					state = OPERAND;
				}
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = INIT;
			}
			else {
				state = ERROR;
			}
			break;
		case NUM_INT:
			//if (c == '\0') {
			//	state = BRACKET_CHECK;
			//}
			if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = ERROR;
				}
				else {
					state = OPERAND;
				}
			}
			else if (isdigit(c)) {
				state = NUM_INT;
			}
			else if (c == '.') {
				state = NUM_DOUBLE;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = INIT;
			}
			else {
				state = ERROR;
			}
			break;
		case ERROR:
			return false;
		}
		
	}
	if (bracket_counter) {
		state = ERROR;
	}
	if (state == ERROR) {
		return false;
	}
	return true;
}