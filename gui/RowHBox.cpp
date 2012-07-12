#include "RowHBox.h"
//#include "CardPics.h"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "DeckGui.h"
#include "../gameplay/Card.h"
#include "CardPics.h"
#include <iostream> 
using namespace std;

// Constructor - it creates the 4 suits in a Hbox each
RowHBox::RowHBox(DeckGui* deck, int suit, int spacing = 5) : HBox(true, spacing), mSuit(suit), mDeck(deck) {
    for (int i = 0; i < 13; i++) {
        if (i == 6 && mSuit == 3) {
            cout << "Hurr durr found seven of spades lol" << endl;
            // 7 of spades;
            mCards[i] = new CardPics(false, mDeck, SEVEN, SPADE);
        } else {
            mCards[i] = new CardPics(false, mDeck, RANK_COUNT, SUIT_COUNT);
        }
        //mCards[i] = new Gtk::Button("Fuck Nuts");
        mCards[i]->set_name("Test");
        add(*mCards[i]);
    }

    // The final step is to display the buttons (they display themselves)
    show_all_children();

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
