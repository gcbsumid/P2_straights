#ifndef VIEW_INTERFACE
#define VIEW_INTERFACE

// Contract that the view needs to implement. Used by the controller when it needs the view to do stuff.
class ViewInterface {
public:
    // Prompt the user to add a player.
    virtual void AddPlayer(int player) = 0;

    // Wait for the human to take their turn.
    virtual void HumanTurn(int player) = 0;
};

#endif
