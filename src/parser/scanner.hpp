/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#pragma once
#ifndef SCANNER_H
#define SCANNER_H

#include "token.hpp"

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
        };
    };
}

#endif /*SCANNER_H*/

