#ifndef BLOCKCOMMENTAUTOMATON_H
#define BLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class BlockCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void SFail(const std::string& input);

public:
    BlockCommentAutomaton() : Automaton(TokenType::BLOCKCOMMENT) {}  // Call the base constructor

    void S0(const std::string& input);

};

#endif // BLOCKCOMMENTAUTOMATON_H

