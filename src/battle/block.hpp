/* Copyright (c) 2010-2011 Andrew Crowell and Jeffrey Tsang, all rights reserved. *
 * See /doc/license.txt for details on how this source can be licensed for use.   */

#pragma once
#ifndef BLOCK_H
#define BLOCK_H

namespace Eternity {
/* a unit instruction block */
    class Block {
    protected:
    public:
    };

/* a special-purpose unit instruction block for computing interrupt wait timers */
    class Block_Timer:public Block {
    };

/* a special-purpose unit instruction block for ranking units passed to a sorting node */
    class Block_Ranking: public Block {
    };

/* a special-purpose unit instruction block for handling action interrupt events */
    class Block_Interrupt:public Block {
    };

/* a unit instruction block taking no inargs without output, as entry points for unit execution */
    class Block_Pure:public Block {
    };

/* a unit instruction block taking (only) byval inargs and outputs, for writing function subroutines */
    class Block_Function:public Block {
    };

/* a unit instruction block taking (only) byref inargs without output, for writing subroutines */
    class Block_Procedure:public Block {
    };
}

#endif /*BLOCK_H*/

