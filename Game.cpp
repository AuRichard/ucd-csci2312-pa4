#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <set>
#include "Game.h"
#include "Piece.h"
#include "Resource.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"

using namespace std;

namespace Gaming {

    char mander = 'A';
    char meleon = 'X';
    char izard = 'B';

    // Constants as describe in the Detailed Instruction (IV)
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;
    
    PositionRandomizer Game::__posRandomizer = PositionRandomizer();

    // Default Constructor:
    Game::Game() {
        __numInitAgents = 0;
        __numInitResources = 0;
        __width = MIN_WIDTH;
        __height = MIN_HEIGHT;

        for (int i=0; i < (__width*__height); i++)
            __grid.push_back(nullptr);

        __round = 0;
        __status = NOT_STARTED;
        __verbose = false;
    }

    // Constructor:
    Game::Game(unsigned width, unsigned height, bool manual) : __width(width), __height(height) {
        if (width < MIN_HEIGHT || height < MIN_HEIGHT)
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);

        __numInitAgents = 0;
        __numInitResources = 0;

        for (int i=0; i < (__width * __height); i++)
            __grid.push_back(nullptr);

        if (!manual)
            populate();

        __round = 0;
        __status = NOT_STARTED;
        __verbose = false;

    }

    // Destructor:
    Game::~Game() { }

    void Game::populate(){
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;

        unsigned int numAdvantages = __numInitResources / 2;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents / 2;
        unsigned int numFoods = __numInitResources - numAdvantages;

        // Taken from section 6.5 of the default README file:
        default_random_engine gen;
        uniform_int_distribution<int> d(0, __width * __height);

        // populate Strategic agents:
        while (numStrategic > 0) {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }

        // populate Simple agents:
        while (numSimple > 0) {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }


        // populate Advantage:
        while (numAdvantages > 0) {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }

        // populate food:
        while (numFoods > 0) {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }
    }

    unsigned int Game::getNumPieces() const { return getNumAgents() + getNumResources(); }

    unsigned int Game::getNumAgents() const
    { return getNumSimple() + getNumStrategic(); }

    unsigned int Game::getNumSimple() const {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it){
            Simple *simple = dynamic_cast<Simple*>(*it);
            if (simple) numAgents++;
        }
        return numAgents;
    }

    unsigned int Game::getNumStrategic() const {
        unsigned int numStrat = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Strategic *strategic = dynamic_cast<Strategic*>(*it);
            if (strategic) numStrat++;
        }
        return numStrat;

    }

    unsigned int Game::getNumResources() const {

        unsigned int numResour = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Resource *resource = dynamic_cast<Resource*>(*it);
            if (resource) numResour++;
        }
        return numResour;
    }

    const Piece *  Game::getPiece(unsigned int x, unsigned int y) const {
        unsigned int pos = (x *__width) + y;
        if (__grid[pos] == nullptr)
            throw PositionEmptyEx(x, y);
        return __grid[pos];
    }

    // grid population methods
    void Game::addSimple(const Position &position) {
        addSimple(position, STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(const Position &position, double energy){
        Simple *sim = new Simple(*this,position,energy);

        if((position.x*__width + position.y)>__grid.size())
            throw OutOfBoundsEx(__width,__height,position.x,position.y);

        if((__grid[position.x*__width + position.y])!=nullptr)
            throw PositionNonemptyEx(position.x,position.y);

        __grid[position.x*__width + position.y] = sim;
    }

    void Game::addSimple(unsigned x, unsigned y) {
        Position pos(x,y);
        this->addSimple(pos);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy) {
        Position pos(x,y);
        this->addSimple(pos,energy);
    }

    void Game::addStrategic(const Position &position, Strategy *s) {
        Strategic *strat = new Strategic(*this,position,STARTING_RESOURCE_CAPACITY,s);

        if((position.x*__width + position.y)>__grid.size())
            throw OutOfBoundsEx(__width,__height,position.x,position.y);

        if((__grid[position.x*__width + position.y])!=nullptr)
            throw PositionNonemptyEx(position.x,position.y);

        __grid[position.x*__width + position.y] = strat;
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        Position pos(x,y);
        this->addStrategic(pos,s);
    }

    void Game::addFood(const Position &position)
    {
        Food *foo = new Food(*this,position,STARTING_RESOURCE_CAPACITY);    // pun not intended

        if((position.x*__width + position.y)>__grid.size())
            throw OutOfBoundsEx(__width,__height,position.x,position.y);

        if((__grid[position.x*__width + position.y])!=nullptr)
            throw PositionNonemptyEx(position.x,position.y);

        __grid[position.x*__width + position.y] = foo;
    }

    void Game::addFood(unsigned x, unsigned y) {
        Position pos(x,y);
        this->addFood(pos);
    }

    void Game::addAdvantage(const Position &position) {
        Advantage *advan = new Advantage(*this,position,STARTING_RESOURCE_CAPACITY);

        if((position.x*__width + position.y)>__grid.size())
            throw OutOfBoundsEx(__width,__height,position.x,position.y);

        if((__grid[position.x*__width + position.y])!=nullptr)
            throw PositionNonemptyEx(position.x,position.y);

        __grid[position.x*__width + position.y] = advan;
    }

    void Game::addAdvantage(unsigned x, unsigned y) {
        Position pos(x,y);
        this->addAdvantage(pos);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const {

        Surroundings surro;
        for (int i = 0; i < 9; ++i) {
            surro.array[i] = EMPTY;
        }
        for (int row = -1; row <= 1; ++row) {
            for (int col = -1; col <= 1; ++col) {
                if (pos.x + row >= 0 && pos.x + row < __height
                    && pos.y + col >= 0 && pos.y + col < __width) {
                    unsigned int index = pos.y + col + ((pos.x + row) * __width);
                    if (__grid[index])
                        surro.array[col + 1 + ((row + 1) * 3)] = __grid[index]->getType();
                }
                else {
                    surro.array[col + 1 + ((row + 1) * 3)] = INACCESSIBLE;
                }
            }
        }
        surro.array[4] = SELF;

        return surro;
    }

    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {

        int xDiff = to.x - from.x + 1;
        int yDiff = to.y - from.y + 1;
        unsigned int index = (yDiff + (xDiff * 3));
        switch (index) {
            case 0:
                return NW;
            case 1:
                return N;
            case 2:
                return NE;
            case 3:
                return W;
            case 4:
                return STAY;
            case 5:
                return E;
            case 6:
                return SW;
            case 7:
                return S;
            case 8:
                return SE;
            default:
                return STAY;
        }

    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
        Surroundings ss = getSurroundings(pos);
        ActionType direction [9] =  {NW,N,NE,W,STAY,E,SW,S,SE};
        int directionInt;
        bool duhTruth;
        for (int i = 0; i < 9; ++i) {
            if(direction[i]== ac) {
                directionInt = i;
                break;
            }
        }
        duhTruth = ss.array[directionInt] != INACCESSIBLE;

        if (izard == 'B') {
            return duhTruth;
        }
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const {
       if (isLegal(ac, pos)) {
            int x, y;
            x = pos.x;
            y = pos.y;
            switch (ac) {
                case E: 
                    y++; 
                    break;
                case NE: 
                    y++; 
                    x--; 
                    break;
                case N: 
                    x--; 
                    break;
                case NW: 
                    y--; 
                    x--; 
                    break;
                case W: 
                    y--; 
                    break;
                case SW: 
                    y--; 
                    x++; 
                    break;
                case S: 
                    x++; 
                    break;
                case SE: 
                    x++; 
                    y++; 
                    break;
                default: 
                    break;
            }
            Position p((unsigned )x, (unsigned)y);
            return p;
        }
        return pos;
    }

    void Game::round(){
        set<Piece*> pieces;
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            if (*it) {
                pieces.insert(pieces.end(), *it);
                (*it)->setTurned(false);
            }
        }
        
    for (auto it = pieces.begin(); it != pieces.end(); ++it) {
            if (!(*it)->getTurned()) {
                (*it)->setTurned(true);
                (*it)->age();
                ActionType ac = (*it)->takeTurn(getSurroundings((*it)->getPosition()));
                Position pos0 = (*it)->getPosition();
                Position pos1 = move(pos0, ac);
                if (pos0.x != pos1.x || pos0.y != pos1.y) {
                    Piece *p = __grid[pos1.y + (pos1.x * __width)];
                    if (p) {
                        (*(*it)) * (*p);
                        if ((*it)->getPosition().x != pos0.x || (*it)->getPosition().y != pos0.y) {
                            __grid[pos1.y + (pos1.x * __width)] = (*it);
                            __grid[pos0.y + (pos0.x * __width)] = p;
                        }
                    } else {
                        (*it)->setPosition(pos1);
                        __grid[pos1.y + (pos1.x * __width)] = (*it);
                        __grid[pos0.y + (pos0.x * __width)] = nullptr;
                    }
                }
            }
        }        
        
    for (unsigned int i = 0; i < __grid.size(); ++i) {
        if (__grid[i] && !(__grid[i]->isViable())) {
            delete __grid[i];
            __grid[i] = nullptr;
        }
    }
    
    if (getNumResources() <= 0) {
        __status = Status::OVER;
        }
        
        __round++;

    }
    
    void Game::play(bool verbose) {
        __verbose = verbose;
        __status = PLAYING;
        cout << *this;
        while (__status != OVER) {
            round();
            if (verbose) cout << *this;
        }
        if (!verbose) cout << *this;
    }

    ostream &operator<<(ostream &os, const Game &game) {
      os << "Round " << game.__round << endl;
        int column = 0;
        for (auto it = game.__grid.begin(); it != game.__grid.end(); ++it) {
            if (*it == nullptr) {
                os << "[" << setw(6) << "]";
            } else {
                stringstream ss;
                ss << "[" << **it;
                string str;
                getline(ss, str);
                os << str << "]";
            }
            if (++column == game.__width) {
                column = 0;
                os << endl;
            }
        }
        os << "Status: ";
        switch (game.getStatus()) {
            case Game::Status::NOT_STARTED:
                cout << "Not Started..." << endl; break;
            case Game::Status::PLAYING:
                cout << "Playing..." << endl; break;
            default:
                cout << "Over!" << endl; break;
        }
        return os;
    }

}

