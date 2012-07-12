#include "GamePlay.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include "Card.h"
#include <iostream>
#include <cassert>
#include <unistd.h>

using namespace std;

// Copy Constructor
ComputerPlayer::ComputerPlayer(Player* human) : Player(human->mGamePlay, human->mGameState, human->mView, human->mID) {
    mID = human->GetID();
}

// Prompt command from AI
void ComputerPlayer::TakeTurn() {
    vector<Card*> legalPlays = GetLegalPlays();
    if (legalPlays.empty()) {
        // No legal plays, discard first available card.
        vector<Card*> hand = mGameState->GetHand(GetID());
        for (int i = 0; i < 13; i++) {
            if (hand[i]) {
                cout << "Player " << GetID() << " discards " << *(hand[i]) << "." << endl;
                mGameState->DiscardCard(GetID(), hand[i]);
                return;
            }
        }
        cerr << "No legal plays and no cards to discard for player " << GetID() << endl;
        assert(false);
    }
    mGameState->PlayCard(GetID(), legalPlays[0]);
}

bool ComputerPlayer::IsHuman() const {
    return false;
}
