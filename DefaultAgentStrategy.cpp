#include <random>
#include "DefaultAgentStrategy.h"

using namespace std;

namespace Gaming {

    DefaultAgentStrategy::DefaultAgentStrategy() { }

    DefaultAgentStrategy::~DefaultAgentStrategy() { }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
        vector<int> positions;
        default_random_engine gen;

        
        for (int i = 0; i < 9; ++i) {
            if (s.array[i] == PieceType::ADVANTAGE) {
                positions.push_back(i);
            }
        }

        if (positions.size() == 0) {
            for (int i = 0; i < 9; ++i) {
                if (s.array[i] == PieceType::FOOD) {
                    positions.push_back(i);
                }
            }
        }
        
        if (positions.size() == 0) {
            for (int i = 0; i < 9; ++i) {
                if (s.array[i] == PieceType::EMPTY) {
                    positions.push_back(i);
                }
            }
        }
        
        if (positions.size() == 0) {
            for (int i = 0; i < 9; ++i) {
                if (s.array[i] == PieceType::SIMPLE) {
                    positions.push_back(i);
                }
            }
        }

        if (positions.size() > 0) {
            int index = positions[gen() % positions.size()];
            if (positions.size() == 1) index = positions[0];
            ActionType action;
            switch (index) {
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