#include "Player.h"

#include <iostream>
#include "Gameplay.h"
#include "Card.h"
using namespace std;

// Constructor 
Player::Player(Gameplay* gameplay, int id) :
    mGameplay(gameplay),
    mScore(0),
    mID(id)
    {}

// Destructor
Player::~Player() {
    mGameplay = NULL;
}

// give cards to respecting players
void Player::ReceiveCards(vector<Card*> cardsArray) {
    mHand = cardsArray;
}

// Returns the current score
int Player::GetScore() const {
    return mScore;
}

int Player::GetID() const {
    return mID;
}

bool Player::PlayerHas(Card* card) const {
    for (int i = 0; i < 13; i++) {
        if (mHand[i]) {
            if (*mHand[i] == *card) {
                return true;
            }
        }
    }
    return false;
}

void Player::PrintDiscard() {
    int newScore = 0;
    cout << "Player " << mID << "'s discards:";

    // Replicating silly behaviour of their program.
    if (mDiscard.empty()) {
        cout << " ";
    }
    
    for (vector<Card*>::iterator it = mDiscard.begin(); it != mDiscard.end(); it++) {
        newScore += (int)((*it)->getRank()) + 1;
        cout << " " << (**it);
    }
    cout << endl;
    cout << "Player " << mID << "'s score: ";
    cout << mScore << " + " << newScore;
    cout << " = " << mScore + newScore << endl;
    mScore += newScore;
    mDiscard.clear();
}

void Player::RemoveFromHand(Card* card) {
    for (int i = 0; i < 13; i++) {
        if (mHand[i] && *mHand[i] == *card) {
            mHand[i] = NULL;
            return;
        }
    }
    cerr << "The card is not in your hand."<< endl;
}

void Player::PlayCardInHand(Card* card){
    cout << "Player " << mID << " plays " << *(card) << "." << endl;
    mGameplay->AddCardToTable(card);
    RemoveFromHand(card);
}
