#include "Game.h"
#include "Piece.h"
#include "Resource.h"
#include "Agent.h"
#include "Food.h"
#include <iomanip>

using namespace std;

namespace Gaming {

    // Brought to you by the letter:
    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity)
    : Resource(g, p, capacity) { __capacity = capacity; }

    Food::~Food(){
        // Not sure what to put here. Who would want to delete food anyways.
    }

    void Food::print(ostream &os) const {
        os << FOOD_ID << left << __id;
    }
}