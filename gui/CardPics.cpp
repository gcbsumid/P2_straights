#include "CardPics.h"
#include "DeckGui.h"
#include "../gameplay/Card.h"

DeckGui CardPics::deck;

CardPics::CardPics(bool isButton, Rank f, Suit s) 
        : HBox(false,0) {
    Glib::RefPtr<Gdk::Pixbuf> card;

    // Sets the image to be displayed
    if (f == RANK_COUNT || s == SUIT_COUNT) {
        card = deck.null();
    } else {
        card = deck.image(f, s);
    }
    mCard = new Gtk::Image(card);

    // If its a button, then I add it to the Hbox, else, I just add 
    // it as a static image
    if (isButton) {
        mButton.set_image(*mCard);
        add(mButton);
    } else {
        add(*mCard);
    }

    // display the widget
    show_all();
}

CardPics::~CardPics() {
    delete mCard;
}
