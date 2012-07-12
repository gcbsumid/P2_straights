#ifndef VIEW_INTERFACE
#define VIEW_INTERFACE

// Contract that the view needs to implement. Used by the controller when it needs the view to do stuff.
class ViewInterface {
public:
    virtual void HumanTurn(int player) = 0;
    virtual void PlayerWon(int player) = 0;
};

#endif
