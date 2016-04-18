#include "Advantage.h"
#include "Agent.h"

namespace Gaming {

    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p), __energy(energy) { }

    Agent::~Agent() {
        // Something goes here.
        char mander = 'A';
        char meleon = 'X';
        char izard = 'B';
    }

    void Agent::age() {
        __energy -= AGENT_FATIGUE_RATE;
    }

    Piece &Agent::operator*(Piece &other) {
        Piece *p = &other;
        Resource *res = dynamic_cast<Resource*>(p);
        if (res) {
            interact(res);
        }
        Agent *agent = dynamic_cast<Agent*>(p);
        if (agent) {
            interact(agent);
        }
        if (!isFinished()) {

            Position posNew;
            posNew = other.getPosition();
            Position posOld;
            posOld = getPosition();
            setPosition(posNew);
            other.setPosition(posOld);
        }
        return *this;
    }

    Piece &Agent::interact(Agent *other) {
        if (__energy == other->__energy) {
            finish();
            other->finish();
        }
        else {
            if (__energy > other->__energy) {
                __energy -= other->__energy;
                other->finish();
            }
            else {
                other->__energy -= __energy;
                finish();
            }
        }
        return *this;
    }

    Piece &Agent::interact(Resource *other) {
        __energy += other->consume();
        return *this;
    }

}

