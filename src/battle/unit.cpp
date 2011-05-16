/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#include "eternity.hpp"
#include "unit.hpp"

namespace Eternity {
/* Unit class methods */
    int Unit::getID() const {
        return unit_id;
    }

    string Unit::getName() const {
        return name;
    }

    Location Unit::getPosition() const {
        return position;
    }

    bool Unit::getDirty() const {
        return dirty;
    }

    const map<int,Unit*>* Unit::getUnitList() const {
        return unit_set_base;
    }

    const map<int,Unit*>* Unit::getDirtyUnitList() const {
        return dunit_set_base;
    }

    bool Unit::setID(int new_id) {
        unit_id = new_id;
        return true;
    }

    bool Unit::setName(string new_name) {
        name = new_name;
        return true;
    }

    bool Unit::retCurNode(Node* last_node, Node* past_filter, const map<int,Unit*>* punit_set, const map<int,Unit*>* pdunit_set, int timer_surplus) {
        cur_node = last_node;
        cur_filter = past_filter;
        unit_set_cur = punit_set;
        dunit_set_cur = pdunit_set;
        timer_carry = timer_surplus;
        return true;
    }

    /* these memory accesses are unchecked since the GUI/loading routines will prevent programming in an invalid index */
    bool queryMemBool(int index) const {
        return mem_bool[index];
    }

    int queryMemInt(int index) const {
        return mem_int[index];
    }

    double queryMemReal(int index) const {
        return mem_real[index];
    }

    string* queryMemString(int index) const {
        return mem_str[index];
    }

    Unit* queryMemUnit(int index) const {
        return mem_unit[index];
    }

    Location* queryMemLocation(int index) const {
        return mem_loc[index];
    }

    bool elapseCallback(const map<int,Unit*>* unit_base, const map<int,Unit*>* dunit_base) {
        unit_set_base = unit_base;
        if (exec_decision) {
            /* last tick did not clear decision tree, combine past/current dirty unit lists */
            dunit_set_base.insert(dunit_base->begin(), dunit_base->end());
            if ((timer_carry += /*TODO timer base */0) >= 0) {
                exec_decision = cur_node->evaluate(this, cur_filter, unit_set_cur, dunit_set_cur, timer_carry);
            }
        } else {
            /* new tick will restart from decision tree root, only current dirty units needed */
            dunit_set_base = dunit_base;
            if ((timer_carry += /*TODO timer base */0) >= 0) {
                exec_decision = decision_root.evaluate(this, NULL, unit_set_base, dunit_set_base, timer_carry);
            }
        }
    }
}

