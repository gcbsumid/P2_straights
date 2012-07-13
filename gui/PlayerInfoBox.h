#ifndef PLAYER_INFO
#define PLAYER_INFO

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/textview.h>
#include <gtkmm/dialog.h>
#include "HandHBox.h"
#include "DeckGui.h"

class GamePlay;

class PlayerInfoBox : public Gtk::VBox {
public:
    PlayerInfoBox(bool, int, GamePlay* gameplay, DeckGui*); // bool is for human or computer, int is player number
    ~PlayerInfoBox();

    void UpdateScore(int score);
    void HumanToComputer();
    void AddToDiscardPile(Rank r, Suit s);
    void DeleteDiscardPile();
    void DisableButtons();
private:
    int mPlayerNumber;
    bool mIsHuman;
    int mScore;

    GamePlay* mGamePlay;
    DeckGui* mDeck;

    // Widgets
    Gtk::VBox mPanel;          // Frame Box
    Gtk::VBox mButtonBox;       // VBox containing button data
    Glib::RefPtr<Gtk::TextBuffer> mScoreText; // player score
    Glib::RefPtr<Gtk::TextBuffer> mPlayerName; // player name
    Gtk::TextView mPlayerTextBox;   // Displays the player name
    Gtk::TextView mScoreTextBox;    // VBox containing the score as text
    Gtk::Button mRageQuit;      // Rage Quit Button
    Gtk::Button mDiscard;   // button that displays the discard pile

    HandHBox mDiscardPile; // Discard Pile to be displayed.

    void RageQuitButtonPressed();
    void DiscardButtonPressed();
};

#endif
