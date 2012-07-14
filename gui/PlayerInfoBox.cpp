/************************************************
 * PlayerInfoBox.cpp                            *
 * Author: Christian Sumido, Didier Smith       *
 ************************************************/

// Include our written code
#include "PlayerInfoBox.h"
#include "HandHBox.h" 
#include "DeckGui.h"
#include "../gameplay/GamePlay.h"

// Include Gtkmm Libraries
#include "gtkmm/textbuffer.h"
#include "gtkmm/textview.h"
#include <gtkmm/dialog.h>
#include <gtkmm/label.h>

// Include C++ libraries
#include <sstream>
#include <iostream>
using namespace std;

// Constructor 
PlayerInfoBox::PlayerInfoBox(bool isHuman, int playerNum, GamePlay* gameplay, DeckGui* deck) : 
    VBox(false, 2), mPlayerNumber(playerNum), mIsHuman(isHuman), 
    mScore(0), mGamePlay(gameplay), mDeck(deck), mButtonBox(false),  
    mRageQuit("Rage Quit"), mDiscard("Discard Pile"), mDiscardPile(deck, gameplay, playerNum, 5) {

    // add panel
    add(mPanel);

    stringstream playerNumberStream, scoreStream; 
    
    // Determine whether the player info box will say human or computer
    playerNumberStream << "Player " << playerNum << endl;
    if (isHuman) {
        playerNumberStream << "Status: Human";
    } else {
        playerNumberStream << "Status: Computer";
    }

    // displays the Player and its status
    mPlayerName = new Gtk::Label::Label(playerNumberStream.str().c_str(), Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);

    // Displays the score
    scoreStream << "Score: " << mScore;
    mScoreBox = new Gtk::Label::Label(scoreStream.str().c_str(), Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);

    // adds both labels to the panel so it can be displayed
    mPanel.add(*mPlayerName);
    mPanel.add(*mScoreBox);

    //Add Button container
    add(mButtonBox);

    // If not human, buttons are disabled
    if (!isHuman) {
        mRageQuit.set_sensitive(false);
        mDiscard.set_sensitive(false);
    }
    // Adds the buttons 
    mButtonBox.add(mRageQuit);
    mButtonBox.add(mDiscard);

    // clicked functions assigned to buttons
    mRageQuit.signal_clicked().connect(sigc::mem_fun(*this, &PlayerInfoBox::RageQuitButtonPressed));
    mDiscard.signal_clicked().connect(sigc::mem_fun(*this, &PlayerInfoBox::DiscardButtonPressed));
    
    // Display everythin
    show_all();
}

// Destructor 
PlayerInfoBox::~PlayerInfoBox() {
    delete mPlayerName;
    delete mScoreBox;
}

// If the player pressed the rage quit button, call the controller
void PlayerInfoBox::RageQuitButtonPressed() {
    mGamePlay->RageQuit(mPlayerNumber);
}

// Display a dialog box that shows the player's discard pile
void PlayerInfoBox::DiscardButtonPressed() {
    // Creates the dialog box and adds the discard pile
    Gtk::Dialog dialog("Discard Pile");
    Gtk::VBox* mDialogBox = dialog.get_vbox();
    mDialogBox->add(mDiscardPile);
    dialog.add_button("Okay", 1);

    // Shows and runs dialog
    dialog.show_all_children();
    dialog.run();
}

// Updates the displayed score
void PlayerInfoBox::UpdateScore(int score) {
    // Update Display Scores
    stringstream scoreStream;
    mScore = score;
    scoreStream << "Score: " << mScore;

    // sets the label to display the new score
    mScoreBox->set_text(scoreStream.str().c_str());
}

// Updates the label chaning the status from human to computer
void PlayerInfoBox::HumanToComputer() {
    stringstream playerNumberStream;
    playerNumberStream << "Player " << mPlayerNumber << endl;
    playerNumberStream << "Status: Computer";
    mPlayerName->set_text(playerNumberStream.str().c_str());

    // Also disables all the buttons sinc it is a computer
    DisableButtons();
}

// Disables the rage quit button and the discard button
void PlayerInfoBox::DisableButtons() {
    // Disables Rage Quit and Discard button when computer or game over.
    mRageQuit.set_sensitive(false);
    mDiscard.set_sensitive(false);
}

// Adds a card to the discard pile
void PlayerInfoBox::AddToDiscardPile(Rank r, Suit s) {
    mDiscardPile.AddCard(r, s);
}

// Resets the discard pile to display null images
void PlayerInfoBox::DeleteDiscardPile() {
    mDiscardPile.Reset();
}

// Returns a pointer to the discard pile widget
HandHBox* PlayerInfoBox::GetDiscardPile() {
    return &mDiscardPile;
}