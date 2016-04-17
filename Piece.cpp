#include "Game.h"
#include "Piece.h"
#include <iostream>

namespace Gaming {

    unsigned int Piece::__idGen = 0;
    Piece::Piece(const Game &g, const Position &p): __game(g) {
        __position = p;
        __finished = false;
        __turned = false;
        __id = ++__idGen;
    }

    Piece::~Piece() {
        // Tear it down to pieces
    }

    std::ostream &operator<<(std::ostream &os, const Piece &piece) {
        piece.print(os);
        return os;
    }

}