/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#include "eternity.hpp"
#include "node.hpp"

namespace Eternity {
/* Node_Internal class methods */
    Node* Node_Internal::getFBranch() const {
        return f_branch;
    }

    Node* Node_Internal::getTBranch() const {
        return t_branch;
    }

    Predicate* Node_Internal::getTest() const {
        return test;
    }

    bool Node_Internal::setFBranch(const Node* new_branch) {
        f_branch = new_branch;
        modified = true;
        return true;
    }

    bool Node_Internal::setTBranch(const Node* new_branch) {
        t_branch = new_branch;
        modified = true;
        return true;
    }

    bool Node_Internal::setTest(const Predicate* new_test) {
        test = new_test;
        modified = true;
        return true;
    }

    bool Node_Internal::evaluate(Unit& caller, Node* passing_filter, const map<int,Unit*>* punit_set, const map<int,Unit*>* pdunit_set, int timer) {
        unit_set_b = punit_set;
        dunit_set_b = pdunit_set;
        last_filter = passing_filter;
        /* reevaluate if modified | TODO: check also for dirty */
        if (modified) {
            modified = false;
            satisfied = test->evaluate();
            timer -= test->cost();
        }
        /* return from executing decision tree with failure if timer has run out, else go forwards */
        if (satisfied) {
            if (timer < 0) {
                caller.retCurNode(t_branch, last_filter, unit_set_b, dunit_set_b, timer);
                return false;
            } else {
                return t_branch->evaluate(caller, last_filter, unit_set_b, dunit_set_b, timer);
            }
        } else {
            if (timer < 0) {
                caller.retCurNode(f_branch, last_filter, unit_set_b, dunit_set_b, timer);
                return false;
            } else {
                return f_branch->evaluate(caller, last_filter, unit_set_b, dunit_set_b, timer);
            }
        }
    }

/* Node_Filter class methods */
    Node* Node_Filter::getFBranch() const {
        return f_branch;
    }

    Node* Node_Filter::getTBranch() const {
        return t_branch;
    }

    Predicate_Filter* Node_Filter::getTest() const {
        return test;
    }

    bool Node_Filter::setFBranch(const Node* new_branch) {
        f_branch = new_branch;
        modified = true;
        return true;
    }

    bool Node_Filter::setTBranch(const Node* new_branch) {
        t_branch = new_branch;
        modified = true;
        return true;
    }

    bool Node_Filter::setTest(const Predicate_Filter* new_test) {
        test = new_test;
        modified = true;
        return true;
    }

    bool Node_Filter::evaluate(Unit& caller, Node* passing_filter, const map<int,Unit*>* punit_set, const map<int,Unit*>* pdunit_set, int timer) {
        int t_id;
        map<int,Unit*>::iterator unit_cur, unit_max, dunit_cur, dunit_tmp, dunit_max;
        map<int,Unit*>::const_iterator punit_cur, punit_max;
        dunit_set.clear();
        if (test->checkDirty() || (passing_filter != last_filter) || modified) {
            /* cache unusable, compute the filter-set from scratch */
            last_filter = passing_filter;
            modified = false;
            unit_set.swap(dunit_set);
            /* evaluate every unit in punit_set for inclusion into unit_set */
            unit_cur = unit_set.begin();
            for (punit_cur = punit_set->begin(), punit_max = punit_set->end(); punit_cur != punit_max; punit_cur++) {
                if (test->evaluate(punit_cur->second)) {
                    unit_cur = unit_set.insert(unit_cur, *punit_cur);
                }
                timer -= test->cost();
            }
            /* a unit past this filter is dirty if it (was in, now out), or vv, or if it was marked as dirty and (was in, now in)
             * (in unit_set <==> now in), (in dunit_set <==> was in), (in pdunit_set <==> was dirty) */
            dunit_cur = dunit_set.begin(); dunit_max = dunit_set.end();
            punit_cur = pdunit_set->begin(); punit_max = pdunit_set->end();
            for (unit_cur = tunit_set.begin(), unit_max = tunit_set.end(); unit_cur != unit_max; unit_cur++) {
                t_id = unit_cur->first;
                if (dunit_cur != dunit_max) {
                    while ((dunit_cur->first < t_id) && (++dunit_cur != dunit_max));
                    if ((dunit_cur != dunit_max) && (dunit_cur->first == t_id)) {
                        /* unit_cur in dunit_set */
                        if (punit_cur != punit_max) {
                            while ((punit_cur->first < t_id) && (++punit_cur != punit_max));
                            if ((punit_cur == punit_max) || punit_cur->first > t_id) {
                                /* unit_cur not in pdunit_set: remove from dunit_set */
                                dunit_set.erase(dunit_cur++);
                            }
                        } else {
                            /* pdunit_set iterated through, equal to above block */
                            dunit_set.erase(dunit_cur++);
                        }
                    } else {
                        /* unit_cur not in dunit_set: add to dunit_set */
                        dunit_tmp = dunit_cur;
                        dunit_set.insert(--dunit_tmp, *unit_cur);
                    }
                } else {
                    /* dunit_set iterated through, equal to above block */
                    dunit_tmp = dunit_cur;
                    dunit_set.insert(--dunit_tmp, *unit_cur);
                }
            }
        } else {
            /* cache valid, re-check all units marked dirty
             * a unit past this filter is dirty if it was marked dirty, and !(was out, now out) */
            unit_cur = unit_set.begin(); unit_max = unit_set.end();
            dunit_cur = dunit_set.begin();
            for (punit_cur = pdunit_set->begin(), punit_max = pdunit_set->end(); punit_cur != punit_max; punit_cur++) {
                t_id = punit_cur->first;
                if (test->evaluate(punit_cur->second)) {
                    if (unit_cur != unit_max) {
                        while ((unit_cur->first < t_id) && (++unit_cur != unit_max));
                        if ((unit_cur == unit_max) || (unit_cur->first > t_id)) {
                            /* punit_cur not in unit_set: add to unit_set */
                            unit_cur = unit_set.insert(--unit_cur, *punit_cur);
                        }
                    } else {
                        /* unit_set iterated through, equal to above block */
                        unit_cur = unit_set.insert(--unit_cur, *punit_cur);
                    }
                    dunit_cur = dunit_set.insert(dunit_cur, *punit_cur);
                } else {
                    if (unit_cur != unit_max) {
                        while ((unit_cur->first < t_id) && (++unit_cur != unit_max));
                        if ((unit_cur != unit_max) && (unit_cur->first == t_id)) {
                            /* punit_cur in unit_set: remove from unit_set and add to dunit_set */
                            unit_set.erase(unit_cur++);
                            dunit_cur = dunit_set.insert(dunit_cur, *punit_cur);
                        }
                    }
                }
                timer -= test->cost();
            }
        }
        /* return from executing decision tree with failure if timer has run out, else go forwards */
        if (satisfied = !unit_set.empty()) {
            if (timer < 0) {
                caller.retCurNode(t_branch, this, &unit_set, &dunit_set, timer);
                return false;
            } else {
                return t_branch->evaluate(caller, this, &unit_set, &dunit_set, timer);
            }
        } else {
            if (timer < 0) {
                caller.retCurNode(f_branch, NULL, NULL, NULL, timer);
                return false;
            } else {
                return f_branch->evaluate(caller, NULL, caller.getUnitList(), caller.getDirtyUnitList(), timer);
            }
        }
    }

/* Node_Terminal class methods */
    Block* Node_Terminal::getInstruction() const {
        return instruction;
    }

    Block_Timer* Node_Terminal::getInterrupt() const {
        return interrupt;
    }

    bool Node_Terminal::setInstruction(const Block* new_block) {
        instruction = new_block;
        modified = true;
        return true;
    }

    bool Node_Terminal::setInterrupt(const Block_Timer* new_block) {
        interrupt = new_block;
        modified = true;
        return true;
    }

    bool Node_Terminal::evaluate(Unit& caller, Node* passing_filter, const map<int,Unit*>* punit_set, const map<int,Unit*>* pdunit_set, int timer) {
        caller.retCurNode(this, NULL, NULL, NULL, timer);
        /* TODO: set target unit and invoke interrupt timer block if necessary */
        return true;
    }

/* Node_Sorter class methods */
    Block* Node_Sorter::getInstruction() const {
        return instruction;
    }

    Block_Timer* Node_Sorter::getInterrupt() const {
        return interrupt;
    }

    Block_Comparer* Node_Sorter::getRanking() const {
        return ranking;
    }

    bool Node_Sorter::setInstruction(Block* new_block) {
        instruction = new_block;
        modified = true;
        return true;
    }

    bool Node_Sorter::setInterrupt(Block_Timer* new_block) {
        interrupt = new_block;
        modified = true;
        return true;
    }

    bool Node_Sorter::setRanking(Block_Comparer* new_ranking) {
        ranking = new_ranking;
        modified = true;
        return true;
    }

    bool Node_Sorter::evaluate(Unit& caller, Node* passing_filter, const map<int,Unit*>* punit_set, const map<int,Unit*>* pdunit_set, int timer) {
        Unit* tmp_unit;
        double tmp_unit_rank;
        map<int,Unit*>::const_iterator punit_cur, punit_max;
        if (test->checkDirty() || (passing_filter != last_filter) || (punit_set->find(max_unit_id) == punit_set->end()) || (pdunit_set->find(max_unit_id) != pdunit_set->end()) || modified) {
            /* cache unusable, find the maximal unit from scratch */
            last_filter = passing_filter;
            modified = false;
            punit_cur = punit_set->begin();
            max_unit = punit_cur->second;
            for (punit_cur++, punit_max = punit_set->end(); punit_cur != punit_max; punit_cur++) {
                if ((tmp_unit_rank = ranking->invoke(tmp_unit = punit_cur->second)) > max_unit_rank) {
                    max_unit_id = punit_cur->first;
                    max_unit = tmp_unit;
                    max_unit_rank = tmp_unit_rank;
                }
                timer -= ranking->cost(); /*XXX*/
            }
        } else {
            /* cache usable, just check all dirty units against the cached max */
            for (punit_cur = pdunit_set->begin(), punit_max = pdunit_set->end(); punit_cur != punit_max; punit_cur++) {
                if ((tmp_unit_rank = ranking->invoke(tmp_unit = punit_cur->second)) > max_unit_rank) {
                    max_unit_id = punit_cur->first;
                    max_unit = tmp_unit;
                    max_unit_rank = tmp_unit_rank;
                }
                timer -= ranking->cost(); /*XXX*/
            }
        }
        caller.retCurNode(this, NULL, NULL, NULL, timer);
        /* TODO: set target unit and invoke interrupt timer block if necessary */
        return true;
    }
}

