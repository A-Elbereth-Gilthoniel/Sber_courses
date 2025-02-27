#include "analyzer.h"

// E -> E + T
// T -> T * F | F
// F -> xyz | value | (E)

int main()
{
    string expression;
    getline(cin, expression);

    vector<token_t> token_list;
    token_list.reserve(LIST_SIZE);

    lex_analysis(expression, token_list);

    Table* table = new Table(TABLE_SIZE);

    syntax_analysis(token_list, table);

    table->Print();

    return 0;

}

