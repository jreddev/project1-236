cmake_minimum_required(VERSION 3.17)
project(project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project1
        AddAutomaton.cpp
        AddAutomaton.h
        Automaton.h
        BlockCommentAutomaton.cpp
        BlockCommentAutomaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        CommaAutomaton.cpp
        CommaAutomaton.h
        EOFAutomaton.cpp
        EOFAutomaton.h
        FactsAutomaton.cpp
        FactsAutomaton.h
        IdAutomaton.cpp
        IdAutomaton.h
        Left_ParenAutomaton.cpp
        Left_ParenAutomaton.h
        Lexer.cpp
        Lexer.h
        LineCommentAutomaton.cpp
        LineCommentAutomaton.h
        main.cpp
        MultiplyAutomaton.cpp
        MultiplyAutomaton.h
        PeriodAutomaton.cpp
        PeriodAutomaton.h
        Q_MarkAutomaton.cpp
        Q_MarkAutomaton.h
        QueriesAutomaton.cpp
        QueriesAutomaton.h
        Right_ParenAutomaton.cpp
        Right_ParenAutomaton.h
        RulesAutomaton.cpp
        RulesAutomaton.h
        SchemesAutomaton.cpp
        SchemesAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        Token.cpp
        Token.h
        UndefinedAutomaton.cpp
        UndefinedAutomaton.h)
