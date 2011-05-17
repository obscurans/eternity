/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#pragma once
#ifndef ETERNITY_PARSER_TOKEN_H
#define ETERNITY_PARSER_TOKEN_H

namespace Eternity {
    namespace Token {
        enum Type {
            IDENTIFIER,
            DECIMAL,
            BINARY,
            OCTAL,
            HEXADECIMAL,
            FLOATING_POINT,
            CHARACTER,
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
            END_OF_FILE,
            E_DECIMAL_CONCAT_ALPHA,
            E_BINARY_CONCAT_ALPHA,
            E_BINARY_INVALID_DIGIT,
            E_OCTAL_CONCAT_ALPHA,
            E_OCTAL_INVALID_DIGIT,
            E_HEXADECIMAL_CONCAT_ALPHA,
            E_FLOATING_MISSING_EXPONENT,
            E_CHARACTER_UNTERMINATED,
            E_STRING_UNTERMINATED,
            E_INVALID_CLOSE_COMMENT,
            E_COMMENT_UNTERMINATED
        };
    }
}

#endif /*ETERNITY_PARSER_TOKEN_H*/

