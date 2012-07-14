/************************************************
 * HandHBox.cpp                                 *
 * Author: Christian Sumido, Didier Smith       * 
 ************************************************/

// Include our written code
#include "HandHBox.h"
#include "CardPics.h"
#include "../gameplay/Card.h"
#include "DeckGui.h"

// Include Gtkmm Libraries
#include <gtkmm/box.h>
#include <gtkmm/label.h>

// Include vectpr of Images
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class GamePlay;

// Constructor - it creates the 4 suits in a Hbox each
HandHBox::HandHBox(DeckGui* deck, GamePlay* gameplay, int player, int spacing) : 
                Gtk::HBox(true, spacing), mDeck(deck), mPlayer(player), 
                mName(NULL), mGamePlay(gameplay) {

    stringstream name;
    name << "Player " << player << endl;
    // adding label of which player the hand belongs to
    mName = new Gtk::Label::Label(name.str().c_str(), false);

    add(*mName);
    show_all();

    // Adds the cards but don't show them yet
    for (int i = 0; i < 13; i++) {
        // Set them as the null image
        mCards[i] = new CardPics(false, mDeck, mGamePlay, RANK_COUNT, SUIT_COUNT);
        add(*mCards[i]);
    }
}

// Deletes the each card object
HandHBox::~HandHBox() {
    for (int i = 0; i < 13; i++) {
        // Deteles all the cards
        if(mCards[i]) {
            delete mCards[i];
        }
    }
    // deletes the name label
    delete mName;
}

// When no legal plays, every card turns into a discard
// option, therefore we turn them into buttons
void HandHBox::TurnHandToButton() {
    for (int i = 0; i < 13; i++) {
        if (mCards[i]->IsImage() && mCards[i]->IsValidCard()) {
            // Turn this image into a button
            mCards[i]->ImageToButton();
        }
    }

}

// When the discard turn is done, return everything back
// into imagesons
void HandHBox::TurnHandToStatic() {
    for (int i = 0; i < 13; i++) {
        if (!mCards[i]->IsImage()) {
            // Turns this button into an image
            mCards[i]->ButtonToImage();
        }
    }
}

// Display all the legal cards and turn them into buttons
void HandHBox::DisplayLegalCards(vector<Card*> legalCards) {
    // Makes all the Legal cards into buttons
    for (int i = 0; i < 13; i++) {
        for(int j = 0; j < legalCards.size(); j++) {
            if (!mCards[i]->IsValidCard()) {
                // If the card is invalid (null image) just break 
                // out of the for loop
                break;
            }
            if (mCards[i]->GetRank() == legalCards[j]->getRank()) {
                if (mCards[i]->GetSuit() == legalCards[j]->getSuit()) {
                    // if the rank and suit match then we have a legal 
                    // card and turn the image into a button.
                    mCards[i]->ImageToButton();
                    break;
                }
            }
        }
    }

}

// Return all legal cards to images
void HandHBox::ReturnLegalCardsToImage() {
    for (int i = 0; i < 13; i++) {
        if (!mCards[i]->IsImage()) {
            // Loop through the hand and see if the card is a button
            // If it is, then turn it into an image
            mCards[i]->ButtonToImage();
        }
    }
}

// Add dealt cards to my hand
void HandHBox::AddCards(std::vector<Card*> cards) {
    // Display all the cards
    for (int i = 0; i < 13; i++) {
        Card* card = cards.at(i);
        // Loop through the vector of cards recieved and display 
        mCards[i]->UpdateCard(card->getRank(), card->getSuit());
    }
}

// Once a card is played, remove it from the human player's hand
void HandHBox::CardPlayed(Card* card) {
    for (int i = 0; i < 13; i++) {
        if (mCards[i]->GetRank() == card->getRank() 
            && mCards[i]->GetSuit() == card->getSuit()) {
            // Removing a card from hand means replacing it with the 
            // null image
            mCards[i]->RemoveCard();
            return;
        }
    }
}

// Add a specific card to hand
void HandHBox::AddCard(Rank r, Suit s) {
    // It adds the card to the first slot that is not a valid card
    for (int i = 0; i < 13; i++) {
        if (!mCards[i]->IsValidCard()) {
            mCards[i]->UpdateCard(r, s);
            return;
        }
    }
}

// Resets the hand to display the null image or invalid card
void HandHBox::Reset() {
    for (int i = 0; i < 13; i++) {
        if (mCards[i]->IsValidCard()) {
            // If a card is valid (or not a null image) then we replace
            // it with the null image
            mCards[i]->RemoveCard();
        }
    }
}