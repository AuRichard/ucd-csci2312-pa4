#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"
#include <iomanip>
#include <set>
#include <sstream>

namespace Gaming{
    
    // Constants as describe in the Detailed Instruction (IV)
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
	const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
	const unsigned Game::MIN_WIDTH = 3;
	const unsigned Game::MIN_HEIGHT = 3;
	const double Game::STARTING_AGENT_ENERGY = 20;
	const double Game::STARTING_RESOURCE_CAPACITY = 10;
	
	// Default Constructor:	
	Game::Game(){
		__status = NOT_STARTED;
        __width = MIN_WIDTH;
        __height = MIN_HEIGHT;
        __round = 0;
        populate();
    }
    // Constructor:
    Game::Game(unsigned width, unsigned height, bool manual){
        __status = NOT_STARTED;
        __width = width;
        __height = height;
        
        // If manual is set to true, then populate the game
        if(!manual) {
            populate();
        }
    }
    
    Game::Game(const Game &another){
        __width = another.__width;
        __height = another.__height;
        __status = another.__status;
        __grid = another.__grid;
    }
    
    // Destructor:
    Game::~Game(){}
    
    // Populate:
    void Game::populate(){
        
        // Taken from section 6.5 of the default README file:
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);

        
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;

        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        
        // populate Strategic agents:
        while (numStrategic > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }
        
        // populate Simple agents:
         while (numSimple > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr && i != (__width * __height)) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple--;
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

        // populate advantages:
        while (numAdvantages > 0) {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }

        
        
    }
    
    // dynamic_cast returns a pointer of the argument type
    // or NULL if the derived type of the object is not of
    // the argument type
    unsigned int Game::getNumSimple() const {
    unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Simple *simple = dynamic_cast<Simple*>(*it);
            if (simple) numAgents++;
        }

    return numAgents;
    
    }
    


    
}
