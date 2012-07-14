/************************************************
 * TableVBox.h                                  *
 * Author: Christian Sumido, Didier Smith       *
 ************************************************/

#ifndef TABLE_VBOX
#define TABLE_VBOX

// Include Gtkmm Libraries
#include <gtkmm/frame.h>

// Include our written code
#include "RowHBox.h"

// Forward declare classes
class RowHBox;
class DeckGui;
class Card;
class GamePlay;

class TableVBox : public Gtk::Frame {
public:
    TableVBox(DeckGui* deck, GamePlay* gameplay);       
    ~TableVBox();

    // Inserts the card being played into its proper place on the table
    void CardPlayed(Card* card);
    
    // Clears the table of cards
    void ClearTable();

private:
    GamePlay* mGamePlay;    // A pointer to the controller
    Gtk::VBox mPanel;       // The VBox that contains all the objects in this file
    RowHBox* mSuits[4];     // This is the row of cards that have the same suit
    DeckGui* mDeck;         // This is the deck that contains the image of all cards
};

#endif
