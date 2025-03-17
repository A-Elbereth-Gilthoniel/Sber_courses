class Table {
public:
    vector<string> stack_cond;
    vector<string> input_cond;
    vector<string> action_cond;
    int max_stack_size = 0;
    int max_input_size = 0;
    int max_action_size = 0;
    bool table_is_changed = false;

    Table(int size);
    void PushCondition(const vector<token_t>& token_stack, const vector<token_t>& input, int offset, string action);
    string LastCondition();
    void Print();

    ~Table() {};


private:
    string align(string str, int final_size);
};
