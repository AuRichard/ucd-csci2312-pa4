#include "Game.h"

using namespace std;

namespace Gaming {

    DefaultAgentStrategy::DefaultAgentStrategy() { }

    DefaultAgentStrategy::~DefaultAgentStrategy() { }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
        ActionType action;
        vector<int> pos;
        default_random_engine gen;

        for (int i = 0; i < s.array.size(); i++) {
            if (s.array[i] == ADVANTAGE) {
                pos.push_back(i);
            }
        }

        if (pos.size() == 0) {
            for (int i = 0; i < s.array.size(); i++) {
                if (s.array[i] == FOOD) {
                    pos.push_back(i);
                }
            }
        }

        if (pos.size() == 0) {
            for (int i = 0; i < s.array.size(); i++) {
                if (s.array[i] == EMPTY) {
                    pos.push_back(i);
                }
            }
        }

        if (pos.size() == 0) {
            for (int i = 0; i < s.array.size(); i++) {
                if (s.array[i] == SIMPLE) {
                    pos.push_back(i);
                }
            }
        }

        if (pos.size() > 0) {
            uniform_int_distribution<> dis(0, (int) (pos.size()-1));
            int index = dis(gen);


            if (pos.size() == 1) {
                index = pos[0];
            }

            switch (index) {
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