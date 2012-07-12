#ifndef CARDPICS
#define CARDPICS
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include "DeckGui.h"
#include "../gameplay/Card.h"

class DeckGui;

class CardPics : public Gtk::HBox {
public:
    CardPics(bool isButton, Rank f = RANK_COUNT, Suit s = SUIT_COUNT);
    ~CardPics();
private:
    static DeckGui deck;

    // Member widgets:
    Gtk::Image* mCard;          // Images to display.
    Gtk::Button mButton;        // Button that will hold an image.
};

#endif 