#include <string>
#include <iostream>
#include <stdlib.h>

#include "gameplay/GamePlay.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 2) {
        // Seed the random number generator.
        int seed = atoi(argv[1]);
        srand48(seed);
    }

    GamePlay* gameplay = new GamePlay();
    // Play the game, round by round.
    while(gameplay->PlayRound()) {}
    delete gameplay;
    return 0;
}
