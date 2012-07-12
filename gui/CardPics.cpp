#include "CardPics.h"

CardPics::CardPics(bool isButton, DeckGui::Faces f = SUIT_COUNT, DeckGui::Suits s = RANK_COUNT) {
    const Glib::RefPtr<Gdk::Pixbuf> card;

    // Sets the image to be displayed
    if (f == SUIT_COUNT || s == RANK_COUNT) {
        card = deck.getNullCardImage();
    } else {
        card = deck.getCardImage(f, s);
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
