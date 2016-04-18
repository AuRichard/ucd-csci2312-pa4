#include <iostream>
#include <iomanip>
#include "Agent.h"
#include "Strategic.h"

using namespace std;

namespace Gaming{

    const char Strategic::STRATEGIC_ID = 'T';
    
    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s)
            : Agent(g, p, energy) { __strategy = s; }

    Strategic::~Strategic() { delete __strategy; }

    void Strategic::print(ostream &os) const {
        os << STRATEGIC_ID << left << __id;
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const { return (*__strategy)(s); }

}