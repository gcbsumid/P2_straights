#include "HandHBox.h"
#include "RowHBox.h"
#include "CardPics.h"
#include "../gameplay/Card.h"
#include "DeckGui.h"
using namespace std;

// Constructor - it creates the 4 suits in a Hbox each
HandHBox::HandHBox(DeckGui* deck, int player, int spacing) : RowHBox(deck, -1, spacing) {
    mCards.resize(13);


    // The final step is to display the buttons (they display themselves)

}

// Deletes the each card object
HandHBox::~HandHBox() {
    for (int i = 0; i < 13; i++) {
        if(mCards[i]) {
            delete mCards[i];
        }
    }
}

void HandHBox::update(){
    for (int i = 0; i < 13; i++) {
        mCards[i]->update();
    }
}

void HandHBox::StaticToButton() {
    // TODO: delete all images and replace them as buttons
    for (int i = 0; i < 13; i++) {
        if (mCards[i]->IsValidCard()) {
            remove(mCards[i]);
            CardPics* card = new CardPics(true, mCards[i]->GetRank(), mCards[i]->getSuit());
            delete mCards[i];
            mCards[i] = card;
            add(mCards[i]);
        }
    }
}

void HandHBox::ButtonToStatic() {
    // TODO: delete buttons and replace them as static images
    for (int i = 0; i < 13; i++) {
        if (mCards[i]->IsValidCard()) {
            remove(mCards[i]);
            CardPics* card = new CardPics(false, mCards[i]->getRank(), mCards[i]->getSuit());
            delete mCards[i];
            mCards[i] = card;
            add(mCards[i]);
        }
    }
}

void HandHBox::AddCards(std::vector<Card*> cards) {
    // Display all the cards
    for (int i = 0; i < 13; i++) {
        Card* card = cards.at(i);
        mCards[i] = new CardPics(false, deck, card->getRank(), card->getSuit());
        add(*mCards[i]);
    }
    // show_all_children();  // Not sure if needed
}