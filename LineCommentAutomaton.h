#ifndef LINECOMMENTAUTOMATON_H
#define LINECOMMENTAUTOMATON_H

#include "Automaton.h"

class LineCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void SFail(const std::string& input);

public:
    LineCommentAutomaton() : Automaton(TokenType::LINECOMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // LINECOMMENTAUTOMATON_H

