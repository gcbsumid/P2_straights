#include <iostream>
#include "GamePlay.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "Card.h"

using namespace std;

// Alert view that we need to take a turn.
void HumanPlayer::TakeTurn() {
    //mView->HumanTurn(GetID());
}

// Is Human: yes
bool HumanPlayer::IsHuman() const {
    return true;
}

// Player rage quits. Sets boolean to true
void HumanPlayer::RageQuit() {
    mRageQuit = true;
}

// Player rage quits. Sets boolean to true
bool HumanPlayer::IsRageQuitted() const {
    return mRageQuit;
}
