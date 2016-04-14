#include"Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"

namespace Gaming {
    
    // Constants as describe in the Detailed Instruction (IV)
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
	const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
	const unsigned Game::MIN_WIDTH = 3;
	const unsigned Game::MIN_HEIGHT = 3;
	const double Game::STARTING_AGENT_ENERGY = 20;
	const double Game::STARTING_RESOURCE_CAPACITY = 10;
    
}
