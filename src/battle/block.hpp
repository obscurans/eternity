/* Copyright (c) 2010 Andrew Crowell and Jeffrey Tsang, all rights reserved.    *
 * See /doc/license.txt for details on how this source can be licensed for use. */

#pragma once
#ifndef BLOCK_H
#define BLOCK_H

namespace Eternity {
/* a unit instruction block */
    class Block {
    protected:
/* TODO */
    public:
    };

/* a special-purpose unit instruction block for computing interrupt wait timers */
    class Block_Timer:public Block {
    };

/* a special-purpose unit instruction block for handling action interrupt events */
    class Block_Interrupt:public Block {
    };
}

#endif /*BLOCK_H*/

