/************************************************
 * View.cpp                                     *
 * Author: Christian Sumido, Didier Smith       *
 ************************************************/

// Include our written code
#include "View.h"
#include "TableVBox.h"
#include "RowHBox.h"
#include "DeckGui.h"
#include "PlayerInfoBox.h"
#include "../gameplay/GamePlay.h"

// Include Gtkmm Libraries
#include <gtkmm/messagedialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/stock.h>
#include <gtkmm/dialog.h>
#include <gtkmm/label.h>

// Include C++ Libraries
#include <sstream>
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

// View Constructor
View::View(DeckGui* deck, GamePlay* gameplay) : 
        Gtk::Window(), mGamePlay(gameplay), mDeck(deck),
        mTable(deck, gameplay), mMenu(false, 10), 
        mPanel(false, 5), mHand(), mPlayerInfoContainer(true, 5) {
    
    // Sets some properties in the window
    set_title("Straights");
    maximize();

    // Initialize mPlayerInfo[x] to NULL pointers
    for (int i = 0; i < 4; i++) {
        mPlayerInfo[i] = NULL;
        mHand[i] = NULL;
    }

    // Sets some attributes of the frame
    mTable.set_label("Cards on the Table:");
    mTable.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP);
    mTable.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    // Adds the Panel;
    add(mPanel);


    /*****************************
     * This initializes the menu *
     *****************************/
    // Define the actions:
    mRefActionGroup = Gtk::ActionGroup::create();

    mRefActionGroup->add(Gtk::Action::create("MenuFile","_Game"));
    mRefActionGroup->add(Gtk::Action::create("New Game", "New Game"),
          sigc::mem_fun(*this, &View::onNewGame));
    mRefActionGroup->add(Gtk::Action::create("New Seed", "New Seed"),
          sigc::mem_fun(*this, &View::onNewSeed));
    mRefActionGroup->add(Gtk::Action::create("Quit", "Quit"),
          sigc::mem_fun(*this, &View::onQuit));

    // Define how the actions are presented in the menus and toolbars:
    Glib::RefPtr<Gtk::UIManager> mRefUIManager = Gtk::UIManager::create();
    mRefUIManager->insert_action_group(mRefActionGroup);
    add_accel_group(mRefUIManager->get_accel_group());

    Glib::ustring ui_info = 
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='MenuFile'>"
        "      <menuitem action='New Game' />"
        "      <menuitem action='New Seed' />"
        "      <separator/>"
        "      <menuitem action='Quit' />"
        "    </menu>"
        "  </menubar>"
        "</ui>";

    try {
        mRefUIManager->add_ui_from_string(ui_info);
    } catch (const Glib::Error& ex) {
        cerr << "building menus and toolbars failed: " << ex.what();
    } // catch

    Gtk::Widget* pMenuBar = mRefUIManager->get_widget("/MenuBar");

    /**********************
     * DONE THE MENU       
     ***********************/

    // Adds the pMenu to the mMenu container
    mMenu.pack_start(*pMenuBar);

    // Adds the Menu container, Table container, and Player
    // Information Container to the Gui
    mPanel.pack_start(mMenu, Gtk::PACK_SHRINK);
    mPanel.pack_start(mTable, Gtk::PACK_SHRINK);
    mPanel.pack_start(mPlayerInfoContainer, Gtk::PACK_SHRINK);

    // Showing all the children
    show_all_children();
}

// View Destructor
View::~View() {
    for (int i = 0; i < 4; i++) {
        if (mPlayerInfo[i] != NULL) {
            delete mPlayerInfo[i];
        }
        if (mHand[i] != NULL) {
            delete mHand[i]; 
        }
    }
}

// Starts a new game
void View::onNewGame() {
    // Clearing from the previous game.
    ResetGame();
    // Start a new game in the Controller
    mGamePlay->PlayGame();
}

// This is used to set a new seed.
void View::onNewSeed() {
    // Prompt the user for the seed via a dialog window
    Gtk::Dialog dialog("Enter a new seed.", *this);

    Gtk::Entry seedField;
    Gtk::Label seedLabel("New seed");

    // Adding widgets to the dialog box
    Gtk::VBox* contentArea = dialog.get_vbox();
    contentArea->pack_start(seedLabel, true, false);
    contentArea->pack_start(seedField, true, false);

    // Displaying children in the dialog box
    seedField.set_text("");
    seedLabel.show();
    seedField.show();

    // Adding okay and cancel buttons in the dialog box
    dialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

    // Run the dialog box and block until response.
    int result = dialog.run();
    if (result == Gtk::RESPONSE_OK || result == Gtk::RESPONSE_ACCEPT) {
        string seedstr = seedField.get_text();
        stringstream seedstream;
        int seed = 0;
        seedstream << seedstr;
        seedstream >> seed;
        // This resets the seed in the controller if Accepted.
        mGamePlay->ResetSeed(seed);
    }
}
 
// Quit th program.
void View::onQuit() {
    // Closes the main window to stop the Gtk::Main::run()
    hide();
}

/****************************************************
 * Implementations of the view external interface.  *
 ****************************************************/

// Adds a new player and asks if it is a human or computer.
void View::AddPlayer(int player) {
    stringstream s;
    s << "Is player " << player << " a human or a computer?";
    Gtk::Dialog dialog(s.str());
    // Adds Human / Computer buttons
    dialog.add_button("Player is a Human", 1);
    dialog.add_button("Player is a Computer", 2);

    // runs the dialog widget
    int resp = dialog.run();
    if (resp == 1) {
        // adds a Human player.
        mGamePlay->AddPlayer(true);
    } else {
        // adds a Computer player.
        mGamePlay->AddPlayer(false);
    }
}

// Prompts human for legal play
void View::HumanTurn(int player) {
    assert(player > 0 && player < 5);
    // I ask for all the legal cards in my hand.
    vector<Card*> legalHand = mGamePlay->GetLegal(player);
    if (!legalHand.empty()) {
        // We have legal cards to play
        mHand[player-1]->DisplayLegalCards(legalHand);
    } else {
        // No legal plays.
        mHand[player-1]->TurnHandToButton();
    }
}


/****************************************************************
 * Observer pattern - notifications of state changes from mode  *
 ****************************************************************/

// creates an HBox for the hand to be displayed also creates a new player
void View::Model_PlayerAdded(bool IsHuman, int playerid) {
    assert(playerid > 0 && playerid < 5);
    if (IsHuman) {
        // If human was added, add a cards in hand container to the UI
        mHand[playerid-1] = new HandHBox(mDeck, mGamePlay, playerid);
        mPanel.pack_start(*mHand[playerid-1], Gtk::PACK_SHRINK);
    } else {
        // Else, don't add any.
        mHand[playerid-1] = NULL;
    }
    
    // Displays the player information onto the screen
    mPlayerInfo[playerid-1] = new PlayerInfoBox(IsHuman, playerid, mGamePlay, mDeck);
    mPlayerInfoContainer.add(*mPlayerInfo[playerid-1]);
    mPlayerInfo[playerid-1]->show();
}

// Gives the list of cards to the mHand box to be displayed
void View::Model_CardsDealt(vector<vector<Card*> > playerCards) {
    for (int i = 0; i < 4; i++) {
        // passes all the cards belonging to human players
        if (!playerCards[i].empty()) {
            // Adds cards to hand and display them
            assert(mHand[i] != NULL);
            mHand[i]->AddCards(playerCards.at(i));
            mHand[i]->show();
        }
    }
}

// Displays the new round dialog box
void View::Model_NewRound(int roundNumber) {
    if (!IsThereAnyHuman()) {
        return;
    }

    // Creates a dialog box displaying the round number.
    Gtk::Dialog dialog("New Round");
    stringstream message;
    message << "Round " << roundNumber << " will begin shortly.";
    Gtk::VBox* mDialogBox = dialog.get_vbox();
    Gtk::Label::Label mLabel(message.str().c_str());
    mDialogBox->add(mLabel);
    dialog.show_all_children();

    // Add button and then running the dialog widget
    dialog.add_button("Okay", 1);
    dialog.run();
}

// Turns human UI into Computer UI. Replaces staus as Computer in the UI.
// Also removes the hand of cards in the UI
void View::Model_PlayerRageQuitted(int player) {
    // Changes the Player Info box status from Human to Computer
    mPlayerInfo[player-1]->HumanToComputer();

    // Remove and Delete the cards in hand widget; and set pointer to NULL
    mPanel.remove(*mHand[player-1]);
    delete mHand[player-1];
    mHand[player-1] = NULL;
}

// Clears the table
void View::Model_CardsCleared() {
    mTable.ClearTable();
}

// Updates the Score
void View::Model_ScoreUpdated(int player, int score, int prevScore) {
    // show the user the discard pile and the addition score if there is 
    // at least one human playing. If not, then just continue the game.
    if (IsThereAnyHuman()) {
        stringstream temp;
        temp << "Player " << player;

        // Creates the dialog title
        Gtk::Dialog dialog(temp.str().c_str());

        // Clear out the stream
        temp.str("");
        
        // Create widgets to be added to the dialog Vbox
        Gtk::VBox* dialogBox = dialog.get_vbox();
        temp << "Player " << player << " Score: " << prevScore;
        temp <<" + " << score - prevScore << " = " << score;
        Gtk::Label::Label message(temp.str().c_str());
        HandHBox* discardPile = mPlayerInfo[player-1]->GetDiscardPile();

        // Adding widgets to the dialog box
        dialogBox->add(message);
        dialogBox->add(*discardPile);
        dialogBox->show_all_children();
        dialog.add_button("Okay", 1);
        dialog.run();
    }

    // at the end of the round, this is their accumulative score.
    assert(player > 0 && player < 5);
    mPlayerInfo[player-1]->UpdateScore(score);
}

// Clears the player's discard pile in the player info box
void View::Model_DiscardsCleared(int player) {
    if (mPlayerInfo[player-1] != NULL) {
        // clears the discard pile
        mPlayerInfo[player-1]->DeleteDiscardPile();
    }
}

// User plays a card and removes the card from human hand in the UI
void View::Model_CardPlayed(int player, Card* card) {
    assert(player > 0 && player < 5);
    // Puts the played card on the table
    mTable.CardPlayed(card);
    if(mHand[player-1]){
        // If human, removes the card from the player's hand in the UI and
        // returns all buttons to static images
        RemoveCardFromHand(player, card);
    }
}

// Put the discarded cards in the Player Info Box's discard pile
void View::Model_CardDiscarded(int player, Card* card) {
    assert(player > 0 && player < 5);
    
    // Add card discarded to the player's discard pile in the info box
    mPlayerInfo[player-1]->AddToDiscardPile(card->getRank(), card->getSuit());
    
    if(mHand[player-1] != NULL){
        // If human, removes the card from the player's hand in the UI and
        // returns all buttons to static images
        RemoveCardFromHand(player, card);
    }

}

// Displays the End of the game.
void View::Model_EndGame(vector<int> players) {
    assert(!players.empty());

    // Disable the discard and ragequit buttons for players
    for (int i = 0; i < 4; i++) {
        mPlayerInfo[i]->DisableButtons();
    }

    // Display the winner in a dialog button.
    for (int i = 0; i < players.size(); i++) {
        Gtk::MessageDialog dialog(*this, "Game over!");
        stringstream s;
        s << "The winner is...player " << players[i] << "!";
        dialog.set_secondary_text(s.str());
        dialog.run();
    }
}

// Returns true if there are humans left in the game
bool View::IsThereAnyHuman() {
    for (int i = 0; i < 4; i++) {
        if (mHand[i] != NULL) {
            return true;
        } 
    }
    // Return false if all players are computer
    return false;
}

// Resets the entire UI
void View::ResetGame() {
    for (int i = 0; i < 4; i++) {
        // Clears the Player Information Boxes
        if (mPlayerInfo[i] != NULL) {
            // remove the Player Info Widget, delete it, and set to null
            mPlayerInfoContainer.remove(*mPlayerInfo[i]);
            delete mPlayerInfo[i];
            mPlayerInfo[i] = NULL;
        }

        // Clears the Hand of Card that human players see
        if (mHand[i] != NULL) {
            // Remove the Hand of Cards displayed for human. delete and set
            // to nu;;
            mPanel.remove(*mHand[i]);
            delete mHand[i];
            mHand[i] = NULL;
        }
    }

    // Clears the tbale
    mTable.ClearTable();
}

// Removes a card from the player's hand in the UI
void View::RemoveCardFromHand (int player, Card* card) {
    // Remove card from hand 
    mHand[player-1]->CardPlayed(card);
    // Changes all the buttons back to images
    mHand[player-1]->TurnHandToStatic();
}