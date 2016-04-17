#include "Game.h"
#include "AggressiveAgentStrategy.h"

using namespace std;

namespace Gaming {

    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
        __agentEnergy = agentEnergy;
    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() { }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        ActionType ac;
        vector<int> pos;

        default_random_engine gen;

        if(__agentEnergy > DEFAULT_AGGRESSION_THRESHOLD){
            for (int i = 0; i < s.array.size(); i++) {
                if (s.array[i] == SIMPLE || s.array[i] == STRATEGIC) {
                    pos.push_back(i);
                }
            }
        }

        if (pos.size() == 0) {
            for (int i = 0; i < s.array.size(); i++) {
                if (s.array[i] == ADVANTAGE) {
                    pos.push_back(i);
                }
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

        if (pos.size() > 0) {
            uniform_int_distribution<> dis(0, (int) (pos.size()-1));
            int index = dis(gen);


            if (pos.size() == 1) {
                index = pos[0];
            }

            switch (index) {
                case 1 :
                    ac = N;
                    break;
                case 2 :
                    ac = NE;
                    break;
                case 5 :
                    ac = E;
                    break;
                case 8 :
                    ac = SE;
                    break;
                case 7 :
                    ac = S;
                    break;
                case 6 :
                    ac = SW;
                    break;
                case 3 :
                    ac = W;
                    break;
                case 0 :
                    ac = NW;
                    break;
                case 4 :
                    ac = STAY;
                    break;
                default :
                    ac = STAY;
            }
            return ac;

        }
        return STAY;
    }
}
