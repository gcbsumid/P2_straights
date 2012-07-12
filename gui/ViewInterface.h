#ifndef VIEW_INTERFACE
#define VIEW_INTERFACE

// Contract that the view needs to implement. Used by the controller when it needs the view to do stuff.
class ViewInterface {
public:
    void HumanTurn(int player);
    void PlayerWon(int player);
};

#endif
