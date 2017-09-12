#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("Process: Hybrid BJ Process");
    ui->treeWidget->setColumnCount(2);

    QTreeWidgetItem * itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0, "Hello World");
    itm->setText(1, "My name is Ali");
    ui->treeWidget->addTopLevelItem(itm);
    QTreeWidgetItem *itm2 = new QTreeWidgetItem();
    itm2->setText(0,"My homie is ok");
    itm2->setText(1, "Whats happening");
    itm->addChild(itm2);





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    mFilename = "";
    ui->textEdit->setPlainText("");
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Open FIle");

    if (!file.isEmpty()) {
        QFile sFile(file);
        if (sFile.open(QFile::ReadOnly | QFile::Text)) {
            mFilename = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();

            ui->textEdit->setPlainText(text);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QFile sFile(mFilename);
    if (sFile.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&sFile);

        out << ui->textEdit->toPlainText();

        sFile.flush();
        sFile.close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Open FIle");

    if (!file.isEmpty()) {
        mFilename = file;
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_textEdit_textChanged()
{
    //Note: This is an inefficient implementation, change to threading and only looking at changed text and not untouched data ...
    //TODO: have a considtion that only triggers the function at certain times, a delay, or upon completing editing

    QString editorText = ui->textEdit->toPlainText(); //ensure toPlainText() keeps all text entities

    //Right now, for every text change it gets triggered if it exists
//    foreach (const QChar character, editorText) {
//        if (character == "[") {
//            //TODO; Check if left character is a [ as well
//            // Note: want to start this next process in a thread to now slow down actual application processing
//        }
//    }
    for (int i = 0; i < editorText.size(); i++) {
        if (editorText.at(i) == "[") {
            int j = i + 1;
            //optimize this asap-
            QString tempVarName = "";
            while (j < editorText.size() && editorText.at(j) != "]" && j - i < 100 ) { //second condition to not go on forever
                tempVarName += editorText.at(j);
                j++;
            }
            if (j - i > 100) {
                //DO SOMETHING
                qDebug() << "Messed up my dude";
            } else if (j > editorText.size()) {
                qDebug() << "Exceeded";

            } else {
                //Statement for if the close bracket was actually found.
                qDebug() << tempVarName;
            }
        }
    }


}
