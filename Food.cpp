#include "Game.h"
#include "Piece.h"
#include "Resource.h"
#include "Agent.h"
#include "Food.h"
#include <iomanip>
#include <sstream>

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
        string s;
        s = to_string(__id);
        stringstream sstream;
        sstream << Food::FOOD_ID;
        sstream << s;
        getline(sstream, s);
        for (int i = 0; i < s.length(); ++i) {
            os << s[i];
        }
    }
}