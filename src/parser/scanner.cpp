/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#include "eternity.hpp"
#include "scanner.hpp"

namespace Eternity {
/*TODO: replace Xfunctions() and fix interface
 * Xoldchar, XEOF, Xconvertchar, Xstate, Xappend, Xdiscard, Xunget, Xclear, Xnewline
 */
    Token Scanner::next() {
        int c2 = Xoldchar;
        char c;
        if (c2 == XEOF) {
            return Token.EOF;
        }
        c = Xconvertchar(c2);
        Xclear();
        do {
            switch (Xstate) {
            case START:
                switch (c) {
                case '0':
                    Xappend(c);
                    Xstate = LEADING_ZERO;
                    break;
                case '1': case '2': case '3': case '4': case '5': case '6':
                case '7': case '8': case '9':
                    Xappend(c);
                    Xstate = DECIMAL_NUMBER;
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
                    Xappend(c);
                    Xstate = IDENTIFIER;
                    break;
                case ';':
                    Xappend(c);
                    return Token.SEMICOLON;
                case '{':
                    Xappend(c);
                    return Token.LEFT_BRACE;
                case '}':
                    Xappend(c);
                    return Token.RIGHT_BRACE;
                case '(':
                    Xappend(c);
                    return Token.LEFT_PARENTHESIS;
                case ')':
                    Xappend(c);
                    return Token.RIGHT_PARENTHESIS;
                case '[':
                    Xappend(c);
                    return Token.LEFT_BRACKET;
                case ']':
                    Xappend(c);
                    return Token.RIGHT_BRACKET;
                case '~':
                    Xappend(c);
                    return Token.BITWISE_NOT;
                case '?':
                    Xappend(c);
                    return Token.TERNARY;
                case '"':
                    Xappend(c);
                    Xstate = STRING;
                    break;
                case ':':
                    Xappend(c);
                    Xstate = COLON;
                    break;
                case '.':
                    Xappend(c);
                    Xstate = PERIOD;
                    break;
                case '+':
                    Xappend(c);
                    Xstate = PLUS;
                    break;
                case '-':
                    Xappend(c);
                    Xstate = MINUS;
                    break;
                case '*':
                    Xappend(c);
                    Xstate = ASTERISK;
                    break;
                case '%':
                    Xappend(c);
                    Xstate = PERCENT;
                    break;
                case '&':
                    Xappend(c);
                    Xstate = AMPERSAND;
                    break;
                case '|':
                    Xappend(c);
                    Xstate = PIPE;
                    break;
                case '^':
                    Xappend(c);
                    Xstate = CARET;
                    break;
                case '<':
                    Xappend(c);
                    Xstate = LT;
                    break;
                case '>':
                    Xappend(c);
                    Xstate = GT;
                    break;
                case '!':
                    Xappend(c);
                    Xstate = EXCLAMATION;
                    break;
                case '=':
                    Xappend(c);
                    Xstate = EQUALS;
                    break;
                case '/':
                    Xappend(c);
                    Xstate = SLASH;
                    break;
                case '\n':
                    Xdiscard(c);
                    Xnewline();
                    break;
                default: Xdiscard(c);
                }
                break;
            case IDENTIFIER:
                if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_')) {
                    Xappend(c);
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.IDENTIFIER;
                }
                break;
            case LEADING_ZERO:
                switch (c) {
                case '0': case '1': case '2': case '3': case '4': case '5':
                case '6': case '7': case '8': case '9': case '_':
                    Xappend(c);
                    Xstate = DECIMAL_NUMBER;
                    break;
                case 'E': case 'e':
                    Xappend(c);
                    Xstate = FLOATING_EXPONENT;
                    break;
                case 'b':
                    Xappend(c);
                    Xstate = BINARY_NUMBER;
                    break;
                case 'o':
                    Xappend(c);
                    Xstate = OCTAL_NUMBER;
                    break;
                case 'x':
                    Xappend(c);
                    Xstate = HEX_NUMBER;
                    break;
                case '.':
                    Xappend(c);
                    Xstate = FLOATING_POINT;
                    break;
                default:
                    Xunget(c);
                    Xstate = START;
                    return Token.DECIMAL_NUMBER;
                }
                break;
            case DECIMAL_NUMBER:
                switch(c) {
                case '0': case '1': case '2': case '3': case '4': case '5':
                case '6': case '7': case '8': case '9': case '_':
                    Xappend(c);
                    break;
                case '.':
                    Xappend(c);
                    Xstate = FLOATING_POINT;
                    break;
                default:
                    Xunget(c);
                    Xstate = START;
                    return Token.DECIMAL;
                }
                break;
            case BINARY_NUMBER:
                if ((c >= '0' && c <= '1') || (c == '_')) {
                    Xappend(c);
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.BINARY;
                }
                break;
            case OCTAL_NUMBER:
                if ((c >= '0' && c <= '7') || (c == '_')) {
                    Xappend(c);
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.OCTAL;
                }
                break;
            case HEX_NUMBER:
                if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c == '_')) {
                    Xappend(c);
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.HEXADECIMAL;
                }
                break;
            case FLOATING_POINT:
                switch (c) {
                case '0': case '1': case '2': case '3': case '4': case '5':
                case '6': case '7': case '8': case '9': case '_':
                    Xappend(c);
                    break;
                case 'E': case 'e':
                    Xappend(c);
                    Xstate = FLOATING_EXPONENT;
                    break;
                default:
                    Xunget(c);
                    Xstate = START;
                    return Token.FLOATING_POINT;
                }
                break;
            case FLOATING_EXPONENT:
                if ((c >= '0' && c <= '9') || (c == '_') || (c == '+') || (c == '-')) {
                    Xappend(c);
                    Xstate = FLOATING_EXPONENT_SIGN;
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.FLOATING_POINT;
                }
                break;
            case FLOATING_EXPONENT_SIGN:
                if ((c >= '0' && c <= '9') || (c == '_')) {
                    Xappend(c);
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.FLOATING_POINT;
                }
                break;
            case COLON:
                if (c == ':') {
                    Xappend(c);
                    Xstate = START;
                    return Token.SCOPE;
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.COLON;
                }
            case PERIOD:
                if (c >= '0' && c <= '9') {
                    Xappend(c);
                    Xstate = FLOATING_POINT;
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.MEMBER;
                }
                break;
            case PLUS:
                switch (c) {
                case '+':
                    Xappend(c);
                    Xstate = START;
                    return Token.INCREMENT;
                case '=':
                    Xappend(c);
                    Xstate = START;
                    return Token.ADD_ASSIGN;
                default:
                    Xunget(c);
                    Xstate = START;
                    return Token.PLUS;
                }
            case MINUS:
                switch (c) {
                case '-':
                    Xappend(c);
                    Xstate = START;
                    return Token.DECREMENT;
                case '=':
                    Xappend(c);
                    Xstate = START;
                    return Token.SUBTRACT_ASSIGN;
                default:
                    Xunget(c);
                    Xstate = START;
                    return Token.MINUS;
                }
            case ASTERISK:
                if (c == '=') {
                    Xappend(c);
                    Xstate = START;
                    return Token.MULTIPLY_ASSIGN;
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.ASTERISK;
                }
            case PERCENT:
                if (c == '=') {
                    Xappend(c);
                    Xstate = START;
                    return Token.MODULO_ASSIGN;
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.MODULO;
                }
            case AMPERSAND:
                switch (c) {
                case '&':
                    Xappend(c);
                    Xstate = START;
                    return Token.LOGICAL_AND;
                case '=':
                    Xappend(c);
                    Xstate = START;
                    return Token.AND_ASSIGN;
                default:
                    Xunget(c);
                    Xstate = START;
                    return Token.AMPERSAND;
                }
            case PIPE:
                switch (c) {
                case '|':
                    Xappend(c);
                    Xstate = START;
                    return Token.LOGICAL_OR;
                case '=':
                    Xappend(c);
                    Xstate = START;
                    return Token.OR_ASSIGN;
                default:
                    Xunget(c);
                    Xstate = START;
                    return Token.BITWISE_OR;
                }
            case CARET:
                switch (c) {
                case '^':
                    Xappend(c);
                    Xstate = START;
                    return Token.LOGICAL_XOR;
                case '=':
                    Xappend(c);
                    Xstate = START;
                    return Token.XOR_ASSIGN;
                default:
                    Xunget(c);
                    Xstate = START;
                    return Token.BITWISE_XOR;
                }
            case LT:
                switch (c) {
                case '<':
                    Xappend(c);
                    Xstate = LT_LT;
                    break;
                case '=':
                    Xappend(c);
                    Xstate = START;
                    return Token.LESS_THAN_EQUALS;
                default:
                    Xunget(c);
                    Xstate = START;
                    return Token.LESS_THAN;
                }
                break;
            case GT:
                switch (c) {
                case '>':
                    Xappend(c);
                    Xstate = GT_GT;
                    break;
                case '=':
                    Xappend(c);
                    Xstate = START;
                    return Token.GREATER_THAN_EQUALS;
                default:
                    Xunget(c);
                    Xstate = START;
                    return Token.GREATER_THAN;
                }
                break;
            case LT_LT:
                if (c == '=') {
                    Xappend(c);
                    Xstate = START;
                    return Token.LEFT_SHIFT_ASSIGN;
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.LEFT_SHIFT;
                }
            case GT_GT:
                if (c == '=') {
                    Xappend(c);
                    Xstate = START;
                    return Token.RIGHT_SHIFT_ASSIGN;
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.RIGHT_SHIFT;
                }
            case EXCLAMATION:
                if (c == '=') {
                    Xappend(c);
                    Xstate = START;
                    return Token.NOT_EQUALS;
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.LOGICAL_NOT;
                }
            case EQUALS:
                if (c == '=') {
                    Xappend(c);
                    Xstate = START;
                    return Token.EQUALS;
                } else {
                    Xunget(c);
                    Xstate = START;
                    return Token.ASSIGN;
                }
            case STRING:
                switch (c) {
                case '"':
                    Xappend(c);
                    Xstate = START;
                    return Token.STRING;
                case '\':
                    Xappend(c);
                    Xstate = STRING_ESCAPE;
                    break;
                default: Xappend(c);
                }
                break;
            case STRING_ESCAPE:
                Xappend(c);
                Xstate = STRING;
                break;
            case SLASH:
                switch (c) {
                case '=':
                    Xappend(c);
                    Xstate = START;
                    return Token.DIVIDE_ASSIGN;
                case '/':
                    Xdiscard(c);
                    Xstate = SLASH_SLASH;
                    break;
                case '*':
                    Xdiscard(c);
                    Xstate = SLASH_STAR;
                    break;
                default:
                    Xunget(c);
                    Xstate = START;
                    return Token.DIVIDE;
                }
            case SLASH_SLASH:
                if (c == '\n') {
                    Xclear();
                    Xnewline();
                    Xstate = START;
                }
                Xdiscard(c);
                break;
            case SLASH_STAR:
                if (c == '*') {
                    Xstate = SLASH_STAR_STAR;
                }
                Xdiscard(c);
                break;
            case SLASH_STAR_STAR:
                switch (c) {
                case '/':
                    Xclear();
                    Xstate = START;
                    break;
                case '*': break;
                default: Xstate = SLASH_STAR;
                }
                Xdiscard(c);
                break;
        } while (/**/);
    }
}

