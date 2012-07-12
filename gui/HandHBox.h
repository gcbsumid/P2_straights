#ifndef HAND_HBOX
#define HAND_HBOX
#include "RowHBox.h"
#include "../gameplay/Card.h"

class HandHBox : public RowHBox {
public:    
    HandHBox(int, Vector<Card*>);
    ~HandHBox();
    void update();
private:
    void NoLegalPlays();
};

#endif