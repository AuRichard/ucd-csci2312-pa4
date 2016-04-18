#include "Simple.h"
#include <iomanip>

using namespace std;

namespace Gaming {

    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy) { }

    Simple::~Simple() { }

    void Simple::print(ostream &os) const {
        os << SIMPLE_ID << left << __id;
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {

        ActionType action;

        vector<int> pos;
        default_random_engine gen;

        for (int i = 0; i < 9; ++i) {
            if (s.array[i] == PieceType::ADVANTAGE || s.array[i] == PieceType::FOOD) {
                pos.push_back(i);

            }
        }

        if (pos.size() == 0) {
            for (int i = 0; i < 9; ++i) {
                if (s.array[i] == PieceType::EMPTY) {
                    pos.push_back(i);

                }
            }
        }

        if (pos.size() > 0) {
            int i = pos[gen() % pos.size()];
            if (pos.size() == 1) i = pos[0];

            switch (i) {
                case 0:
                    action = NW;
                    break;
                case 1:
                    action = N;
                    break;
                case 2:
                    action = NE;
                    break;
                case 3:
                    action = W;
                    break;
                case 4:
                    action = STAY;
                    break;
                case 5:
                    action = E;
                    break;
                case 6:
                    action = SW;
                    break;
                case 7:
                    action = S;
                    break;
                case 8:
                    action = SE;
                    break;
                default:
                    action = STAY;
            }
            return (action);
        }

        return ActionType::STAY;
    }
}

// not exactly "simple"