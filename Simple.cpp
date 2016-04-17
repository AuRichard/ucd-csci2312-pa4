#include "Agent.h"
#include "Simple.h"
#include <iomanip>

using namespace std;

namespace Gaming {

    const char Simple::SIMPLE_ID = 'S';
    Simple::Simple(const Game &g, const Position &p, double energy)
            : Agent(g, p, energy) { }

    Simple::~Simple() { }

    void Simple::print(ostream &os) const {
        os << SIMPLE_ID << left << __id;
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {

        ActionType action;
        vector<int> pos;

        random_device rd;
        mt19937 gen(rd());

        for (int i = 0; i < s.array.size(); i++) {
            if (s.array[i] == ADVANTAGE || s.array[i] == FOOD) {
                pos.push_back(i);
            }
        }

        if (pos.size() == 0) {
            for (int i = 0; i < s.array.size(); i++) {
                if (s.array[i] == EMPTY) {
                    pos.push_back(i);
                }
            }
        }

        if (pos.size() > 0) {
            uniform_int_distribution<> distribution(0, (int) (pos.size() - 1));
            int i = distribution(gen);


            if (pos.size() == 1) {
                i = pos[0];
            }

            switch (i) {
                case 1 :
                    action = N;
                    break;
                case 2 :
                    action = NE;
                    break;
                case 5 :
                    action = E;
                    break;
                case 8 :
                    action = SE;
                    break;
                case 7 :
                    action = S;
                    break;
                case 6 :
                    action = SW;
                    break;
                case 3 :
                    action = W;
                    break;
                case 0 :
                    action = NW;
                    break;
                case 4 :
                    action = STAY;
                    break;
                default :
                    action = STAY;
            }
            return action;

        }

        return STAY;
    }
}