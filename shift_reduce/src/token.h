enum tokens
{
    OPENING_BR,
    CLOSING_BR,
    MULTIPLY,
    DIVISION,
    ADD,
    SUBTRACT,
    VALUE,
    VARIABLE,
    E_TYPE,
    F_TYPE,
    T_TYPE,
    UNKNOWN,
    EMPTY
};


typedef struct token_t{
    enum tokens info;
    std::variant<double, char> value = 0.0;

    bool operator==(const token_t& other) const {
        return info == other.info;
    }

    friend ostream& operator<<(ostream& os, const token_t& p);

 } token_t;


string token_to_str(token_t token);
