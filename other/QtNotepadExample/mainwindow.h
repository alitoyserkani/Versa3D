#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    struct PropertyVariable {
        QString name;
        QString value;
        int frequency;
    };


private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionCopy_triggered();

    void on_actionSave_As_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionPaste_triggered();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    QString mFilename;

    // These two lists must work together
    QList<PropertyVariable> propertiesList;
    QList<QString> infoList;
};

#endif // MAINWINDOW_H
