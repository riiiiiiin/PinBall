#include "headers/mmapeditor.h"

MMapEditor::MMapEditor(QWidget* parent):QWidget(parent){
    setGeometry(0, 0, 960, 540);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);

    _container_back = new QLabel(this);
    _container_back->setText("");
    _container_back->setGeometry(650, 40, 260, 380);
    _container_back->setAutoFillBackground(true);
    _container_back->setFixedSize(260, 380);
    _container_back->setStyleSheet("background-color:rgba(255,255,255,128);border-radius:15px;border: 1px solid silver;");

    _draggable_containers.resize(6);
    for (int i = 0; i < 6; ++i)
    {
        _draggable_containers[i] = new QLabel(this);
        _draggable_containers[i]->setFixedSize(110, 110);
        _draggable_containers[i]->setText("");
        _draggable_containers[i]->setStyleSheet("background-color:rgba(255,255,255,154);border-radius: 10px;border: 1px solid royalblue;");
        _draggable_containers[i]->setAutoFillBackground(true);
    }
    _draggable_containers[0]->setGeometry(670-5, 60-5, 110, 110);
    _draggable_containers[1]->setGeometry(670-5, 180-5, 110, 110);
    _draggable_containers[2]->setGeometry(790-5, 60-5, 110, 110);
    _draggable_containers[3]->setGeometry(790-5, 180-5, 110, 110);
    _draggable_containers[4]->setGeometry(670-5,300-5,110,110);
    _draggable_containers[5]->setGeometry(790-5,300-5,110,110);

    _buttons.resize(2);
    for(int i=0;i<2;++i){
        _buttons[i] = new QPushButton(this);
    }

    _buttons[0]->setGeometry(675,440,110,50);
    _buttons[0]->setText("Play");
    _buttons[0]->setStyleSheet("QPushButton {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
    "QPushButton{background-image: url(:/new/prefix3/play_button_inactive.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
    "QPushButton{font-size:30px;color:#808080;font-family: \"Segoe UI\";}"
    "QPushButton{background-color:transparent;}"
    "QPushButton:hover {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
    "QPushButton:hover{background-image: url(:/new/prefix3/play_button_active.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
    "QPushButton:hover{font-size:30px;color:#fefefe;font-family: \"Segoe UI\";}"
    "QPushButton:hover{background-color:transparent;}");

    _buttons[1]->setGeometry(790,442,130,50);
    _buttons[1]->setText("Menu");
    _buttons[1]->setStyleSheet("QPushButton {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
    "QPushButton{background-image: url(:/new/prefix3/menu_button_inactive.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
    "QPushButton{font-size:30px;color:#808080;font-family: \"Segoe UI\";}"
    "QPushButton{background-color:transparent;}"
    "QPushButton:hover {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
    "QPushButton:hover{background-image: url(:/new/prefix3/menu_button_active.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
    "QPushButton:hover{font-size:30px;color:#fefefe;font-family: \"Segoe UI\";}"
    "QPushButton:hover{background-color:transparent;}");

    _container=new MDragContainer(this);
}

MMapEditor::~MMapEditor(){
    delete _container_back;
    for (auto ptr : _draggable_containers)
    {
        delete ptr;
    }
    for(auto ptr:_buttons){
        delete ptr;
    }
}