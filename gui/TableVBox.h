#ifndef TABLE_VBOX
#define TABLE_VBOX

#include <gtkmm/frame.h>
#include "RowHBox.h"

class RowHBox;
class DeckGui;
class Card;
class GamePlay;

class TableVBox : public Gtk::Frame {
public:
    TableVBox(DeckGui* deck, GamePlay* gameplay);
    ~TableVBox();
    void update();
    void Display();
    void CardPlayed(Card* card);
    void ClearTable();
private:
    GamePlay* mGamePlay;
    Gtk::VBox mPanel;
    RowHBox* mSuits[4];
    DeckGui* mDeck;
};

#endif
