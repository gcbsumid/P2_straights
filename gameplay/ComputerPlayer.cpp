#include <iostream>
#include "Gameplay.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include "Card.h"

using namespace std;

// Copy Constructor
ComputerPlayer::ComputerPlayer(Player* human) : Player(human->mGameplay, human->mID) {
    mScore = human->GetScore();
    mID = human->GetID();
    mHand = human->mHand;
    mDiscard = human->mDiscard;
}

// Prompt command from AI
void ComputerPlayer::TakeTurn() {
    // Create a seven of spades card to compare against player's hand.
    Card sevenOfSpades(SPADE,SEVEN);
    for (int i = 0; i < 13; i++) {
        if (this->PlayerHas(&sevenOfSpades)) {
            if (mHand[i] && *mHand[i] == sevenOfSpades) {
                this->PlayCardInHand(mHand[i]);
                return;
             }
        } else if (mHand[i] && mGameplay->IsLegal(mHand[i])) {
            this->PlayCardInHand(mHand[i]);
            return;
        }
    }

    for (int i = 0; i < 13; i++) {
        if (mHand[i]) {
            cout << "Player " << mID << " discards " << *(mHand[i]) << "." << endl;
            mDiscard.push_back(mHand[i]);
            RemoveFromHand(mHand[i]);
            return;
        }
    }
}

bool ComputerPlayer::IsHuman() const {
    return false;
}
