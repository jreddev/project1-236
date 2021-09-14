#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables

}
// MY ADDED CODE//
void Token::setType(TokenType type){

}
void Token::setDescription(std::string description){

}
void Token::setLine(int line){

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
    int fixmeInt = 0; //FIXME !!!!!!
    return fixmeInt; //FIXME !!!!!!
}
void Token::toString(){

}
//END ADDED CODE//
