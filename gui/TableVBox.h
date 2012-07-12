#ifndef TABLE_VBOX
#define TABLE_VBOX

#include <gtkmm/VBox>
#include <gtkmm/HBox>
#include "RowHBox.h"

class RowHBox;

class TableVBox : public Gtk::VBox {
public:
    TableVBox(int);
    ~TableVBox();
    void update();

private:
    RowHBox* mSuits[4];
};

#endif