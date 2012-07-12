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
    while(!mQuit) {
        mState->Shuffle();
        mState->DealCards();
        
        mState->ResetNextPlayer(mState->PlayerWithSevenOfSpades());

        // Which turn are we on?
        int turnCounter = 0;
        Player* nextPlayer = mState->NextPlayer(); 
        cout << "A new round begins. It's player " << nextPlayer->GetID() << "'s turn to play." << endl;
        
        while (turnCounter < CARD_COUNT) {
            nextPlayer->TakeTurn();
            // If we have a human player, we need to take various actions depending on what they input.
            if (nextPlayer->IsHuman()) {
                // Get a human pointer so we can call human-specific methods.
                HumanPlayer* human = (HumanPlayer*)nextPlayer;

                if (human->IsRageQuitted()) {
                    // Convert human into computer player.
                    nextPlayer = mState->HumanToComputer(human);
                    cout << "Player " << nextPlayer->GetID() << " ragequits. A computer will now take over." << endl;
                    nextPlayer->TakeTurn();    // The computer player must take a turn for the rage quit player.
                }
            }
            turnCounter++;
            nextPlayer = mState->NextPlayer();
        }

        mState->ClearCardsOnTable();
        // Round is over, let's tally scores and see if the game's over.
        // Keep track of the lowest score so we can see who won.
        int winner = -1;
        int minScore = 100000;
        mState->ResetNextPlayer(1);

        for (int i = 0; i < 4; i++) {
            Player* player = mState->NextPlayer();
            player->ClearDiscard();  // Calculate player's final score.
            int score = mState->GetScore(i + 1);
            if (score > 79) {
                mQuit = true;
            }
            if (score < minScore) {
                minScore = score;
                winner = player->GetID();
            }
        }
        if (mQuit) {
            cout << "Player " << winner << " wins!" << endl;
            return;
        }
    }
}
/*
void GamePlay::PrintCardsOnTable() const {
    cout << "Cards on the table:" << endl;
    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                cout << "Clubs:";
                break;
            case 1:
                cout << "Diamonds:";
                break;
            case 2:
                cout << "Hearts:";
                break;
            case 3:
                cout << "Spades:";
                break;
            default:
                // Should never get here.
                break;
        }
        for (int j = 0; j < 13; j++) {
            // Print out all cards in that suit which are on the table.
            if (mCardsOnTable.count(mArrangedCards[i*13 + j]) > 0) {
                cout << " " << mArrangedCards[i*13 + j]->getRankName();
            }
        }
        cout << endl;
    }
}*/

void GamePlay::Quit() {
    mQuit = true;
}

bool GamePlay::PlayCard(int player, Suit suit, Rank rank) {
    Card c(suit, rank);
    Player* p = mState->PlayerWithID(player);
    vector<Card*> legalPlays = p->GetLegalPlays();
    bool isLegal = false;
    for (vector<Card*>::const_iterator i = legalPlays.begin(); i != legalPlays.end(); i++) {
        if ((*i)->getRank() == rank && (*i)->getSuit() == suit) {
            isLegal = true;
            break;
        }
    }
    if (!isLegal) {
        cerr << "Tried to play an illegal card " << rank << suit << endl;
        return false;
    }
    Card* cardInHand = mState->CardInHand(player, &c);
    assert(cardInHand != NULL);

    mState->PlayCard(player, cardInHand);
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
        return false;
    }
    mState->DiscardCard(player, cardInHand);
    return true;
}

void GamePlay::RageQuit(int player) {              // Converts indicated player from human to computer.
    HumanPlayer* p = (HumanPlayer*)mState->PlayerWithID(player);
    p->RageQuit();
}
    
void GamePlay::ResetSeed(int seed) {
    srand48(seed);
}

vector<Card*> GamePlay::GetDiscards(int player) const {
    return mState->GetDiscards(player);
}
