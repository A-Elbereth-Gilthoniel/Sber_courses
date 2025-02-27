#include "analyzer.h"

ostream& operator<<(ostream& os, const token_t& p)
{
    switch (p.info)
    {
        case OPENING_BR:
            os << "(";
            break;
        case CLOSING_BR:
            os << ")";
            break;
        case MULTIPLY:
            os << "*";
            break;
        case DIVISION:
            os << "/";
            break;
        case ADD:
            os << "+";
            break;
        case SUBTRACT:
            os << "-";
            break;
        case VALUE:
            os << get<double>(p.value);
            break;
        case VARIABLE:
            os << "id";
            break;
        case E_TYPE:
            os << "E";
            break;
        case F_TYPE:
            os << "F";
            break;
        case T_TYPE:
            os << "T";
            break;
        case UNKNOWN:
        case EMPTY:
            cerr << "Unknown token";
    }
    return os;
}

//----------------------------------------

string token_to_str(token_t token)
{
    ostringstream oss;

    oss << token;
    string result = oss.str();
    return result;
}
