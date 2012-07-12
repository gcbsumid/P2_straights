#ifndef CARDPICS
#define CARDPICS
#include <gtkmm/hbox.h>
#include <gtkmm/image.h>
#include "DeckGui.h"

class CardPics : public Gtk::HBox {
public:
    CardPics(bool isButton, DeckGui::Faces f, DeckGui::Suits s);
    ~CardPics();
private:
    // Member widgets:
    Gtk::Image* mCard;          // Images to display.
    Gtk::Button mButton;        // Button that will hold an image.
};

#endif 