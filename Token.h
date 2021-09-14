#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    // TODO: add the other types of tokens
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    BLOCKCOMMENT,
    LINECOMMENT,
    END,//FIXME MAYBE
    UNDEFINED
};

class Token
{
private:
    // TODO: add member variables for information needed by Token

public:
    Token(TokenType type, std::string description, int line);

    // TODO: add other needed methods

    //my added code//
    void setType(TokenType type);
    void setDescription(std::string description);
    void setLine(int line);
    TokenType returnType();
    std::string returnDescription();
    int returnLine();
    void toString();
    //end added code//
};

#endif // TOKEN_H

