/*
    ai.h - Definitions of classes which control strategies used by 
    a Computer to set up their Ships and decide where to fire shots.

    The base class AI makes decisions randomly by default. This is 
    intended to be overridden in derived classes.

    ~To do~
    Add a "Systematic_AI" which fires shots at alternating Squares,
    performing a search on neighbouring Squares when it finds a hit.
*/

#ifndef AI_H
#define AI_H

#include <random>

#include "utils.h"

// ----------------

class AI
{
    public:
        /* Returns an orientation to use when a Ship is put(). */
        virtual char decide_orientation();

        /* Returns a Square to use as the location for a shot or as 
        the origin of a Destination at which a Ship is put(). Doesn't 
        check if the Square on the relevant Board is occupied. */
        virtual Square decide_coords();

        /* Returns a Destination on a Computer's primary Board which is 
        a valid Destination to put() a Ship. */ 
        virtual Destination decide_destination(const Board&, Ship);
};

/* Returns a randomly generated integer in the interval [low, high]. */
int randint(int low, int high);

#endif