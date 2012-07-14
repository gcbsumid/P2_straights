/************************************************
 * PlayerInfoBox.h                              *
 * Author: Christian Sumido, Didier Smith       *
 ************************************************/

#ifndef PLAYER_INFO
#define PLAYER_INFO

// Including Gtkmm Libraries
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/label.h>

// Including our written code
#include "HandHBox.h"
#include "DeckGui.h"

class GamePlay;

class PlayerInfoBox : public Gtk::VBox {
public:
    PlayerInfoBox(bool, int, GamePlay* gameplay, DeckGui*); // bool is for human or computer, int is player number
    ~PlayerInfoBox();

    // Updates the score being displayed
    void UpdateScore(int score);

    // Updates the box to reflect that a human has been changed to a computer
    void HumanToComputer();

    // Adds a card to the discard pile
    void AddToDiscardPile(Rank r, Suit s);

    // Resets the discard pile to display blank cards
    void DeleteDiscardPile();

    // Disables the buttons if the player goes from Human to Computer
    void DisableButtons();

    // Returns a pointer to the Discard Pile Widget
    HandHBox* GetDiscardPile();

private:
    int mPlayerNumber;              // Player number
    bool mIsHuman;                  // Determines whether human player or not
    int mScore;                     // Displays the score

    GamePlay* mGamePlay;
    DeckGui* mDeck;

    // Widgets
    Gtk::VBox mPanel;               // Box that contains all the widgets in this class
    Gtk::VBox mButtonBox;           // VBox containing button data
    Gtk::Button mRageQuit;          // Rage Quit Button
    Gtk::Button mDiscard;           // button that displayeds the discard pile
    HandHBox mDiscardPile;          // Discard Pile to be displayed.
    
    Gtk::Label::Label* mPlayerName; // Player Name and status label
    Gtk::Label::Label* mScoreBox;   // Score label

    // Button functionality
    // when the rage quit button is pressed, alert the controller
    void RageQuitButtonPressed();

    // when the discard button is pressed, it displays the player's discard pile
    void DiscardButtonPressed();
};

#endif
