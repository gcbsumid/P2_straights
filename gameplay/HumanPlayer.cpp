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
        return false;
    }
    mView->HumanTurn(GetID());
    return true;
}

// Is Human: yes
bool HumanPlayer::IsHuman() const {
    return true;
}
