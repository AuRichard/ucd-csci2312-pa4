#include <iostream>
#include <iomanip>
#include "Agent.h"
#include "Strategic.h"

namespace Gaming{

    const char Strategic::STRATEGIC_ID = 'T';
    
    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) // didn't use Strategy s
            : Agent(g, p, energy) { __strategy = nullptr; }

    Strategic::~Strategic() { delete __strategy; }

    void Strategic::print(std::ostream &os) const {
        os << STRATEGIC_ID << std::left << __id;
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const { return (*__strategy)(s); }

}