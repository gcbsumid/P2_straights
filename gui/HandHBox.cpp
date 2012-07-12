#include "HandHBox.h"
#include "CardPics.h"
#include "../gameplay/Card.h"
#include "DeckGui.h"
using namespace std;

// Constructor - it creates the 4 suits in a Hbox each
HandHBox::HandHBox(Vector<Card*> cards, int spacing = 5) : HBox(true, spacing){
    int i = 0;
    Card* card = cards.at(i);

    // Display all the cards
    while (card != NULL) {
        bool isLegal = false;
        // TODO: change this to the actual is legal function
        if(isLegal(card)) {
            isLegal = true;
        }

        mCards[i] = new CardPics(isLegal, card->getRank(), card->getSuit());
        add(mCards[i]);
        i++;
    }

    // The final step is to display the buttons (they display themselves)
    show_all();

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

void HandHBox::NoLegalPlays(){
    // TODO: delete all images and replace them as buttons
}