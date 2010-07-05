/* Copyright (c) 2010 Andrew Crowell and Jeffrey Tsang, all rights reserved.    *
 * See /doc/license.txt for details on how this source can be licensed for use. */

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
}

