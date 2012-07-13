#ifndef PLAYER_INFO
#define PLAYER_INFO

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include "gtkmm/textbuffer.h"
#include "gtkmm/textview.h"

class PlayerInfoBox : public Gtk::VBox {
public:
    PlayerInfoBox(bool, int); // bool is for human or computer, int is player number
    ~PlayerInfoBox();

    void UpdateScore(int score);
    void HumanToComputer();
private:
    int mPlayerNumber;
    bool mIsHuman;
    int mScore;

    // Widgets
    Gtk::VBox mPanel;          // Frame Box
    Gtk::VBox mButtonBox;       // VBox containing button data
    Glib::RefPtr<Gtk::TextBuffer> mScoreText; // player score
    Glib::RefPtr<Gtk::TextBuffer> mPlayerName; // player name
    Gtk::TextView mPlayerTextBox;   // Displays the player name
    Gtk::TextView mScoreTextBox;    // VBox containing the score as text
    Gtk::Button mRageQuit;      // Rage Quit Button
    Gtk::Button mDiscard;   // button that displays the discard pile

    void RageQuitButtonPressed();
    void DiscardButtonPressed();
};

#endif