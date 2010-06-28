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
/* base class for unit decision-tree nodes */
    class Node {
    protected:
        bool satisfied;                     /* whether the conditions are currently satisfied */
        bool modified;                      /* whether this node has been modified this tick */
        Node* last_filter;                  /* the last filtering node passed through this path */
    public:
        virtual bool evaluate(Unit&, Node*, const map<int,Unit*>*, const set<int>*) = 0;
    };

/* class for unit decision-tree normal internal nodes */
    class Node_Internal:public Node {
    private:
        Node* f_branch;                     /* the node to test next on condition true */
        Node* t_branch;                     /* the node to test next on condition false */
        Predicate* test;                    /* the boolean logic statement to test */
        const map<int,Unit*>* unit_set_b;   /* the set of units filtered through to this node */
        const set<int>* dunit_set_b;        /* the set of dirty units filtered through to this node */
    public:
        Node* getFBranch() const;
        Node* getTBranch() const;
        Predicate* getTest() const;

        bool setFBranch(const Node*);
        bool setTBranch(const Node*);
        bool setTest(const Predicate*);

        bool evaluate(Unit&, Node*, const map<int,Unit*>*, const set<int>*);
    };

/* class for unit decision-tree filtering internal nodes */
    class Node_Filter:public Node {
    private:
        Node* f_branch;                     /* the node to test next on unit-set nonempty */
        Node* t_branch;                     /* the node to test next on unit-set empty */
        Filter* test;                       /* the boolean logic filter to use */
        map<int,Unit*> unit_set;            /* the set of units filtered past this node */
        set<int> dunit_set;                 /* the set of dirty units filtered past this node */
//        bool dirty;                         /* whether the variables named in the filter have changed */
    public:
        Node* getFBranch() const;
        Node* getTBranch() const;
        Filter* getTest() const;

        bool setFBranch(const Node*);
        bool setTBranch(const Node*);
        bool setTest(const Filter*);

        bool evaluate(Unit&, Node*, const map<int,Unit*>*, const set<int>*);
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

        bool evaluate(Unit&, Node*, const map<int,Unit*>*, const set<int>*);
    };

/* class for unit decision-tree sorting leaves */
    class Node_Sorter:public Node {
    private:
        Block* instruction;                 /* the instruction to execute from this node */
        Block_Timer* interrupt;             /* the function to calculate interrupt waiting time */
        Comparer* ordering;                 /* the ordering function to pick a unit to target */
        const map<int,Unit*>* unit_set_b;   /* the set of units filtered through to pick from */
//        bool dirty;                         /* whether the variables named in the ordering have changed */
    public:
        Block* getInstruction() const;
        Block_Timer* getInterrupt() const;
        Comparer* getOrdering() const;

        bool setInstruction(Block*);
        bool setInterrupt(Block_Timer*);
        bool setOrdering(Comparer*);

        bool evaluate(Unit&, Node*, const map<int,Unit*>*, const set<int>*);
    };
}

#endif /*NODE_H*/

