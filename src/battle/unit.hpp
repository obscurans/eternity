/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#pragma once
#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;

namespace Eternity {
/* base class for game units */
    class Unit {
    private:
        int unit_id;
        string name;
        Location position;
        Battlefield& field;
        list<Buff*> buff_list;

        bool dirty;
        const map<int,Unit*>* unit_set_base;
        const map<int,Unit*>* dunit_set_base;
        Node* cur_node;
        Node* cur_filter;
        const map<int,Unit*>* unit_set_cur;
        const map<int,Unit*>* dunit_set_cur;
        bool exec_decision;
        int timer_carry;

        Node decision_root;
        map<string,Block> instructions;
        vector<bool> mem_bool;
        vector<int> mem_int;
        vector<double> mem_real;
        vector<string*> mem_str;
        vector<Unit*> mem_unit;
        vector<Location> mem_loc;
    public:
        bool modifyDecisions();
        bool modifyInstructions();

        int getID() const;
        string getName() const;
        Location getPosition() const;
        bool getDirty() const;
        const map<int,Unit*>* getUnitList() const;
        const map<int,Unit*>* getDirtyUnitList() const;

        bool setID();
        bool setName(String);
        bool retTimerSurplus(int);
        bool retCurNode(Node*);

        bool queryMemBool(int) const;
        int queryMemInt(int) const;
        double queryMemReal(int) const;
        string* queryMemString(int) const;
        Unit* queryMemUnit(int) const;
        Location queryMemLocation(int) const;

        bool cacheState();
        bool cacheStatus();

        bool elapseCallback(const map<int,Unit*>*, const map<int,Unit*>*); /* unit will act by calling Battlefield.scheduleEvent from this */

        bool applyState();
        bool applyStatus();
    };
}

#endif /*UNIT_H*/

