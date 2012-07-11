#include <string>
#include <iostream>
#include <stdlib.h>

#include "Gameplay.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 2) {
        // Seed the random number generator.
        int seed = atoi(argv[1]);
        srand48(seed);
    }

    Gameplay* gameplay = new Gameplay();
    // Play the game, round by round.
    do {
        gameplay->PlayRound();
    } while (!gameplay->IsGameOver());
    delete gameplay;
    return 0;
}
