/* Copyright (c) 2010 Andrew Crowell and Jeffrey Tsang, all rights reserved.    *
 * See /doc/license.txt for details on how this source can be licensed for use. */

#pragma once
#ifndef PREDICATE_H
#define PREDICATE_H

namespace Eternity {
/* a boolean-logic condition statement, implicitly framed in terms of the caller */
    class Predicate {
    protected:
/* TODO */
    };

/* a boolean unit-selection filter */
    class Filter:public Predicate {
/* TODO */
    };

/* a boolean unit-comparison function */
    class Comparer:public Predicate {
/* TODO */
    };
}

#endif /*PREDICATE_H*/

