#include "TableVBox.h"
#include "RowHBox.h"
#include "../gameplay/Card.h"
#include <iostream>
using namespace std;

class GamePlay;

// Constructor - it creates the 4 suits in a Hbox each
TableVBox::TableVBox(DeckGui* deck, GamePlay* gameplay) : mGamePlay(gameplay), mPanel(false, 5), mDeck(deck) { }

void TableVBox::Display() {
    // Sets some paramters
        //set_border_width(10);

    // Set the look of the panel;
    add(mPanel);

    for (int i = 0; i < 4; i++) {
        mSuits[i] = new RowHBox(mDeck, mGamePlay, i, 5);
        mPanel.pack_start(*mSuits[i], Gtk::PACK_SHRINK);
        cout << "this should be adding hbox " << i << endl;
    }

    // The final step is to display the buttons (they display themselves)
    show_all_children();
}

// Deletes the suit hboxes
TableVBox::~TableVBox(){
    for (int i = 0; i < 4; i++) {
        delete mSuits[i];
    }
}

void TableVBox::CardPlayed(Card* card) {
    cout << "Alerting suit " << (int)card->getSuit() << " of the fact that card " << *card << " was played" << endl;
    mSuits[(int)card->getSuit()]->CardPlayed(card);
}

void TableVBox::ClearTable() {
    
}
