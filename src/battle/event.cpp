/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#include "eternity.hpp"
#include "event.hpp"

namespace Eternity {
/* Event class methods */
    virtual bool Event::isContinuous() {
        return false;
    }

/* Continuous class methods */
    bool Continuous::isContinuous() {
        return true;
    }

/* EventRef class methods */
    EventRef::EventRef(multimap<int,Event*>::iterator input) {
        reference = input;
    }

    int EventRef::getTick() const {
        return reference->first;
    }

    Event* EventRef::getEvent() const {
        return reference->second;
    }

    multimap<int,Event*>::iterator EventRef::getIterator() const {
        return reference;
    }

/* ContRef class methods */
    ContRef::ContRef(list<Continuous*>::iterator input) {
        reference = input;
    }

    Continuous* ContRef::getEvent() const {
        return *reference;
    }

    list<Continuous*>::iterator ContRef::getIterator() const {
        return reference;
    }
}

