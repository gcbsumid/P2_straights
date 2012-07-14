/************************************************
 * View.h                                       *
 * Author: Christian Sumido, Didier Smith       * 
 ************************************************/

#ifndef MVC_VIEW_H
#define MVC_VIEW_H

// Include Gtkmm Libraries
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/actiongroup.h>

// Include our written code
#include "ViewInterface.h"
#include "TableVBox.h"
#include "HandHBox.h"
#include "PlayerInfoBox.h"
#include "../gameplay/ModelObserver.h"

// Include C++ Libraries
#include <vector>

class GamePlay;
class DeckGui;

class View : public Gtk::Window, public ModelObserver, public ViewInterface {
public:
    View(DeckGui* deck, GamePlay* gameplay);
    virtual ~View();

    /*******************************************************
     * Implementing the methods that the controller calls. *
     *******************************************************/
    // Shows that a player was added to the GUI
    virtual void AddPlayer(int player);     

    // Waits for an action in the GUI for the human's turn
    virtual void HumanTurn(int player);     

    
    /****************************************************************
     * Observer pattern - notifications of state changes from model *
     ****************************************************************/
    // Gives the view a list of cards that the human has been dealt 
    // and shows it on th Gui
    virtual void Model_CardsDealt(std::vector<std::vector<Card*> >);        
    
    // Adds the a Player info box and if a human, adds the hand of cards to 
    // the gui
    virtual void Model_PlayerAdded(bool isHuman, int id);

    // Replaces the player with an Computer player. Removes the hand from gui
    // and updates the player information box
    virtual void Model_PlayerRageQuitted(int player);

    // Clears the table on the gui
    virtual void Model_CardsCleared();

    // Shows the current score and what is being added after a round. Also 
    // shows the discard pile for each player.
    virtual void Model_ScoreUpdated(int player, int score, int prevScore);

    // It clears the player's discard pile
    virtual void Model_DiscardsCleared(int player);

    // The card is shown on the table and is removed from the hand in the gui
    virtual void Model_CardPlayed(int player, Card*);

    // Adds the card to the player's discard pile in the gui and removes it 
    // from the hand in the gui
    virtual void Model_CardDiscarded(int player, Card*);

    // Displays a popup saying the game is over and the winner
    virtual void Model_EndGame(std::vector<int> players);

    // Displays a new round will be beginning and resets the table
    virtual void Model_NewRound(int roundNumber);

private:
    GamePlay* mGamePlay;        // Controller
    DeckGui* mDeck;             // Contains the images of the deck

    // Signal Handlers
    virtual void onNewGame();       // New Game Menu function
    virtual void onNewSeed();       // New Seed Menu function
    virtual void onQuit();          // Quit Game Menu function

    // Helper functions
    bool IsThereAnyHuman();         // Returns true if there are humans playing, false if there aren't
    void ResetGame();               // Clears current UI from previous game if needed
    void RemoveCardFromHand(int player, Card* card); // Removes a card from the hand in the UI

    // Member Widgets
    TableVBox mTable;               // This is where all the cards on table is shown
    Gtk::VBox mMenu;                // This is the box that contains the menu buttons
    Gtk::VBox mPanel;               // This is the container for all objects in the gui 
    HandHBox* mHand[4];             // This is where all the human player's hand is shown
    PlayerInfoBox* mPlayerInfo[4];  // contains info and button for players
    Gtk::HBox mPlayerInfoContainer; // A box that contains all the player info boxes

    Glib::RefPtr<Gtk::UIManager> mRefUIManager;         // UI for the menu
    Glib::RefPtr<Gtk::ActionGroup> mRefActionGroup;     // Action group for the menu.
};

#endif
