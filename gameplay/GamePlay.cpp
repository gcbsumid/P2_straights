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

int GamePlay::CARD_COUNT = 52; 

// Constructor
GamePlay::GamePlay() : mQuit(false), mView(NULL) {
    mState = new GameState(this);
}

GamePlay::~GamePlay() {
    delete mState;
}

void GamePlay::AddView(ViewInterface* v) {
    mView = v;
}

void GamePlay::AddModelObserver(ModelObserver* m) {
    mState->AddObserver(m);
}

void GamePlay::AddPlayer(bool human) {
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
    mState->Shuffle();
    mState->DealCards();
    
    mState->ResetNextPlayer(mState->PlayerWithSevenOfSpades());

    cout << "A round has begun" << endl;
    ContinueGame();
}

void GamePlay::EndRound() {
    mState->ClearCardsOnTable();
    // Round is over, let's tally scores and see if the game's over.
    // Keep track of the lowest score so we can see who won.
    int winner = -1;
    int minScore = 100000;

    bool endGame = false;

    mState->ResetNextPlayer(1);
    for (int i = 0; i < 4; i++) {
        Player* player = mState->NextPlayer();
        player->ClearDiscard();  // Calculate player's final score.
        int score = mState->GetScore(i + 1);
        if (score > 79) {
            endGame = true;
        }
        if (score < minScore) {
            minScore = score;
            winner = player->GetID();
        }
    }
    if (endGame) {
        EndGame(winner);
    } else {
        StartRound();
    }
}

void GamePlay::EndGame(int winner) {
    mState->EndGame(winner);
}

void GamePlay::ContinueGame() {
    Player* nextPlayer = mState->NextPlayer(); 
    
    while (true) {
        cout << "It is " << nextPlayer->GetID() << "'s turn to play" << endl;
        if (!nextPlayer->TakeTurn()) {
            // No cards left, round over?
            EndRound();
            break;
        }
        // If we have a human player, we need to take various actions depending on what they input.
        if (nextPlayer->IsHuman()) {
            cout << "We have a human, freaking out" << endl;
            break;
        }
        nextPlayer = mState->NextPlayer();
    }
}

bool GamePlay::PlayCard(Suit suit, Rank rank) {
    Player* p = mState->CurrentPlayer();
    cout << "Player " << p->GetID() << " played the " << rank << " of " << suit << endl;
    Card c(suit, rank);
    vector<Card*> legalPlays = p->GetLegalPlays();

    // The client can discard a card by playing it. DiscardCard returns false if there are legal plays or
    // if the card isn't in the hand, so this is perfectly legal.
    if (DiscardCard(p->GetID(), suit, rank)) {
        return false;
    }

    bool isLegal = false;
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
