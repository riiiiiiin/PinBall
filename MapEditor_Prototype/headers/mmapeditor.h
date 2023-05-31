#ifndef MMAPEDITOR_H
#define MMAPEDITOR_H

#include <QPushButton>

#include "mdragcontainer.h"

class MMapEditor:public QWidget{
    Q_OBJECT
private:
    MDragContainer* _container;
    QLabel* _container_back;
    QList<QLabel*> _draggable_containers;
    QList<QPushButton*> _buttons;
public:
    MMapEditor(QWidget* parent=nullptr);
    ~MMapEditor();
};


#endif