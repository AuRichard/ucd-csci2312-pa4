#include "Game.h"
#include "Piece.h"
#include "Resource.h"
#include "Agent.h"
#include "Advantage.h"
#include <iomanip>

using namespace std;

namespace Gaming {
    
    const char  Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity)
            : Resource (g, p, capacity) { __capacity = capacity * ADVANTAGE_MULT_FACTOR; }

    Advantage::~Advantage() {
        // Not sure what to put here, again.
    }

    void Advantage::print(ostream &os) const {
        os << ADVANTAGE_ID << left << __id;
    }

    double Advantage::getCapacity() const { return __capacity; }

    double Advantage::consume() {
        __capacity = -1;
        finish();
        return __capacity;

    }
}
