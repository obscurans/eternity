/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#pragma once
#ifndef TOKEN_H
#define TOKEN_H

namespace Eternity {
    enum Token {
        IDENTIFIER,
        DECIMAL,
        BINARY,
        OCTAL,
        HEXADECIMAL,
        FLOATING_POINT,
        STRING,
        LEFT_BRACE,
        RIGHT_BRACE,
        SEMICOLON,
        COMMA,
        TERNARY,
        COLON,
        LEFT_PARENTHESIS,
        RIGHT_PARENTHESIS,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        SCOPE,
        MEMBER,
        AMPERSAND,
        INCREMENT,
        DECREMENT,
        PLUS,
        MINUS,
        ASTERISK,
        DIVIDE,
        MODULO,
        LEFT_SHIFT,
        RIGHT_SHIFT,
        LESS_THAN,
        GREATER_THAN,
        LESS_THAN_EQUALS,
        GREATER_THAN_EQUALS,
        EQUALS,
        NOT_EQUALS,
        BITWISE_XOR,
        BITWISE_OR,
        BITWISE_NOT,
        LOGICAL_AND,
        LOGICAL_XOR,
        LOGICAL_OR,
        LOGICAL_NOT,
        ASSIGN,
        ADD_ASSIGN,
        SUBTRACT_ASSIGN,
        MULTIPLY_ASSIGN,
        DIVIDE_ASSIGN,
        MODULO_ASSIGN,
        LEFT_SHIFT_ASSIGN,
        RIGHT_SHIFT_ASSIGN,
        AND_ASSIGN,
        XOR_ASSIGN,
        OR_ASSIGN,
        EOF
    };
}

#endif /*TOKEN_H*/

