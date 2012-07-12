#include "RowHBox.h"
#include "CardPics.h"
#include "DeckGui.h"
#include "../gameplay/Card.h"
using namespace std;

// Constructor - it creates the 4 suits in a Hbox each
RowHBox::RowHBox(int suit, int spacing = 5) : HBox(true, spacing), mSuit(suit) {
    for (int i = 0; i < 13; i++) {
        if (i == 6 && mSuit == 3) {
            // 7 of spades;
            mCards[i] = new CardPics(false, SEVEN, SPADE);
        } else {
            mCards[i] = new CardPics(false);
        }
        add(*mCards[i]);
    }

    // The final step is to display the buttons (they display themselves)
    show_all();

}

// Deletes the each card object
RowHBox::~RowHBox() {
    for (int i = 0; i < 13; i++) {
        delete mCards[i];
    }
}

void RowHBox::update(){
    //for (int i = 0; i < 13; i++) {
    //    mCards[i]->update();
    //}
}