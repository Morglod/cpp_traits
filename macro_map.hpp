#pragma once

/*
 * Created by William Swanson in 2012.
 *
 * I, William Swanson, dedicate this work to the public domain.
 * I waive all rights to the work worldwide under copyright law,
 * including all related and neighboring rights,
 * to the extent allowed by law.
 *
 * You can copy, modify, distribute and perform the work,
 * even for commercial purposes, all without asking permission.
 */

/*

Example usage:

// Basic `MAP` usage: 
#define STRING(x) char const *x##_string = #x;
MAP(STRING, foo, bar, baz)

// Basic `MAP_LIST` usage:
#define PARAM(x) int x
void function(MAP_LIST(PARAM, foo, bar, baz));

// Test `MAP` with parentheses in the arguments:
#define CALL(x) putchar x;
MAP(CALL, ('a'), ('b'), ('c'))

// Test `MAP_LIST` with parentheses in the arguments:
#define CALL_LIST(x) putchar x
MAP_LIST(CALL_LIST, ('a'), ('b'), ('c'));

*/

#define MACRO_EVAL0(...) __VA_ARGS__
#define MACRO_EVAL1(...) MACRO_EVAL0(MACRO_EVAL0(MACRO_EVAL0(__VA_ARGS__)))
#define MACRO_EVAL2(...) MACRO_EVAL1(MACRO_EVAL1(MACRO_EVAL1(__VA_ARGS__)))
#define MACRO_EVAL3(...) MACRO_EVAL2(MACRO_EVAL2(MACRO_EVAL2(__VA_ARGS__)))
#define MACRO_EVAL4(...) MACRO_EVAL3(MACRO_EVAL3(MACRO_EVAL3(__VA_ARGS__)))
#define MACRO_EVAL(...)  MACRO_EVAL4(MACRO_EVAL4(MACRO_EVAL4(__VA_ARGS__)))

#define MACRO_MAP_END(...)
#define MACRO_MAP_OUT
#define MACRO_MAP_COMMA ,

#define MACRO_MAP_GET_END2() 0, MACRO_MAP_END
#define MACRO_MAP_GET_END1(...) MACRO_MAP_GET_END2
#define MACRO_MAP_GET_END(...) MACRO_MAP_GET_END1
#define MACRO_MAP_NEXT0(test, next, ...) next MACRO_MAP_OUT
#define MACRO_MAP_NEXT1(test, next) MACRO_MAP_NEXT0(test, next, 0)
#define MACRO_MAP_NEXT(test, next)  MACRO_MAP_NEXT1(MACRO_MAP_GET_END test, next)

#define MACRO_MAP0(f, x, peek, ...) f(x) MACRO_MAP_NEXT(peek, MACRO_MAP1)(f, peek, __VA_ARGS__)
#define MACRO_MAP1(f, x, peek, ...) f(x) MACRO_MAP_NEXT(peek, MACRO_MAP0)(f, peek, __VA_ARGS__)

#define MACRO_MAP_LIST_NEXT1(test, next) MACRO_MAP_NEXT0(test, MACRO_MAP_COMMA next, 0)
#define MACRO_MAP_LIST_NEXT(test, next)  MACRO_MAP_LIST_NEXT1(MACRO_MAP_GET_END test, next)

#define MACRO_MAP_LIST0(f, x, peek, ...) f(x) MACRO_MAP_LIST_NEXT(peek, MACRO_MAP_LIST1)(f, peek, __VA_ARGS__)
#define MACRO_MAP_LIST1(f, x, peek, ...) f(x) MACRO_MAP_LIST_NEXT(peek, MACRO_MAP_LIST0)(f, peek, __VA_ARGS__)

/**
 * Applies the function macro `f` to each of the remaining parameters.
 */
#define MACRO_MAP(f, ...) MACRO_EVAL(MACRO_MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters and
 * inserts commas between the results.
 */
#define MACRO_MAP_LIST(f, ...) MACRO_EVAL(MACRO_MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
