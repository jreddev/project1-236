#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include "fstream"
#include "iostream"

enum class TokenType {
    COLON,
    COLON_DASH,
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
       /* TokenType colon = TokenType::COLON;
        TokenType colon_dash = TokenType::COLON_DASH;
        TokenType comma = TokenType::COMMA;
        TokenType period = TokenType::PERIOD;
        TokenType q_mark = TokenType::Q_MARK;
        TokenType left_paren = TokenType::LEFT_PAREN;
        TokenType right_paren = TokenType::RIGHT_PAREN;
        TokenType multiply = TokenType::MULTIPLY;
        TokenType add = TokenType::ADD;
        TokenType schemes = TokenType::SCHEMES;
        TokenType facts = TokenType::FACTS;
        TokenType rules = TokenType::RULES;
        TokenType queries = TokenType::QUERIES;
        TokenType id = TokenType::ID;
        TokenType string = TokenType::STRING;
        TokenType block_comment = TokenType::BLOCKCOMMENT;
        TokenType linecomment = TokenType::LINECOMMENT;
        TokenType end = TokenType::END;//FIXME MAYBE
        TokenType undefined = TokenType::UNDEFINED;
        TokenType tokenType = TokenType::UNDEFINED;*/


class Token
{
private:
    // TODO: add member variables for information needed by Token

public:
    std::string value;
    int lineNumber;
    TokenType myType;
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
    std::string enumToString(TokenType tokenType) {
        switch(tokenType){
            case TokenType::COLON: return "COLON"; break;
            case TokenType::COLON_DASH: return "COLON_DASH"; break;
            case TokenType::COMMA : return "COMMA"; break;
            case TokenType::PERIOD: return "PERIOD"; break;
            case TokenType::Q_MARK: return "Q_MARK"; break;
            case TokenType::LEFT_PAREN: return "LEFT_PAREN"; break;
            case TokenType::RIGHT_PAREN: return "RIGHT_PAREN"; break;
            case TokenType::MULTIPLY: return "MULTIPLY"; break;
            case TokenType::ADD: return "ADD"; break;
            case TokenType::SCHEMES: return "SCHEMES"; break;
            case TokenType::FACTS: return "FACTS"; break;
            case TokenType::RULES: return "RULES"; break;
            case TokenType::QUERIES: return "QUERIES"; break;
            case TokenType::ID: return "ID"; break;
            case TokenType::STRING: return "STRING"; break;
            case TokenType::BLOCKCOMMENT: return "COMMENT"; break;
            case TokenType::LINECOMMENT: return "COMMENT"; break;
            case TokenType::END: return "EOF"; break;//FIXME MAYBE
            case TokenType::UNDEFINED: return "UNDEFINED"; break;
        }
        return "ERROR";
    }
    //end added code//
};

#endif // TOKEN_H

