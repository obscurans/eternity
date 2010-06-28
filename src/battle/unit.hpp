/* Copyright (c) 2010 Andrew Crowell and Jeffrey Tsang, all rights reserved.    *
 * See /doc/license.txt for details on how this source can be licensed for use. */

#pragma once
#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <set>
#include <map>
using std::string;
using std::set;
using std::map;

namespace Eternity {
/* base class for game units */
    class Unit {
    private:
        int unit_id;
        string name;
        Location position;
        Battlefield& field;
        bool dirty;
        const map<int,Unit*>* unit_set_base;
        const set<int>* dunit_set_base;
        Node decision_root;
        map<string,Block> instructions;
        list<Buff*> buff_list;

        map<int,bool> mem_bool;
        map<int,int> mem_int;
        map<int,double> mem_real;
        map<int,string*> mem_str;
        map<int,Unit*> mem_unit;
        map<int,Location> mem_loc;
    public:
        bool modifyDecisions();
        bool modifyInstructions();

        int getID() const;
        string getName() const;
        Location getPosition() const;
        bool getDirty() const;
        const map<int,Unit*>* getUnitList() const;
        const set<int>* getDirtyUnitList() const;

        bool setID();
        bool setName(String);

        bool queryMemBool(int) const;
        int queryMemInt(int) const;
        double queryMemReal(int) const;
        string* queryMemString(int) const;
        Unit* queryMemUnit(int) const;
        Location queryMemLocation(int) const;

        bool cacheState();
        bool cacheStatus();

        bool elapseCallback(map<int,Unit*>::const_iterator, map<int,Unit*>::const_iterator, set<int>::const_iterator, set<int>::const_iterator); /* unit will act by calling Battlefield.scheduleEvent from this */

        bool applyState();
        bool applyStatus();
    };
}

#endif /*UNIT_H*/

