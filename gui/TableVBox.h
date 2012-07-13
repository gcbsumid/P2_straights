#ifndef TABLE_VBOX
#define TABLE_VBOX

#include <gtkmm/frame.h>
#include "RowHBox.h"

class RowHBox;
class DeckGui;
class Card;

class TableVBox : public Gtk::Frame {
public:
    TableVBox(DeckGui* deck);
    ~TableVBox();
    void update();
    void Display();
    void CardPlayed(Card* card);
private:
    Gtk::VBox mPanel;
    RowHBox* mSuits[4];
    DeckGui* mDeck;
};

#endif
