#include "analyzer.h"

void lex_analysis(const string& str, vector<token_t>& token_list)
{
    double value = 0;
    token_t token;
    int i = 0;

    while (i < str.size())
    {
        token = {UNKNOWN, 0.0};
        if (str[i] >= '0' && str[i] <= '9')
        {
            size_t pos = 0;
            value = stod(str.substr(i), &pos);
            token.info = VALUE;
            token.value = value;
            i += pos;
            token_list.push_back(token);
            continue;
        }
        switch (str[i])
        {
            case '+':
                token.info = ADD;
                token_list.push_back(token);
                break;
            case '-':
                token.info = SUBTRACT;
                token_list.push_back(token);
                break;
            case '/':
                token.info = DIVISION;
                token_list.push_back(token);
                break;
            case '*':
                token.info = MULTIPLY;
                token_list.push_back(token);
                break;
            case '(':
                token.info = OPENING_BR;
                token_list.push_back(token);
                break;
            case ')':
                token.info = CLOSING_BR;
                token_list.push_back(token);
                break;
            case 'x':
            case 'y':
            case 'z':
                token.info = VARIABLE;
                token.value = str[i];
                token_list.push_back(token);
        }
        i++;
    }
}

//=============================================================
