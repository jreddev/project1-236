#ifndef COMMAAUTOMATON_H
#define COMMAAUTOMATON_H

#include "Automaton.h"

class CommaAutomaton : public Automaton
{
public:
    CommaAutomaton() : Automaton(TokenType::Comma) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // COMMAAUTOMATON_H

