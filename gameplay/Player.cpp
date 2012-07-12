#include "Player.h"

#include <iostream>
#include "GamePlay.h"
#include "GameState.h"
#include "Card.h"
using namespace std;

// Constructor 
Player::Player(GamePlay* gameplay, GameState* gamestate, int id) :
    mGamePlay(gameplay),
    mGameState(gamestate),
    mID(id)
    {}

Player::~Player(){}

int Player::GetID() const {
    return mID;
}

void Player::ClearDiscard() {
    int newScore = 0;

    const vector<Card*> discards = mGameState->GetDiscards(GetID());
    for (vector<Card*>::const_iterator it = discards.begin(); it != discards.end(); it++) {
        newScore += (int)((*it)->getRank()) + 1;
    }
    newScore += mGameState->GetScore(GetID());
    mGameState->UpdateScore(GetID(), newScore);
    mGameState->ClearDiscard(GetID());
}

vector<Card*> Player::GetLegalPlays() {
    vector<Card*> hand = mGameState->GetHand(GetID());
    vector<Card*> plays;
    for (int i = 0; i < 13; i++) {
        if (hand[i] && mGameState->IsLegal(hand[i])) {
            if (hand[i]->getSuit() == SPADE && hand[i]->getRank() == SEVEN) {
                // If the player has the seven of spades, that's their only legal play.
                plays.clear();
                plays.push_back(hand[i]);
                return plays;
            }
            plays.push_back(hand[i]);
        }
    }
    return plays;
}
