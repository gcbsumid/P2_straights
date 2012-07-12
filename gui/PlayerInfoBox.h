#ifndef PLAYER_INFO
#define PLAYER_INFO

#include <gtkmm/box.h>
#include <gtkmm/button.h>

class PlayerInfoBox : public Gtk::VBox {
public:
    PlayerInfoBox(bool, int); // bool is for human or computer, int is player number
    ~PlayerInfoBox();

private:
    int mPlayerNumber;
    bool mIsHuman;
    int mScore;

    // Widgets
    Gtk::VBox mPanel;          // Frame Box
    Gtk::VBox mButtonBox;       // VBox containing button data
    Gtk::VBox mScoreTextBox;    // VBox containing the score as text
    Gtk::Button mRageQuit;      // Rage Quit Button
    Gtk::Button mDiscard;   // button that displays the discard pile

    void RageQuitButtonPressed();
    void DiscardButtonPressed();
};

#endif