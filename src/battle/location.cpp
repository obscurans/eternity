/* Copyright (c) 2010 Andrew Crowell and Jeffrey Tsang, all rights reserved.    *
 * See /doc/license.txt for details on how this source can be licensed for use. */

#include "eternity.hpp"
#include "location.hpp"

namespace Eternity {
/* Location class methods */
    Location::Location(int d_x, int d_y, int d_height, int d_map) {
        x = d_x;
        y = d_y;
        height = d_height;
        map = d_map;
    }

    int Location::getX() const {
        return x;
    }

    int Location::getY() const {
        return y;
    }

    int Location::getHeight() const {
        return height;
    }

    int Location::getMap() const {
        return map;
    }

    bool Location::stepX(bool forward) {
        if (forward) {
            x++;
        } else {
            x--;
        }
        return true;
    }

    bool Location::stepY(bool forward) {
        if (forward) {
            y++;
        } else {
            y--;
        }
        return true;
    }

    bool Location::setX(int new_x) {
        x = new_x;
        return true;
    }

    bool Location::setY(int new_y) {
        y = new_y;
        return true;
    }

    bool Location::setHeight(int new_height) {
        height = new_height;
        return true;
    }

    bool Location::setMap(int new_map) {
        map = new_map;
        return true;
    }

    int Location::lineDistanceTo(Location dest) const {
/* TODO */
    }
}

