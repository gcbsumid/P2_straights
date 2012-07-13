#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include "ViewInterface.h"
#include "../gameplay/ModelObserver.h"

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/actiongroup.h>
#include <vector>
#include "TableVBox.h"
#include "HandHBox.h"
#include "PlayerInfoBox.h"
//#include "gameplay/GamePlay.h"
//#include "gameplay/GameState.h"

class GamePlay; // Controller
//class GameState; // Model

class DeckGui;  // Images of cards.

class View : public Gtk::Window, public ModelObserver, public ViewInterface {
    //, public ControllerObserver, public ModelObserver
public:
    View(DeckGui* deck, GamePlay* gameplay);
    //View(Controller*, Model*);
    virtual ~View();

    // Implementing the methods that the controller calls.
    virtual void AddPlayer(int player);
    virtual void HumanTurn(int player);
    virtual void PlayerWon(int player);


    // Observer pattern - notifications of state changes from model.
    virtual void Model_CardsDealt(std::vector<std::vector<Card*> >);
    virtual void Model_PlayerAdded(bool isHuman, int id);
    virtual void Model_PlayerRageQuitted(int player);
    virtual void Model_CardsCleared();
    virtual void Model_ScoreUpdated(int player, int score);
    virtual void Model_DiscardsCleared(int player);
    virtual void Model_CardPlayed(int player, Card*);
    virtual void Model_CardDiscarded(int player, Card*);

private:
    // Observer Pattern: to access Model accessors without having to downcast subject
    //GameState* mGameState;
    
    // Strategy Pattern member (plus signal handlers)
    GamePlay* mGamePlay;

    // Card Images
    DeckGui* mDeck;

    // Signal Handlers
    virtual void onNewGame();
    virtual void onNewSeed();
    virtual void onQuit();

    // Member Widgets;
    TableVBox mTable;       // This is where all the cards on table is shown
    Gtk::VBox mMenu;
    Gtk::VBox mPanel;       // This is the container for all objects
    HandHBox* mHand[4];
    PlayerInfoBox* mPlayerInfo[4]; // contains info and button for players
    Gtk::HBox mPlayerInfoContainer;

    Glib::RefPtr<Gtk::UIManager> mRefUIManager;
    Glib::RefPtr<Gtk::ActionGroup> mRefActionGroup;
};

#endif
