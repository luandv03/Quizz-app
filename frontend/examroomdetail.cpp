// frontend/sources/examroomdetail.cpp
#include "examroomdetail.h"
#include "ui_examroomdetail.h"
#include <QMenu>
#include <QAction>

ExamRoomDetail::ExamRoomDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamRoomDetail)
{
    ui->setupUi(this);

    // Set up the avatar button dropdown menu
    QMenu *menu = new QMenu(this);
    QAction *examRoomListAction = new QAction("Exam Room List", this);
    QAction *profileAction = new QAction("Profile", this);
    QAction *practicesAction = new QAction("Logout", this);

    menu->addAction(examRoomListAction);
    menu->addAction(profileAction);
    menu->addAction(practicesAction);

    ui->avatarButton->setMenu(menu);
}

ExamRoomDetail::~ExamRoomDetail()
{
    delete ui;
}
