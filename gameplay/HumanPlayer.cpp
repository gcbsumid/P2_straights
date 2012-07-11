#include <iostream>
#include "Command.h"
#include "Gameplay.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "Card.h"

using namespace std;

// Prompt command from AI
void HumanPlayer::TakeTurn() {
    // Prompt user
    mGameplay->PrintCardsOnTable();
    this->PrintHand();
    this->PrintLegal();
    
    bool finishTurn = false;
    Command command;
    
    while (!finishTurn) {
        cout << ">";
        cin >> command;
        Card* cardPtr;
        Card* cardInHand;
        switch (command.type) {
            case PLAY: {
                cardPtr = &(command.card);
                cardInHand = CardInHand(cardPtr);

                // If the user has the seven of spades, that is their only legal option.
                Card sevenOfSpades(SPADE,SEVEN);
                if (this->PlayerHas(&sevenOfSpades) && !(*cardPtr == sevenOfSpades)) {
                    cout << "This is not a legal play." << endl;
                    break;
                }

                // cardInHand now contains the address of the card in your hand
                if (mGameplay->IsLegal(cardPtr) && cardInHand != NULL) {
                    // Card is legal
                    this->PlayCardInHand(cardInHand);
                    finishTurn = true;
                } else {
                    // card is not legal
                    cout << "This is not a legal play." << endl;
                }
                break;
            } case DISCARD: {
                cardPtr = &(command.card);
                cardInHand = CardInHand(cardPtr);
                if (!mHasLegal && cardInHand != NULL) {
                    // No legal moves and the card the card is in your hand
                    cout << "Player " << mID << " discards " << *cardPtr << "." << endl;
                    mDiscard.push_back(cardInHand);
                    RemoveFromHand(cardInHand);
                    finishTurn = true;
                } else if (mHasLegal) {
                    // The player has a legal play, cannot discard.
                    cout << "You have a legal play. You may not discard." << endl;
                } else{
                    // no legal play, but the card played is not in your hand
                    cout << "This is not a legal play." << endl;
                }
                break;
            } case DECK: {
                mGameplay->PrintAllCards();
                break;
            } case QUIT: {
                mGameplay->Quit();
                finishTurn = true;
                break;
            } case RAGEQUIT: {
                mRageQuit = true;
                finishTurn = true;
                break;
            } default: {
                cout << "Invalid Type" << endl;
                break;
            }
        } 
    }
    mHasLegal = false;
}

// Print current hand
void HumanPlayer::PrintHand() const {
    cout << "Your hand:";
    for (int i = 0; i < 13; i++) {
        if (mHand[i]) {
            cout << " " << *(mHand[i]);
        }
    }
    cout << endl;
}

// Print Legal moves in hand
void HumanPlayer::PrintLegal() {
    cout << "Legal Plays:";

    // If the user has the seven of spades, that is their only legal option.
    Card sevenOfSpades(SPADE,SEVEN);
    if (this->PlayerHas(&sevenOfSpades)) {
        cout << " " << sevenOfSpades << endl;
        return;
    }

    for (int i = 0; i < 13; i++) {
        if (mHand[i] && mGameplay->IsLegal(mHand[i])) {
            cout << " " << *(mHand[i]);
            mHasLegal = true;
        }
    }
    cout << endl;
}

// Is Human: yes
bool HumanPlayer::IsHuman() const {
    return true;
}

// Returns the address of the card in your hand
Card* HumanPlayer::CardInHand(Card* card) const {
    for (int i = 0; i < 13; i++) {
        if (mHand[i] && *mHand[i] == *card) {
            return mHand[i];
        }
    }
    return NULL;
}

// Player rage quits. Sets boolean to true
bool HumanPlayer::IsRageQuitted() const {
    return mRageQuit;
}
