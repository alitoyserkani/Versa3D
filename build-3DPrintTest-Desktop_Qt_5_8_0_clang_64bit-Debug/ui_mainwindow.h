/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "canvas.h"
#include "layerdraw.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    Canvas *stl_viewer;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QHBoxLayout *horizontalLayout_4;
    LayerDraw *svg_viewer;
    QLabel *thicknessLabel;
    QWidget *tab_5;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *layerNum_label;
    QLineEdit *lineEdit;
    QSlider *verticalSlider;
    QTabWidget *tabWidget_2;
    QWidget *machine_tab;
    QLabel *systemImage;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QLabel *machineLabel;
    QLabel *processLabel;
    QWidget *tab_3;
    QWidget *tab_4;
    QWidget *tab;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1004, 640);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1004, 600));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        stl_viewer = new Canvas(centralWidget);
        stl_viewer->setObjectName(QStringLiteral("stl_viewer"));
        stl_viewer->setMinimumSize(QSize(600, 500));

        horizontalLayout_2->addWidget(stl_viewer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_3->addWidget(pushButton);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(layoutWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(325, 100));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        horizontalLayout_4 = new QHBoxLayout(tab_1);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        svg_viewer = new LayerDraw(tab_1);
        svg_viewer->setObjectName(QStringLiteral("svg_viewer"));
        svg_viewer->setMinimumSize(QSize(310, 0));
        svg_viewer->setAutoFillBackground(false);
        thicknessLabel = new QLabel(svg_viewer);
        thicknessLabel->setObjectName(QStringLiteral("thicknessLabel"));
        thicknessLabel->setGeometry(QRect(180, 0, 121, 20));
        QFont font;
        font.setPointSize(10);
        thicknessLabel->setFont(font);

        horizontalLayout_4->addWidget(svg_viewer);

        tabWidget->addTab(tab_1, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        tabWidget->addTab(tab_5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        layerNum_label = new QLabel(layoutWidget);
        layerNum_label->setObjectName(QStringLiteral("layerNum_label"));
        layerNum_label->setFont(font);

        verticalLayout->addWidget(layerNum_label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setFont(font);

        verticalLayout->addWidget(lineEdit);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSlider = new QSlider(layoutWidget);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setMouseTracking(true);
        verticalSlider->setToolTipDuration(1);
        verticalSlider->setLayoutDirection(Qt::RightToLeft);
        verticalSlider->setMinimum(1);
        verticalSlider->setMaximum(100);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setInvertedAppearance(false);
        verticalSlider->setInvertedControls(false);
        verticalSlider->setTickPosition(QSlider::TicksBothSides);

        verticalLayout_2->addWidget(verticalSlider);


        horizontalLayout->addLayout(verticalLayout_2);

        splitter->addWidget(layoutWidget);
        tabWidget_2 = new QTabWidget(splitter);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setTabShape(QTabWidget::Rounded);
        machine_tab = new QWidget();
        machine_tab->setObjectName(QStringLiteral("machine_tab"));
        systemImage = new QLabel(machine_tab);
        systemImage->setObjectName(QStringLiteral("systemImage"));
        systemImage->setGeometry(QRect(10, 10, 61, 51));
        layoutWidget1 = new QWidget(machine_tab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(90, 10, 216, 40));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        machineLabel = new QLabel(layoutWidget1);
        machineLabel->setObjectName(QStringLiteral("machineLabel"));

        verticalLayout_4->addWidget(machineLabel);

        processLabel = new QLabel(layoutWidget1);
        processLabel->setObjectName(QStringLiteral("processLabel"));

        verticalLayout_4->addWidget(processLabel);

        tabWidget_2->addTab(machine_tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget_2->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget_2->addTab(tab, QString());
        splitter->addWidget(tabWidget_2);

        verticalLayout_3->addWidget(splitter);


        horizontalLayout_2->addLayout(verticalLayout_3);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1004, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(tabWidget_2, pushButton);
        QWidget::setTabOrder(pushButton, tabWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Generate Machine Code", Q_NULLPTR));
        thicknessLabel->setText(QApplication::translate("MainWindow", "Layer Thickness:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MainWindow", "Slice", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Infill", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Raster", Q_NULLPTR));
        layerNum_label->setText(QApplication::translate("MainWindow", "Layer #", Q_NULLPTR));
        lineEdit->setText(QString());
        systemImage->setText(QString());
        machineLabel->setText(QApplication::translate("MainWindow", "Machine: MSAM Research Platform", Q_NULLPTR));
        processLabel->setText(QApplication::translate("MainWindow", "Process: Hybrid Silicone AM ", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(machine_tab), QApplication::translate("MainWindow", "Machine", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("MainWindow", "Machine Settings", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("MainWindow", "Output", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab), QApplication::translate("MainWindow", "Scripting", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
