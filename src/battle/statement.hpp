/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#pragma once
#ifndef STATEMENT_H
#define STATEMENT_H

namespace Eternity {
/* a unit instruction statement */
    class Statement {
    protected:
    public:
        virtual bool execute() = 0;
    };

/* a unit ACTION (...) statement */
    class Statement_Action:public Statement {
    private:
    public:
        bool execute();
    };

/* a unit ASSIGN (VAR) = (EXPRESSION) statement */
    class Statement_Assign:public Statement {
    private:
        vector<>::iterator reference;
        Expression* expression;
    public:
        bool execute();
    };

/* a unit IF (PREDICATE) {BLOCK1} else {BLOCK2} statement */
    class Statement_Ifelse:public Statement {
    private:
        bool returning;
        Predicate* condition;
        Block* t_branch;
        Block* f_branch;
    };

/* a unit WHILE (PREDICATE) {BLOCK} statement */
    class Statement_While:public Statement {
    private:
        Predicate* condition;
        Block* loop_body;
    };

/* a unit GOTO/GOSUB (BLOCK) statement */
    class Statement_Goto:public Statement {
    private:
        bool returning;
        Block* target;
    };
}

#endif /*STATEMENT_H*/

