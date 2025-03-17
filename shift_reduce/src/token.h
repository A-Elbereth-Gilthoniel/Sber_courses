enum tokens
{
    OPENING_BR = 1,
    CLOSING_BR = 2,
    MULTIPLY = 3,
    DIVISION = 4,
    ADD = 5,
    SUBTRACT = 6,
    VALUE = 7,
    VARIABLE = 8,
    E_TYPE = 9,
    F_TYPE = 10,
    T_TYPE = 11,
    UNKNOWN = 12,
    EMPTY = 13
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
