/* Copyright (c) 2010 Andrew Crowell and Jeffrey Tsang, all rights reserved.    *
 * See /doc/license.txt for details on how this source can be licensed for use. */

#pragma once
#ifndef LOCATION_H
#define LOCATION_H

namespace Eternity {
/* a unit map location wrapper */
    class Location {
    private:
        int x;
        int y;
        int height;
        int map;
    public:
        Location(int, int, int, int);

        int getX() const;
        int getY() const;
        int getHeight() const;
        int getMap() const;

        bool stepX(bool);
        bool stepY(bool);

        bool setX(int);
        bool setY(int);
        bool setHeight(int);
        bool setMap(int);

        int lineDistanceTo(Location) const;
    };
}

#endif /*LOCATION_H*/

