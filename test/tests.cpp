#include <gtest.h>
#include "Translator.h"

//	Object-oriented tests
TEST(translator_basic, can_create_translator) {
	ASSERT_NO_THROW(Translator t);
}

TEST(translator_basic, can_perform_expression) {
	Translator t;
	ASSERT_NO_THROW(t.test_execute("1"));
}

//	Assignment operation tests
TEST(translator_assignment, can_create_integer_variable) {
	Translator t;
	t.test_execute("a=3");
	ASSERT_EQ(t.test_execute("a"), 3);
}

TEST(translator_assignment, can_create_multi_digit_integer_variable) {
	Translator t;
	t.test_execute("a=35");
	ASSERT_EQ(t.test_execute("a"), 35);
}

TEST(translator_assignment, deletes_spaces_and_tabs_correctly) {
	Translator t;
	t.test_execute("a\t= 3 ");
	ASSERT_EQ(t.test_execute("a"), 3);
}

TEST(translator_assignment, can_create_variable_with_multiple_letter_name) {
	Translator t;
	t.test_execute("abc= 3 ");
	ASSERT_EQ(t.test_execute("abc"), 3);
}

TEST(translator_assignment, can_create_float_variable) {
	Translator t;
	t.test_execute("a=3.0");
	ASSERT_EQ(t.test_execute("a"), 3.0);
}

TEST(translator_assignment, can_create_multi_digit_float_variable) {
	Translator t;
	t.test_execute("a=35.0");
	ASSERT_EQ(t.test_execute("a"), 35.0);
}

TEST(translator_assignment, can_create_float_variable_without_specified_fraction) {
	Translator t;
	t.test_execute("a=35.");
	ASSERT_EQ(t.test_execute("a"), 35.);
}

TEST(translator_assignment, can_overwrite_variable_integer_value) {
	Translator t;
	t.test_execute("a=3");
	t.test_execute("a=4");
	ASSERT_EQ(t.test_execute("a"), 4);
}

TEST(translator_assignment, can_overwrite_variable_float_value) {
	Translator t;
	t.test_execute("a=3.");
	t.test_execute("a=4.");
	ASSERT_EQ(t.test_execute("a"), 4);
}

TEST(translator_assignment, can_overwrite_integer_variable_with_float_value) {
	Translator t;
	t.test_execute("a=3");
	t.test_execute("a=4.5");
	ASSERT_EQ(t.test_execute("a"), 4.5);
}

TEST(translator_assignment, can_assign_variable) {
	Translator t;
	t.test_execute("a=1");
	t.test_execute("b=a");
	ASSERT_EQ(t.test_execute("a"), t.test_execute("b"));
}

TEST(translator_assignment, can_assign_integer_expression) {
	Translator t;
	t.test_execute("a=1+1");
	ASSERT_EQ(t.test_execute("a"), 2);
}

TEST(translator_assignment, can_assign_float_expression) {
	Translator t;
	t.test_execute("a=1.+1.");
	ASSERT_EQ(t.test_execute("a"), 2.);
}

TEST(translator_assignment, can_assign_expression_with_variable) {
	Translator t;
	t.test_execute("a=5");
	t.test_execute("b=1+a");
	ASSERT_EQ(t.test_execute("b"), 6);
}

TEST(translator_assignment, can_assign_expression_with_same_variable) {
	Translator t;
	t.test_execute("a=2");
	t.test_execute("a=1+a");
	ASSERT_EQ(t.test_execute("a"), 3);
}


TEST(translator_assignment, can_assign_expression_with_brackets) {
	Translator t;
	t.test_execute("a=2*(2+2)");
	ASSERT_EQ(t.test_execute("a"), 8);
}

TEST(translator_assignment, can_assign_expression_with_multiple_variables) {
	Translator t;
	t.test_execute("a=1");
	t.test_execute("b=2");
	t.test_execute("c=a+b");
	ASSERT_EQ(t.test_execute("c"), 3);
}

TEST(translator_assignment, can_assign_expression_with_every_operation) {
	Translator t;
	t.test_execute("a=2^2+2*2-2/2");
	ASSERT_EQ(t.test_execute("a"), 7);
}

TEST(translator_assignment, can_assign_expression_with_multiple_variables_and_brackets) {
	Translator t;
	t.test_execute("a=1");
	t.test_execute("b=2");
	t.test_execute("c=(a+b)^2");
	ASSERT_EQ(t.test_execute("c"), 9);
}

TEST(translator_assignment, can_assign_variable_with_alike_name) {
	Translator t;
	t.test_execute("ab=2");
	t.test_execute("a=ab");
	ASSERT_EQ(t.test_execute("a"), 2);
}


//	Calculating expression tests
TEST(translator_calculate, can_calculate_trivial_integer_expression) {
	Translator t;
	auto res = t.test_execute("1+1");
	ASSERT_EQ(res, 2);
}

TEST(translator_calculate, can_calculate_trivial_double_expression) {
	Translator t;
	auto res = t.test_execute("1.3 - 0.4");
	ASSERT_EQ(res, 0.9);
}

TEST(translator_calculate, can_calculate_trivial_variable_expression) {
	Translator t;
	t.test_execute("a=2");
	auto res = t.test_execute("a * 0.5");
	ASSERT_EQ(res, 1);
}

TEST(translator_calculate, can_calculate_expression_with_lower_priority_operation_in_brackets) {
	Translator t;
	auto res = t.test_execute("2^(2+1)");
	ASSERT_EQ(res, 8);
}

TEST(translator_calculate, can_calculate_expression_with_multiple_brackets) {
	Translator t;
	auto res = t.test_execute("2*(2/(1+1))");
	ASSERT_EQ(res, 2);
}

TEST(translator_calculate, can_calculate_expression_with_multiple_variables) {
	Translator t;
	t.test_execute("a=2");
	t.test_execute("b=5");
	auto res = t.test_execute("(a+1)*(b-2)");
	ASSERT_EQ(res, 9);
}

TEST(translator_calculate, can_calculate_expression_with_alike_variable_names) {
	Translator t;
	t.test_execute("a=2");
	t.test_execute("ab=3");
	auto res = t.test_execute("a+ab");
	ASSERT_EQ(res, 5);
}

TEST(translator_calculate, throws_when_dividing_by_zero) {
	Translator t;
	ASSERT_ANY_THROW(t.test_execute("0/0"));
}

TEST(translator_calculate, can_calculate_nested_expressions_in_brackets) {
	Translator t;
	auto res = t.test_execute("2^(2*(2+2))");
	ASSERT_EQ(res, 256);
}


//	Expression analysis tests
TEST(translator_analysis, assignment_throws_when_assigning_uninitialized_variable) {
	Translator t;
	ASSERT_ANY_THROW(t.test_execute("a=1+b"));
}

TEST(translator_analysis, assignment_throws_when_assigning_invalid_float_number) {
	Translator t;
	ASSERT_ANY_THROW(t.test_execute("a=3.3.3"));
}

TEST(translator_analysis, assignment_throws_when_too_many_opening_brackets) {
	Translator t;
	ASSERT_ANY_THROW(t.test_execute("a = ((1+1)"));
}

TEST(translator_analysis, assignment_throws_when_too_many_closing_brackets) {
	Translator t;
	ASSERT_ANY_THROW(t.test_execute("a = (1+1))"));
}

TEST(translator_analysis, assignment_throws_when_expression_is_empty) {
	Translator t;
	ASSERT_ANY_THROW(t.test_execute("a = "));
}

TEST(translator_analysis, assignment_throws_when_invalid_variable_name) {
	Translator t;
	EXPECT_ANY_THROW(t.test_execute("0a=1"));
	EXPECT_ANY_THROW(t.test_execute("%a=1"));
}

TEST(translator_analysis, throws_when_expression_in_brackets_is_empty) {
	Translator t;
	ASSERT_ANY_THROW(t.test_execute("1+()"));
}

TEST(translator_analysis, throws_when_expression_contains_unsupported_symbol) {
	Translator t;
	ASSERT_ANY_THROW(t.test_execute("1+%"));
}

TEST(translator_analysis, throws_when_expression_ends_with_operation_sign) {
	Translator t;
	EXPECT_ANY_THROW(t.test_execute("1+"));
	EXPECT_ANY_THROW(t.test_execute("1-"));
	EXPECT_ANY_THROW(t.test_execute("1/"));
}

TEST(translator_analysis, throws_when_closing_bracket_comes_after_operation_sign) {
	Translator t;
	ASSERT_ANY_THROW(t.test_execute("1+(1^)"));
}

TEST(translator_analysis, throws_when_meets_two_consecutive_operation_signs) {
	Translator t;
	ASSERT_ANY_THROW(t.test_execute("1+*"));
}
