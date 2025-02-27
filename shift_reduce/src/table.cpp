#include "analyzer.h"

Table::Table(int size)
{
    stack_cond.reserve(size);
    input_cond.reserve(size);
    action_cond.reserve(size);
}

//==================================

void Table::PushCondition(const vector<token_t>& token_stack, const vector<token_t>& input, int offset, string action)
{
    if (action != string(""))
    {
        string stack_str = "";
        for (int i = 0; i < token_stack.size(); i++)
            stack_str += token_to_str(token_stack[i]);
        if (stack_str.size() > max_stack_size)
            max_stack_size = stack_str.size();

        string input_str = "";
        for (int i = offset; i < input.size(); i++)
            input_str += token_to_str(input[i]);
        if (input_str.size() > max_input_size)
            max_input_size = input_str.size();

        if (action.size() > max_action_size)
            max_action_size = action.size();

        stack_cond.push_back(stack_str);
        input_cond.push_back(input_str);
        action_cond.push_back(action);
        table_is_changed = true;


        if (action == string("Error"))
        {
            Print();
            exit(0);
        }
    }
}

//=================================================

void Table::Print()
{
    int padding, left_padding, right_padding;
    string stk = "Stack", inp = "Input", act = "Action";
    max_stack_size = max(max_stack_size, 5);
    max_input_size = max(max_input_size, 5);
    max_action_size = max(max_action_size, 6);
    stk = align(stk, max_stack_size);
    inp = align(inp, max_input_size);
    act = align(act, max_action_size);
    cout << "|" << stk << "|" << inp << "|" << act << "|" << endl;

    for (int i = 0; i < stack_cond.size(); i++)
    {
        stk = align(stack_cond[i], max_stack_size);
        inp = align(input_cond[i], max_input_size);
        act = align(action_cond[i], max_action_size);
        cout << "|" << stk << "|" << inp << "|" << act << "|" << endl;
    }
}

//=======================================================

string Table::align(string str, int final_size)
{
    int padding = final_size - str.size();
    int left_padding = padding / 2;
    int right_padding = padding - left_padding;
    str.insert(0, left_padding, ' ');
    str.append(right_padding, ' ');
    return str;
}

//========================================================
