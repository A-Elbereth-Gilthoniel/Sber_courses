#ifndef ANALYZER_H
#define ANALYZER_H
#include "libr.h"
#include "token.h"
#include "stack.h"
#include "table.h"

#define LIST_SIZE 30
#define STACK_SIZE 30
#define TABLE_SIZE 30

// lexer.l
extern int yylex();
extern token_t yylval;
// lexical.cpp
void lex_analysis(const string& str, vector<token_t>& token_list);
// syntax.cpp
void syntax_analysis(vector<token_t>& token_list, Table* table);
string process_f(Stack* token_stack);
string process_t(Stack* token_stack, vector<token_t>& elements, int offset);
string process_e(Stack* token_stack);
string process_if_no_changes(Stack* token_stack);
string process_plus_minus(Stack* token_stack);
string process_closing_br(Stack* token_stack);
// token.cpp
#endif
