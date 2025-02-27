#include "analyzer.h"

Stack::Stack(int length)
{
    data.reserve(length);
}

//--------------------------------------------------------------------------

void Stack::Push(token_t value)
{
    if (data.size() == data.capacity())
    {
        Realloc(data.capacity() * 2);
    }
    if (value.info != EMPTY)
        data.push_back(value);
}

//----------------------------------------------------------------------------

token_t Stack::Pop()
{
    token_t res = {EMPTY, 0.0};
    if (data.size() > 0)
    {
        res = data.back();
        data.pop_back();

        if (data.size() < data.capacity() / 3)
        {
            Realloc((data.capacity() / 3)+1);
        }
    }

    return res;
}

//----------------------------------------------------------------------------

void Stack::Print()
{
    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}

//----------------------------------------------------------------------------

void Stack::Realloc (int new_capacity)
{
    data.reserve(new_capacity);
}

//----------------------------------------------------------------------------

vector<token_t> Stack::GetStack()
{
    return data;
}

token_t Stack::Pop_without_del()
{
    token_t res = {EMPTY, 0.0};
    if (data.size() > 0)
    {
        res = data.back();

        if (data.size() < data.capacity() / 3)
        {
            Realloc((data.capacity() / 3)+1);
        }
    }

    return res;
}
