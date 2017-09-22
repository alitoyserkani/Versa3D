/********************************************************************************
** Form generated from reading UI file 'formtest.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMTEST_H
#define UI_FORMTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormTest
{
public:

    void setupUi(QWidget *FormTest)
    {
        if (FormTest->objectName().isEmpty())
            FormTest->setObjectName(QStringLiteral("FormTest"));
        FormTest->resize(400, 300);

        retranslateUi(FormTest);

        QMetaObject::connectSlotsByName(FormTest);
    } // setupUi

    void retranslateUi(QWidget *FormTest)
    {
        FormTest->setWindowTitle(QApplication::translate("FormTest", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FormTest: public Ui_FormTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMTEST_H
