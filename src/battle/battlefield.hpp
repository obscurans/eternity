/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#pragma once
#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <string>
#include <list>
#include <map>
#include <multimap>
using std::string;
using std::list;
using std::map;
using std::multimap;

namespace Eternity {
/* the exposed interface for the battlefield class */
    class Battlefield_Interface {
    public:
        virtual int elapseGameTime(int) = 0;

        virtual bool toggleIssuePause() = 0;
        virtual bool playerInterrupt() = 0;                         /* player interrupts execution handler */
        virtual bool requestInterrupt(const Unit*, string) = 0;     /* unit interrupt request handler */

        virtual int insertOrder(const Order*) = 0;
        virtual bool deleteOrder(int) = 0;

        virtual bool registerUnit(const Unit*) = 0;                 /* register a Unit onto the map */
        virtual bool renameUnit(int, string) = 0;                   /* wrapper for renaming a specific Unit */
        virtual bool deleteUnit(int) = 0;                           /* de-register a Unit off the map */

        virtual Unit* getUnit(int) const = 0;                       /* retrieve a Unit by unit_ID */
    };

/* the base class for the entire battlefield */
    class Battlefield:public Battlefield_Interface {
    private:
        bool paused;                        /* whether game is in decision phase */
        bool issue_pause;                   /* will the game pause after current issue */
        int game_tick;                      /* game tick currently calculated */

        list<Order*> order_queue;           /* list of all orders pending */
        multimap<int,Event*> event_queue;   /* (tick,event) multimap queue */
        list<Continuous*> event_continuous; /* list of all continuous events */
        map<int,Unit*> unit_list;           /* (ID,unit) list of all units on map */
        map<int,bool*> dunit_temp;          /* (ID,isDirty) list of all units dirtied this tick */
        set<int> dunit_list;                /* ID list of all units dirtied this tick */

        void elapseTick();
        bool cacheStatus();
        bool applyStatus();
        bool issueOrder(Order*);
        void handleEvent(const Event*);
        bool handleContinuous(const Continuous*);
    public:
        Battlefield();
        ~Battlefield();

        int elapseGameTime(int);

        bool toggleIssuePause();
        bool playerInterrupt();
        bool requestInterrupt(const Unit*, string);

        int insertOrder(const Order*);
        bool deleteOrder(int);

        EventRef scheduleEvent(const Event*, int);      /* schedule an Event specified ticks later */
        EventRef delayEvent(EventRef, int);             /* delay an already scheduled Event */
        bool deleteEvent(EventRef);                     /* delete an already scheduled Event */

        ContRef registerContinuous(const Continuous*);  /* register a Continuous event */
        bool deleteContinuous(ContRef);                 /* de-register a Continuous event */

        bool registerUnit(const Unit*);
        bool renameUnit(int, string);
        bool deleteUnit(int);

        Unit* getUnit(int) const;
        const map<int,Unit*>* getUnitList() const;      /* retrieve the full list of map Units */
        const set<int>* getDirtyUnitsStart() const;     /* retrieve the ID list of Units dirtied this tick */
    };
}

#endif /*BATTLEFIELD_H*/

