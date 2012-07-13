#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "GamePlay.h"

#include "GameState.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Card.h"
#include "ModelObserver.h"
#include "../gui/ViewInterface.h"

using namespace std;

const int GamePlay::CARD_COUNT = 52; 

// Constructor
GamePlay::GamePlay() :  mView(NULL) {
    // We create the model, must remember to clean this up.
    mState = new GameState(this);
}

GamePlay::~GamePlay() {
    // Clean up model.
    delete mState;
}

void GamePlay::AddView(ViewInterface* v) {
    mView = v;
}

void GamePlay::AddModelObserver(ModelObserver* m) {
    // Pass the observer to the model.
    mState->AddObserver(m);
}

void GamePlay::AddPlayer(bool human) {
    // Alert the model that we need to add a player.
    if (human) {
        mState->AddHumanPlayer(mView);
    } else {
        mState->AddComputerPlayer(mView);
    }
}

void GamePlay::PlayGame() {
    mState->Initialize();
    cout << "WOULD YOU LIEK TO PLAY A GAME?!" << endl;
    // Initializes players.
    for (int i = 0; i < 4; i++) {
        // Ask the view if the player should be a human or computer
        // The view calls GamePlay::AddPlayer, then we call PlayerAdded.
        mView->AddPlayer(i + 1);
    }
    StartRound();
}
void GamePlay::StartRound() {
    // Get the state to shuffle/deal/alert view.
    mState->Shuffle();
    mState->DealCards();
    
    // Start at the player with the 7 of spades.
    mState->ResetNextPlayer(mState->PlayerWithSevenOfSpades());

    cout << "A round has begun" << endl;

    // Start playing.
    ContinueGame();
}

void GamePlay::EndRound() {
    mState->ClearCardsOnTable();
    // Round is over, let's tally scores and see if the game's over.
    // Keep track of the lowest score so we can see who won.
    int winner = -1;
    int minScore = 100000;

    bool endGame = false;

    // mState gives us a handy iteration interface, use that to loop through the players.
    mState->ResetNextPlayer(1);
    for (int i = 0; i < 4; i++) {
        Player* player = mState->NextPlayer();
        player->ClearDiscard();  // Calculate player's final score.
        int score = mState->GetScore(i + 1);

        // See if the game is over.
        if (score > 79) {
            endGame = true;
        }
        
        // Keep track of the player with the lowest score.
        if (score < minScore) {
            minScore = score;
            winner = player->GetID();
        }
    }

    if (endGame) {
        // Game is over, alert view.
        EndGame(winner);
    } else {
        // Game isn't over, start a new round.
        StartRound();
    }
}

void GamePlay::EndGame(int winner) {
    // The game being over represents a change in state.
    // Also, the model can alert the view of this.
    mState->EndGame(winner);
}

void GamePlay::ContinueGame() {
    // Figure out whose turn it is next.
    Player* nextPlayer = mState->NextPlayer(); 
    
    while (true) {
        cout << "It is " << nextPlayer->GetID() << "'s turn to play" << endl;
        // Player takes their turn. A computer plays, a human alerts the view and blocks.
        if (!nextPlayer->TakeTurn()) {
            // No cards left, round over.
            EndRound();
            break;
        }
        
        // Break out of this loop and wait for a human's input.
        if (nextPlayer->IsHuman()) {
            break;
        }

        // A computer just played, run again with the next player's turn.
        nextPlayer = mState->NextPlayer();
    }
}

bool GamePlay::PlayCard(Suit suit, Rank rank) {
    // Only the current player can call this function. This way the view doesn't have to keep track of who played what.
    Player* p = mState->CurrentPlayer();
    cout << "Player " << p->GetID() << " played the " << rank << " of " << suit << endl;
    Card c(suit, rank);

    // The client can discard a card by playing it. DiscardCard returns false if there are legal plays or
    // if the card isn't in the hand, so this is perfectly legal.
    if (DiscardCard(p->GetID(), suit, rank)) {
        return false;
    }

    // The user didn't discard the card. Now, let's see if this is a card that they can legally play.
    bool isLegal = false;
    // Get the legal plays for the player.
    vector<Card*> legalPlays = p->GetLegalPlays();
    for (vector<Card*>::const_iterator i = legalPlays.begin(); i != legalPlays.end(); i++) {
        if ((*i)->getRank() == rank && (*i)->getSuit() == suit) {
            isLegal = true;
            break;
        }
    }
    if (!isLegal) {
        cerr << "Player " << p->GetID() << " tried to play an illegal card " << rank + 1 << " of " << suit + 1 << endl;
        return false;
    }
    Card* cardInHand = mState->CardInHand(p->GetID(), &c);
    assert(cardInHand != NULL);

    mState->PlayCard(p->GetID(), cardInHand);
    ContinueGame();
    return true;
}

bool GamePlay::DiscardCard(int player, Suit suit, Rank rank) {
    Player* p = mState->PlayerWithID(player);
    vector<Card*> legalPlays = p->GetLegalPlays();
    if (!legalPlays.empty()) {
        cerr << "There are legal plays." << endl;
        return false;
    }
    Card c(suit, rank);
    Card* cardInHand = mState->CardInHand(player, &c);
    if (cardInHand == NULL) {
        cout << "Couldn't find card in hand for discarding" << endl;
        return false;
    }
    cout << "Player " << player << " is discarding card " << c << endl;
    mState->DiscardCard(player, cardInHand);
    ContinueGame();
    return true;
}

void GamePlay::RageQuit(int player) {              // Converts indicated player from human to computer.
    Player* p = mState->PlayerWithID(player);
    if (!p->IsHuman()) {
        return;
    }
    HumanPlayer* h = (HumanPlayer*)p;

    // If the current player just rage quit, carry on.
    Player* newPlayer = mState->HumanToComputer(h);
    if (newPlayer == mState->CurrentPlayer()) {
        cout << "New player " << newPlayer->GetID() << " is the current player, so let's keep playing" << endl;
        mState->ResetNextPlayer(newPlayer->GetID());
        ContinueGame();
    }
    cout << "New player " << newPlayer->GetID() << " isn't " << mState->CurrentPlayer()->GetID() << " so let's block" << endl;
}
    
void GamePlay::ResetSeed(int seed) {
    mState->ResetSeed(seed);
    srand48(seed);
}

vector<Card*> GamePlay::GetDiscards(int player) const {
    return mState->GetDiscards(player);
}

vector<Card*> GamePlay::GetLegal(int player) const {
    return mState->PlayerWithID(player)->GetLegalPlays();
}
