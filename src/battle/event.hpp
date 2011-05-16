/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#pragma once
#ifndef EVENT_H
#define EVENT_H

#include <list>
#include <map>
#include <multimap>
using std::list;
using std::map;
using std::multimap;

namespace Eternity {
/* a game-play event */
    class Event {
    protected:
        Unit invoker;
        map<Filter,list<Effect>> effect_list;
    public:
        virtual bool occur();
        virtual bool isContinuous() const;
/* TODO */
    };

/* a continuous game-play event */
    class Continuous:public Event {
    private:
        Condition ending;
    public:
        bool occur();
        bool isContinuous() const;
    };

/* a game-play effect */
    class Effect {
    public:
        bool affect(Unit*);
/* TODO */
    };

/* wrapper for event queue references */
    class EventRef {
    private:
        multimap<int,Event*>::iterator reference;
    public:
        EventRef(multimap<int,Event*>::iterator);

        int getTick() const;
        Event* getEvent() const;
        multimap<int,Event*>::iterator getIterator() const;
    };

/* wrapper for continuous event references */
    class ContRef {
    private:
        list<Continuous*>::iterator reference;
    public:
        ContRef(list<Continuous*>::iterator);

        Continuous* getEvent() const;
        list<Continuous*>::iterator getIterator() const;
    };
}

#endif /*EVENT_H*/

