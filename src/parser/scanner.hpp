/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#pragma once
#ifndef ETERNITY_PARSER_SCANNER_H
#define ETERNITY_PARSER_SCANNER_H

#include "token.hpp"
#include <string>
#include <istream>
using std::string
using std::istream

namespace Eternity {
    class Scanner {
    private:
        enum State {
            START,
            IDENTIFIER,
            LEADING_ZERO,
            DECIMAL_NUMBER,
            BINARY_NUMBER,
            OCTAL_NUMBER,
            HEX_NUMBER,
            FLOATING_POINT,
            FLOATING_EXPONENT,
            FLOATING_EXPONENT_SIGN,
            CHARACTER,
            CHARACTER_ESCAPE,
            STRING,
            STRING_ESCAPE,
            COLON,
            PERIOD,
            PLUS,
            MINUS,
            ASTERISK,
            PERCENT,
            AMPERSAND,
            PIPE,
            CARET,
            LT,
            GT,
            LT_LT,
            GT_GT,
            EXCLAMATION,
            EQUALS,
            SLASH,
            SLASH_SLASH,
            SLASH_STAR,
            SLASH_STAR_STAR,
            WHITESPACE
        };

        bool input_eof;
        char c;
        int line, col;
        State state;
        string buffer;
        istream input;

        void advanceAppend();
        void handleNewline();
        Token::Type tokenReturn(Token::Type, int&, int&);
    public:
        Scanner();

        Token::Type getToken(int&, int&, int&, int&);
    };
}

#endif /*ETERNITY_PARSER_SCANNER_H*/

