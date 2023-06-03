#ifndef MENU_H
#define MENU_H

#include <QDialog>

namespace natsume {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private:
    natsume::menu *ui;
};

#endif // MENU_H
