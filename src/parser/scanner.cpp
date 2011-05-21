/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#include "eternity.hpp"
#include "scanner.hpp"

namespace Eternity {
/* Scanner class methods */
    void Scanner::advanceAppend() {
        buffer.push_back(c);
        input.get(c);
        /* 'EOF' misnomer: waits for no character read; badbit/failbit gets exception thrown */
        if (input.gcount() == 0) {
            input_eof = true;
        }
        col++;
    }

    inline void Scanner::handleNewline() {
        line++;
        col = 0;
    }

    inline Token::Type Scanner::tokenReturn(Token::Type retval, int& eline, int& ecol) {
        eline = line;
        ecol = col;
        return retval;
    }

    Token::Type Scanner::getToken(int& sline, int& scol, int& eline, int& ecol) {
        sline = line;
        scol = col;
        buffer.clear();
        while (!input_eof) {
            switch (state) {
            case START:
                switch (c) {
                case '0':
                    advanceAppend();
                    state = LEADING_ZERO;
                    break;
                case '1': case '2': case '3': case '4': case '5': case '6':
                case '7': case '8': case '9':
                    advanceAppend();
                    state = DECIMAL_NUMBER;
                    break;
                case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
                case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
                case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
                case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
                case 'Y': case 'Z': case 'a': case 'b': case 'c': case 'd':
                case 'e': case 'f': case 'g': case 'h': case 'i': case 'j':
                case 'k': case 'l': case 'm': case 'n': case 'o': case 'p':
                case 'q': case 'r': case 's': case 't': case 'u': case 'v':
                case 'w': case 'x': case 'y': case 'z': case '_':
                    advanceAppend();
                    state = IDENTIFIER;
                    break;
                case ';':
                    advanceAppend();
                    return tokenReturn(Token::SEMICOLON, eline, ecol);
                case '{':
                    advanceAppend();
                    return tokenReturn(Token::LEFT_BRACE, eline, ecol);
                case '}':
                    advanceAppend();
                    return tokenReturn(Token::RIGHT_BRACE, eline, ecol);
                case '(':
                    advanceAppend();
                    return tokenReturn(Token::LEFT_PARENTHESIS, eline, ecol);
                case ')':
                    advanceAppend();
                    return tokenReturn(Token::RIGHT_PARENTHESIS, eline, ecol);
                case '[':
                    advanceAppend();
                    return tokenReturn(Token::LEFT_BRACKET, eline, ecol);
                case ']':
                    advanceAppend();
                    return tokenReturn(Token::RIGHT_BRACKET, eline, ecol);
                case '~':
                    advanceAppend();
                    return tokenReturn(Token::BITWISE_NOT, eline, ecol);
                case '?':
                    advanceAppend();
                    return tokenReturn(Token::TERNARY, eline, ecol);
                case '\'':
                    advanceAppend();
                    state = CHARACTER;
                case '"':
                    advanceAppend();
                    state = STRING;
                    break;
                case ':':
                    advanceAppend();
                    state = COLON;
                    break;
                case '.':
                    advanceAppend();
                    state = PERIOD;
                    break;
                case '+':
                    advanceAppend();
                    state = PLUS;
                    break;
                case '-':
                    advanceAppend();
                    state = MINUS;
                    break;
                case '*':
                    advanceAppend();
                    state = ASTERISK;
                    break;
                case '%':
                    advanceAppend();
                    state = PERCENT;
                    break;
                case '&':
                    advanceAppend();
                    state = AMPERSAND;
                    break;
                case '|':
                    advanceAppend();
                    state = PIPE;
                    break;
                case '^':
                    advanceAppend();
                    state = CARET;
                    break;
                case '<':
                    advanceAppend();
                    state = LT;
                    break;
                case '>':
                    advanceAppend();
                    state = GT;
                    break;
                case '!':
                    advanceAppend();
                    state = EXCLAMATION;
                    break;
                case '=':
                    advanceAppend();
                    state = EQUALS;
                    break;
                case '/':
                    advanceAppend();
                    state = SLASH;
                    break;
                case '\n':
                    advanceAppend();
                    handleNewline();
                    state = WHITESPACE;
                    break;
                default:
                    advanceAppend();
                    state = WHITESPACE;
                }
                break;
            case IDENTIFIER:
                if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_')) {
                    advanceAppend();
                } else {
                    state = START;
                    return tokenReturn(Token::IDENTIFIER, eline, ecol);
                }
                break;
            case LEADING_ZERO:
                switch (c) {
                case '0': case '1': case '2': case '3': case '4': case '5':
                case '6': case '7': case '8': case '9': case '_':
                    advanceAppend();
                    state = DECIMAL_NUMBER;
                    break;
                case 'E': case 'e':
                    advanceAppend();
                    state = FLOATING_EXPONENT;
                    break;
                case 'b':
                    advanceAppend();
                    state = BINARY_NUMBER;
                    break;
                case 'o':
                    advanceAppend();
                    state = OCTAL_NUMBER;
                    break;
                case 'x':
                    advanceAppend();
                    state = HEX_NUMBER;
                    break;
                case '.':
                    advanceAppend();
                    state = FLOATING_POINT;
                    break;
                default:
                    state = START;
                    return tokenReturn(Token::DECIMAL_NUMBER, eline, ecol);
                }
                break;
            case DECIMAL_NUMBER:
                switch(c) {
                case '0': case '1': case '2': case '3': case '4': case '5':
                case '6': case '7': case '8': case '9': case '_':
                    advanceAppend();
                    break;
                case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
                case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
                case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
                case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
                case 'Y': case 'Z': case 'a': case 'b': case 'c': case 'd':
                case 'e': case 'f': case 'g': case 'h': case 'i': case 'j':
                case 'k': case 'l': case 'm': case 'n': case 'o': case 'p':
                case 'q': case 'r': case 's': case 't': case 'u': case 'v':
                case 'w': case 'x': case 'y': case 'z':
                    state = START;
                    return tokenReturn(Token::E_DECIMAL_INVALID, eline, ecol);
                case '.':
                    advanceAppend();
                    state = FLOATING_POINT;
                    break;
                default:
                    state = START;
                    return tokenReturn(Token::DECIMAL, eline, ecol);
                }
                break;
            case BINARY_NUMBER:
                switch (c) {
                case '0': case '1': case '_':
                    advanceAppend();
                    break;
                case '2': case '3': case '4': case '5': case '6': case '7':
                case '8': case '9': case 'A': case 'B': case 'C': case 'D':
                case 'E': case 'F': case 'G': case 'H': case 'I': case 'J':
                case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
                case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V':
                case 'W': case 'X': case 'Y': case 'Z': case 'a': case 'b':
                case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
                case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
                case 'o': case 'p': case 'q': case 'r': case 's': case 't':
                case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
                    state = START;
                    return tokenReturn(Token::E_BINARY_INVALID_DIGIT, eline, ecol);
                default:
                    state = START;
                    return tokenReturn(Token::BINARY, eline, ecol);
                }
                break;
            case OCTAL_NUMBER:
                switch (c) {
                case '0': case '1': case '2': case '3': case '4': case '5':
                case '6': case '7': case '_':
                    advanceAppend();
                    break;
                case '8': case '9': case 'A': case 'B': case 'C': case 'D':
                case 'E': case 'F': case 'G': case 'H': case 'I': case 'J':
                case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
                case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V':
                case 'W': case 'X': case 'Y': case 'Z': case 'a': case 'b':
                case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
                case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
                case 'o': case 'p': case 'q': case 'r': case 's': case 't':
                case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
                    state = START;
                    return tokenReturn(Token::E_OCTAL_INVALID, eline, ecol);
                default:
                    state = START;
                    return tokenReturn(Token::OCTAL, eline, ecol);
                }
                break;
            case HEX_NUMBER:
                switch (c) {
                case '0': case '1': case '2': case '3': case '4': case '5':
                case '6': case '7': case '8': case '9': case '_': case 'A':
                case 'B': case 'C': case 'D': case 'E': case 'F': case 'a':
                case 'b': case 'c': case 'd': case 'e': case 'f':
                    advanceAppend();
                    break;
                case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
                case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
                case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
                case 'Y': case 'Z': case 'e': case 'f': case 'g': case 'h':
                case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
                case 'o': case 'p': case 'q': case 'r': case 's': case 't':
                case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
                    state = START;
                    return tokenReturn(Token::E_HEXADECIMAL_INVALID, eline, ecol);
                default:
                    state = START;
                    return tokenReturn(Token::HEXADECIMAL, eline, ecol);
                }
                break;
            case FLOATING_POINT:
                switch (c) {
                case '0': case '1': case '2': case '3': case '4': case '5':
                case '6': case '7': case '8': case '9': case '_':
                    advanceAppend();
                    break;
                case 'E': case 'e':
                    advanceAppend();
                    state = FLOATING_EXPONENT;
                    break;
                default:
                    state = START;
                    return tokenReturn(Token::FLOATING_POINT, eline, ecol);
                }
                break;
            case FLOATING_EXPONENT:
                if ((c >= '0' && c <= '9') || (c == '_') || (c == '+') || (c == '-')) {
                    advanceAppend();
                    state = FLOATING_EXPONENT_SIGN;
                } else {
                    state = START;
                    return tokenReturn(Token::E_FLOATING_MISSING_EXPONENT, eline, ecol);
                }
                break;
            case FLOATING_EXPONENT_SIGN:
                if ((c >= '0' && c <= '9') || (c == '_')) {
                    advanceAppend();
                } else {
                    state = START;
                    return tokenReturn(Token::FLOATING_POINT, eline, ecol);
                }
                break;
            case COLON:
                if (c == ':') {
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::SCOPE, eline, ecol);
                } else {
                    state = START;
                    return tokenReturn(Token::COLON, eline, ecol);
                }
            case PERIOD:
                if (c >= '0' && c <= '9') {
                    advanceAppend();
                    state = FLOATING_POINT;
                } else {
                    state = START;
                    return tokenReturn(Token::MEMBER, eline, ecol);
                }
                break;
            case PLUS:
                switch (c) {
                case '+':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::INCREMENT, eline, ecol);
                case '=':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::ADD_ASSIGN, eline, ecol);
                default:
                    state = START;
                    return tokenReturn(Token::PLUS, eline, ecol);
                }
            case MINUS:
                switch (c) {
                case '-':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::DECREMENT, eline, ecol);
                case '=':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::SUBTRACT_ASSIGN, eline, ecol);
                default:
                    state = START;
                    return tokenReturn(Token::MINUS, eline, ecol);
                }
            case ASTERISK:
                switch (c) {
                case '=':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::MULTIPLY_ASSIGN, eline, ecol);
                case '/':
                    state = START;
                    return tokenReturn(Token::E_INVALID_CLOSE_COMMENT, eline, ecol);
                default:
                    state = START;
                    return tokenReturn(Token::ASTERISK, eline, ecol);
                }
            case PERCENT:
                if (c == '=') {
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::MODULO_ASSIGN, eline, ecol);
                } else {
                    state = START;
                    return tokenReturn(Token::MODULO, eline, ecol);
                }
            case AMPERSAND:
                switch (c) {
                case '&':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::LOGICAL_AND, eline, ecol);
                case '=':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::AND_ASSIGN, eline, ecol);
                default:
                    state = START;
                    return tokenReturn(Token::AMPERSAND, eline, ecol);
                }
            case PIPE:
                switch (c) {
                case '|':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::LOGICAL_OR, eline, ecol);
                case '=':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::OR_ASSIGN, eline, ecol);
                default:
                    state = START;
                    return tokenReturn(Token::BITWISE_OR, eline, ecol);
                }
            case CARET:
                switch (c) {
                case '^':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::LOGICAL_XOR, eline, ecol);
                case '=':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::XOR_ASSIGN, eline, ecol);
                default:
                    state = START;
                    return tokenReturn(Token::BITWISE_XOR, eline, ecol);
                }
            case LT:
                switch (c) {
                case '<':
                    advanceAppend();
                    state = LT_LT;
                    break;
                case '=':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::LESS_THAN_EQUALS, eline, ecol);
                default:
                    state = START;
                    return tokenReturn(Token::LESS_THAN, eline, ecol);
                }
                break;
            case GT:
                switch (c) {
                case '>':
                    advanceAppend();
                    state = GT_GT;
                    break;
                case '=':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::GREATER_THAN_EQUALS, eline, ecol);
                default:
                    state = START;
                    return tokenReturn(Token::GREATER_THAN, eline, ecol);
                }
                break;
            case LT_LT:
                if (c == '=') {
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::LEFT_SHIFT_ASSIGN, eline, ecol);
                } else {
                    state = START;
                    return tokenReturn(Token::LEFT_SHIFT, eline, ecol);
                }
            case GT_GT:
                if (c == '=') {
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::RIGHT_SHIFT_ASSIGN, eline, ecol);
                } else {
                    state = START;
                    return tokenReturn(Token::RIGHT_SHIFT, eline, ecol);
                }
            case EXCLAMATION:
                if (c == '=') {
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::NOT_EQUALS, eline, ecol);
                } else {
                    state = START;
                    return tokenReturn(Token::LOGICAL_NOT, eline, ecol);
                }
            case EQUALS:
                if (c == '=') {
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::EQUALS, eline, ecol);
                } else {
                    state = START;
                    return tokenReturn(Token::ASSIGN, eline, ecol);
                }
            case CHARACTER:
                switch (c) {
                case '\'':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::CHARACTER, eline, ecol);
                case '\\':
                    advanceAppend();
                    state = CHARACTER_ESCAPE;
                    break;
                case '\n':
                    state = START;
                    return tokenReturn(Token::E_CHARACTER_UNTERMINATED, eline, ecol);
                default: advanceAppend();
                }
                break;
            case CHARACTER_ESCAPE:
                if (c == '\n') {
                    state = START;
                    return tokenReturn(Token::E_CHARACTER_UNTERMINATED, eline, ecol);
                } else {
                    advanceAppend();
                    state = CHARACTER;
                }
                break;
            case STRING:
                switch (c) {
                case '"':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::STRING, eline, ecol);
                case '\\':
                    advanceAppend();
                    state = STRING_ESCAPE;
                    break;
                case '\n':
                    state = START;
                    return tokenReturn(Token::E_STRING_UNTERMINATED, eline, ecol);
                default: advanceAppend();
                }
                break;
            case STRING_ESCAPE:
                if (c == '\n') {
                    state = START;
                    return tokenReturn(Token::E_STRING_UNTERMINATED, eline, ecol);
                } else {
                    advanceAppend();
                    state = STRING;
                }
                break;
            case SLASH:
                switch (c) {
                case '=':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::DIVIDE_ASSIGN, eline, ecol);
                case '/':
                    advanceDiscard();
                    state = SLASH_SLASH;
                    break;
                case '*':
                    advanceDiscard();
                    state = SLASH_STAR;
                    break;
                default:
                    state = START;
                    return tokenReturn(Token::DIVIDE, eline, ecol);
                }
            case SLASH_SLASH:
                if (c == '\n') {
                    advanceAppend();
                    handleNewline();
                    state = START;
                    return tokenReturn(Token::COMMENT, eline, ecol);
                }
                advanceAppend();
                break;
            case SLASH_STAR:
                if (c == '*') {
                    state = SLASH_STAR_STAR;
                }
                advanceAppend();
                break;
            case SLASH_STAR_STAR:
                switch (c) {
                case '/':
                    advanceAppend();
                    state = START;
                    return tokenReturn(Token::COMMENT, eline, ecol);
                    break;
                case '*': break;
                default: state = SLASH_STAR;
                }
                advanceAppend();
                break;
            case WHITESPACE:
                switch (c) {
                case '0': case '1': case '2': case '3': case '4': case '5':
                case '6': case '7': case '8': case '9': case 'A': case 'B':
                case 'C': case 'D': case 'E': case 'F': case 'G': case 'H':
                case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
                case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T':
                case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
                case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
                case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
                case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
                case 's': case 't': case 'u': case 'v': case 'w': case 'x':
                case 'y': case 'z': case '_': case ';': case '{': case '}':
                case '(': case ')': case '[': case ']': case '~': case '?':
                case '\'': case '"': case ':': case '.': case '+': case '-':
                case '*': case '%': case '&': case '|': case '^': case '<':
                case '>': case '!': case '=': case '/':
                    state = START;
                    return tokenReturn(Token::WHITESPACE, eline, ecol);
                case '\n':
                    advanceAppend();
                    handleNewline();
                    break;
                default:
                    advanceAppend();
                }
                break;
            default:
                advanceAppend();
        }
        switch (state) {
        case START:
            return tokenReturn(Token::END_OF_FILE, eline, ecol);
        case IDENTIFIER:
            return tokenReturn(Token::IDENTIFIER, eline, ecol);
        case LEADING_ZERO:
        case DECIMAL_NUMBER:
            return tokenReturn(Token::DECIMAL, eline, ecol);
        case BINARY_NUMBER:
            return tokenReturn(Token::BINARY, eline, ecol);
        case OCTAL_NUMBER:
            return tokenReturn(Token::OCTAL, eline, ecol);
        case HEX_NUMBER:
            return tokenReturn(Token::HEXADECIMAL, eline, ecol);
        case FLOATING_POINT:
            return tokenReturn(Token::FLOATING_POINT, eline, ecol);
        case FLOATING_EXPONENT:
            return tokenReturn(Token::E_FLOATING_MISSING_EXPONENT, eline, ecol);
        case FLOATING_EXPONENT_SIGN:
            return tokenReturn(Token::FLOATING_POINT, eline, ecol);
        case CHARACTER:
        case CHARACTER_ESCAPE:
            return tokenReturn(Token::E_CHARACTER_UNTERMINATED, eline, ecol);
        case STRING:
        case STRING_ESCAPE:
            return tokenReturn(Token::E_STRING_UNTERMINATED, eline, ecol);
        case COLON:
            return tokenReturn(Token::COLON, eline, ecol);
        case PERIOD:
            return tokenReturn(Token::MEMBER, eline, ecol);
        case PLUS:
            return tokenReturn(Token::PLUS, eline, ecol);
        case MINUS:
            return tokenReturn(Token::MINUS, eline, ecol);
        case ASTERISK:
            return tokenReturn(Token::ASTERISK, eline, ecol);
        case PERCENT:
            return tokenReturn(Token::MODULO, eline, ecol);
        case AMPERSAND:
            return tokenReturn(Token::AMPERSAND, eline, ecol);
        case PIPE:
            return tokenReturn(Token::BITWISE_OR, eline, ecol);
        case CARET:
            return tokenReturn(Token::BITWISE_XOR, eline, ecol);
        case LT:
            return tokenReturn(Token::LESS_THAN, eline, ecol);
        case GT:
            return tokenReturn(Token::GREATER_THAN, eline, ecol);
        case LT_LT:
            return tokenReturn(Token::LEFT_SHIFT, eline, ecol);
        case GT_GT:
            return tokenReturn(Token::RIGHT_SHIFT, eline, ecol);
        case EXCLAMATION:
            return tokenReturn(Token::LOGICAL_NOT, eline, ecol);
        case EQUALS:
            return tokenReturn(Token::ASSIGN, eline, ecol);
        case SLASH:
            return tokenReturn(Token::DIVIDE, eline, ecol);
        case SLASH_SLASH:
            return tokenReturn(Token::END_OF_FILE_COMMENT, eline, ecol);
        case SLASH_STAR:
        case SLASH_STAR_STAR:
            return tokenReturn(Token::E_COMMENT_UNTERMINATED, eline, ecol);
        case WHITESPACE:
        default:
            return tokenReturn(Token::END_OF_FILE, eline, ecol);
        }
    }

    Scanner::Scanner():
            input_eof(true),
            line(0),
            col(0),
            state(START) {
/*TODO*/
        input.exceptions(ifstream::failbit | ifstream::badbit);
    }
}

