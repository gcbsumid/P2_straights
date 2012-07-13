#include <iostream>
#include "GamePlay.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "Card.h"
#include "../gui/ViewInterface.h"

using namespace std;

// Alert view that we need to take a turn.
bool HumanPlayer::TakeTurn() {
    if (mGameState->CardsInHand(GetID()) == 0) {
        // If we're out of cards, the round is over.
        cout << "It's a human's turn and he doesn't have any cards left. Ending round." << endl;
        return false;
    }
    // Get the view to block and wait for user input.
    mView->HumanTurn(GetID());
    return true;
}

// Is Human: yes
bool HumanPlayer::IsHuman() const {
    return true;
}
