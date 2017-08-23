/********************************************************************************
** Form generated from reading UI file 'gui_window.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_WINDOW_H
#define UI_GUI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE

class Ui_GUI_Window
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    MainWindow *widget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GUI_Window)
    {
        if (GUI_Window->objectName().isEmpty())
            GUI_Window->setObjectName(QStringLiteral("GUI_Window"));
        GUI_Window->resize(800, 600);
        centralwidget = new QWidget(GUI_Window);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new MainWindow(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout->addWidget(widget);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        GUI_Window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GUI_Window);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        GUI_Window->setMenuBar(menubar);
        statusbar = new QStatusBar(GUI_Window);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        GUI_Window->setStatusBar(statusbar);

        retranslateUi(GUI_Window);

        QMetaObject::connectSlotsByName(GUI_Window);
    } // setupUi

    void retranslateUi(QMainWindow *GUI_Window)
    {
        GUI_Window->setWindowTitle(QApplication::translate("GUI_Window", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("GUI_Window", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GUI_Window: public Ui_GUI_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_WINDOW_H
