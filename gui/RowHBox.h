#ifndef ROW_HBOX
#define ROW_HBOX

#include <gtkmm/box.h>
#include "CardPics.h"

class CardPics;

class RowHBox : public Gtk::HBox {
public:
    RowHBox(int, int);
    virtual ~RowHBox();
    void update();

protected:
    int mSuit;
    //Gtk::VBox* mCards[13];
    CardPics* mCards[13];
};

#endif