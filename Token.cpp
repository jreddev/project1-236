#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    setType(type);
    setDescription(description);
    setLine(line);

}
// MY ADDED CODE//
void Token::setType(TokenType type){
    myType = type;
}
void Token::setDescription(std::string description){
    value = description;
}
void Token::setLine(int line){
    lineNumber = line;
}
TokenType Token::returnType() {
    TokenType fixmeToken = TokenType::ID;// FIXME read below, haha.
    return fixmeToken; //FIXME this is just for now, needs to actually return something real in the future, haha.
}
std::string Token::returnDescription(){
    std::string fixmeString; //FIXME !!!!!!
    return fixmeString; //FIXME !!!!!!
}
int Token::returnLine(){
    int fixmeInt = 0; // !!!!!!
    return fixmeInt; //FIXME !!!!!!
}
void Token::toString(){
    std::string tokenString = enumToString(myType);
    std::cout << "(";
    std::cout << tokenString;
    std::cout << ",\"";
    std::cout << value;
    std::cout << "\",";
    std::cout << lineNumber;
    std::cout << ")\n";//FIXME: maybe need to remove \n
}
//END ADDED CODE//
