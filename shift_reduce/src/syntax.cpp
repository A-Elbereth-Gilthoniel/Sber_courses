#include "analyzer.h"

void syntax_analysis(vector<token_t>& token_list, Table* table)
{
    Stack* token_stack = new Stack(STACK_SIZE);
    token_t last_elem, cur;
    vector<token_t> entire_stack;
    string act;
    int i = 0;
    while (i <= token_list.size() + 1)
    {
        cur = {UNKNOWN, 0.0};
        entire_stack = token_stack->data;
        last_elem = token_stack->Pop();
        switch (last_elem.info)
        {
            case VARIABLE:
            case VALUE:
                cur.info = F_TYPE;
                token_stack->Push(cur);
                table->PushCondition(entire_stack, token_list, i, string("Reduce F -> id"));
                break;
            case MULTIPLY:
            case DIVISION:
            case OPENING_BR:
                token_stack->Push(last_elem);
                break;
            case ADD:
            case SUBTRACT:
                table->PushCondition(entire_stack, token_list, i, process_plus_minus(token_stack));
                if (token_stack->Pop_without_del().info == E_TYPE)
                {
                    token_stack->Push(last_elem);
                    entire_stack = token_stack->data;
                    token_stack->Pop();
                    token_stack->Pop();
                    table->PushCondition(entire_stack, token_list, i, process_e(token_stack));
                }
                token_stack->Push(last_elem);
                break;
            case CLOSING_BR:
                act = process_closing_br(token_stack);
                if (act == "")
                {
                    token_t cl_br = {CLOSING_BR, 0.0};
                    table->PushCondition(entire_stack, token_list, i, process_e(token_stack));
                    token_stack->Push(cl_br);
                }
                else
                    table->PushCondition(entire_stack, token_list, i, act);
                break;
            case F_TYPE:
                table->PushCondition(entire_stack, token_list, i, process_f(token_stack));
                break;
            case T_TYPE:
                table->PushCondition(entire_stack, token_list, i, process_t(token_stack));
                break;
            case E_TYPE:
                table->PushCondition(entire_stack, token_list, i, process_e(token_stack));
                break;
            case EMPTY:
                break;
        }
        if (!table->table_is_changed)
        {
            if (i < token_list.size())
            {
                token_stack->Push(token_list[i]);
                table->PushCondition(entire_stack, token_list, i, string("Shift"));
            }
            else
            {
                table->PushCondition(entire_stack, token_list, i, process_plus_minus(token_stack));
            }
            i++;
        }
        table->table_is_changed = false;
    }
    table->PushCondition(token_stack->data, token_list, i, string("accept"));
}

//=========================================================

string process_f(Stack* token_stack)
{
    token_t stack_elem = token_stack->Pop();
    token_t a = {T_TYPE, 0.0};
    ostringstream oss;
    switch (stack_elem.info)
    {
        case MULTIPLY:
        case DIVISION:
            if (token_stack->Pop().info == T_TYPE)
            {
                token_stack->Push(a);
                oss << "Reduce T -> T " << stack_elem << " F";
                return oss.str();
            }
            return string("Error");
        case ADD:
        case SUBTRACT:
        case OPENING_BR:
        case EMPTY:
            token_stack->Push(stack_elem);
            token_stack->Push(a);
            return string("Reduce T -> F");

        default:
            return string("Error");
    }
}

//================================================

string process_t(Stack* token_stack)
{
    token_t stack_elem = token_stack->Pop();
    token_t a = {T_TYPE, 0.0};
    token_t b;
    ostringstream oss;
    switch (stack_elem.info)
    {
        case MULTIPLY:
        case DIVISION:
            b = token_stack->Pop();
            if (b.info == T_TYPE || b.info == F_TYPE)
            {
                token_stack->Push(a);
                oss << "Reduce T -> " << b << " " << stack_elem << " T";
                return oss.str();
            }
            return string("Error");
        case ADD:
        case SUBTRACT:
        case OPENING_BR:
        case EMPTY:
            token_stack->Push(stack_elem);
            token_stack->Push(a);
            return string("");

        default:
            return string("Error");
    }
}

//==============================================

string process_plus_minus(Stack* token_stack)
{
    token_t a1 = token_stack->Pop();
    token_t e_tok = {E_TYPE, 0.0};
    if (a1.info == T_TYPE)
    {
        token_stack->Push(e_tok);
        return string("Reduce E -> T");
    }
    else
    {
        token_stack->Push(a1);
        return string("");
    }
}

//=====================================================

string process_e(Stack* token_stack)
{
    token_t stack_elem = token_stack->Pop();
    token_t a = {E_TYPE, 0.0};
    token_t b;
    ostringstream oss;
    switch (stack_elem.info)
    {
        case ADD:
        case SUBTRACT:
            b = token_stack->Pop();
            if (b.info == E_TYPE || b.info == T_TYPE)
                token_stack->Push(b);
            oss << "Reduce E -> " << b << " " << stack_elem << " E";
            return oss.str();
        case OPENING_BR:
        case EMPTY:
            token_stack->Push(stack_elem);
            token_stack->Push(a);
            return string("");

        default:
            return string("Error");
    }
}

//=================================================

string process_closing_br(Stack* token_stack)
{
    token_t f_t = {F_TYPE, 0.0};
    token_t a = token_stack->Pop();
    if (a.info == E_TYPE && token_stack->Pop_without_del().info == OPENING_BR)
    {
        token_stack->Pop();
        token_stack->Push(f_t);
        return string("Reduce F -> (E)");
    }
    return string("");
}
