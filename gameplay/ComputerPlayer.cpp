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
bool ComputerPlayer::TakeTurn() {
    // See if we have any legal plays first, if not, discard a card. If we have no cards to discard, fail.
    vector<Card*> legalPlays = GetLegalPlays();
    if (legalPlays.empty()) {
        // No legal plays, discard first available card.
        vector<Card*> hand = mGameState->GetHand(GetID());
        for (int i = 0; i < 13; i++) {
            if (hand[i]) {
                cout << "Player " << GetID() << " discards " << *(hand[i]) << "." << endl;
                mGameState->DiscardCard(GetID(), hand[i]);
                // Able to discard a card - the round may continue.
                return true;
            }
        }
        cerr << "No legal plays and no cards to discard for player " << GetID() << endl;
        // No cards left -  indicate that the round is over.
        return false;
    }
    // Play a card by updating the state.
    cout << "Computer " << GetID() << " has " << legalPlays.size() << " plays " << endl;
    mGameState->PlayCard(GetID(), legalPlays[0]);
    // We were able to play a card - the round may continue.
    return true;
}

bool ComputerPlayer::IsHuman() const {
    return false;
}
