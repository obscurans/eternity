/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#pragma once
#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <map>
using std::string;
using std::map;

namespace Eternity {
/* base class for unit decision-tree nodes */
    class Node {
    protected:
        bool satisfied;                     /* whether the conditions are currently satisfied */
        bool modified;                      /* whether this node has been modified this tick */
        Node* last_filter;                  /* the last filtering node passed through this path */
    public:
        virtual Node* evaluate(Unit&, Node*, const map<int,Unit*>*, const map<int,Unit*>*, int) = 0;
    };

/* class for unit decision-tree normal internal nodes */
    class Node_Internal:public Node {
    private:
        Node* f_branch;                     /* the node to test next on condition true */
        Node* t_branch;                     /* the node to test next on condition false */
        Predicate* test;                    /* the boolean logic statement to test */
        const map<int,Unit*>* unit_set_b;   /* the set of units filtered through to this node */
        const map<int,Unit*>* dunit_set_b;  /* the set of dirty units filtered through to this node */
    public:
        Node* getFBranch() const;
        Node* getTBranch() const;
        Predicate* getTest() const;

        bool setFBranch(const Node*);
        bool setTBranch(const Node*);
        bool setTest(const Predicate*);

        bool evaluate(Unit&, Node*, const map<int,Unit*>*, const map<int,Unit*>*, int);
    };

/* class for unit decision-tree filtering internal nodes */
    class Node_Filter:public Node {
    private:
        Node* f_branch;                     /* the node to test next on unit-set nonempty */
        Node* t_branch;                     /* the node to test next on unit-set empty */
        Predicate_Filter* test;             /* the boolean logic filter to use */
        map<int,Unit*> unit_set;            /* the set of units filtered past this node */
        map<int,Unit*> dunit_set;           /* the set of dirty units filtered past this node */
//        bool dirty;                         /* whether the variables named in the filter have changed */
    public:
        Node* getFBranch() const;
        Node* getTBranch() const;
        Predicate_Filter* getTest() const;

        bool setFBranch(const Node*);
        bool setTBranch(const Node*);
        bool setTest(const Predicate_Filter*);

        bool evaluate(Unit&, Node*, const map<int,Unit*>*, const map<int,Unit*>*, int);
    };

/* class for unit decision-tree normal leaves */
    class Node_Terminal:public Node {
    private:
        Block* instruction;                 /* the instruction to execute from this node */
        Block_Timer* interrupt;             /* the function to calculate interrupt waiting time */
    public:
        Block* getInstruction() const;
        Block_Timer* getInterrupt() const;

        bool setInstruction(Block*);
        bool setInterrupt(Block_Timer*);

        bool evaluate(Unit&, Node*, const map<int,Unit*>*, const map<int,Unit*>*, int);
    };

/* class for unit decision-tree sorting leaves */
    class Node_Sorter:public Node {
    private:
        Block* instruction;                 /* the instruction to execute from this node */
        Block_Timer* interrupt;             /* the function to calculate interrupt waiting time */
        Block_Comparer* ranking;            /* the ranking function to pick a unit to target */
        const map<int,Unit*>* unit_set_b;   /* the set of units filtered through to pick from */
        int max_unit_id;                    /* the cached maximal unit ID from filtered units */
        Unit* max_unit;                     /* the cached maximal unit from filtered units */
        double max_unit_rank;               /* the cached functional rank for the maximal unit */
//        bool dirty;                         /* whether the variables named in the ordering have changed */
    public:
        Block* getInstruction() const;
        Block_Timer* getInterrupt() const;
        Block_Comparer* getRanking() const;

        bool setInstruction(Block*);
        bool setInterrupt(Block_Timer*);
        bool setRanking(Block_Comparer*);

        bool evaluate(Unit&, Node*, const map<int,Unit*>*, const map<int,Unit*>*, int);
    };
}

#endif /*NODE_H*/

