#include "Piece.h"
#include "Resource.h"
#include "Game.h"

namespace Gaming {
    
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece (g, p) { __capacity = capacity; }

    Resource::~Resource() { }

    double Resource::consume() {
        __capacity = 0.00;
        return __capacity;
    }

    void Resource::age() {
        __capacity /= RESOURCE_SPOIL_FACTOR;
        if (__capacity < 0.001)
            __capacity = 0;
    }

    ActionType Resource::takeTurn(const Surroundings &s) const { return Gaming::STAY; }


    Piece & Resource::operator*(Piece &other) { return other.interact(this); }

    Piece & Resource::interact(Agent *) { return *this; }

    Piece & Resource::interact(Resource *) { return *this; }
}
