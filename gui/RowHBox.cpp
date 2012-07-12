#include "RowHBox.h"
//#include "CardPics.h"
#include "gtkmm/box.h"
#include "DeckGui.h"
#include "../gameplay/Card.h"
#include <iostream> 
using namespace std;

// Constructor - it creates the 4 suits in a Hbox each
RowHBox::RowHBox(int suit, int spacing = 5) : HBox(true, spacing), mSuit(suit) {
    for (int i = 0; i < 13; i++) {
        if (i == 6 && mSuit == 3) {
            // 7 of spades;
            //mCards[i] = new CardPics(false, SEVEN, SPADE);
        } else {
            //mCards[i] = new CardPics(false, RANK_COUNT, SUIT_COUNT);
        }
        mCards[i] = new Gtk::VBox(false);
        mCards[i]->set_name("Test");
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