class Stack {
public:
    Stack(int length);
    void Push(token_t value);
    token_t Pop();
    token_t Pop_without_del();
    void Print();
    vector<token_t> GetStack();

    vector<token_t> data;

    ~Stack() {};

private:

    void Realloc(int new_capacity);
};
