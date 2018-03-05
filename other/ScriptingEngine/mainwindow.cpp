#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treeview.h"
//#include "process.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TreeView * variableTreeView = new TreeView();
    TreeView * stepTreeView = new TreeView();
    ui->treeView->setModel(variableTreeView);
    ui->treeView_2->setModel(stepTreeView);

    editTriggered = false;
    currentProcess = NULL;

    updateActions();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertChild()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeView->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
    }

    ui->treeView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
    updateActions();
}

bool MainWindow::insertColumn()
{
    QAbstractItemModel *model = ui->treeView->model();
    int column = ui->treeView->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

    updateActions();

    return changed;
}

void MainWindow::insertRow()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeView->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
    }
}

bool MainWindow::removeColumn()
{
    QAbstractItemModel *model = ui->treeView->model();
    int column = ui->treeView->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    bool changed = model->removeColumn(column);

    if (changed)
        updateActions();

    return changed;
}

void MainWindow::removeRow()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeView->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void MainWindow::updateActions()
{
//    bool hasSelection = !ui->treeView->selectionModel()->selection().isEmpty();

//    //change back to signals and slots
//    removeRowAction->setEnabled(hasSelection);
//    removeColumnAction->setEnabled(hasSelection);

//    bool hasCurrent = ui->treeView->selectionModel()->currentIndex().isValid();
//    insertRowAction->setEnabled(hasCurrent);1
//    insertColumnAction->setEnabled(hasCurrent);

//    if (hasCurrent) {
//        view->closePersistentEditor(view->selectionModel()->currentIndex());

//        int row = ui->treeView->selectionModel()->currentIndex().row();
//        int column = ui->selectionModel()->currentIndex().column();
//        if (ui->treeView->selectionModel()->currentIndex().parent().isValid())
//            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
//        else
//            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    //    }
}

void MainWindow::removeAllTreeView()
{
    ui->treeView->model()->removeRows(0,ui->treeView->model()->rowCount());

}

void MainWindow::addStepToProcess()
{
    QModelIndex index = ui->treeView_2->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeView_2->model();

    if (!model->insertRow(model->rowCount(index.parent()), index.parent()))
        return;

    updateActions();

    //TODOOOOOOO
    QModelIndex col1 = model->index(model->rowCount(index.parent()) - 1,
                                                    0, index.parent());
    QModelIndex col2 = model->index(model->rowCount(index.parent()) - 1,
                                                    1, index.parent());
    model->setData(col1, QVariant("Step 1"), Qt::EditRole);
    model->setData(col2, QVariant("Description"), Qt::EditRole);



//    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
//        QModelIndex child = model->index(index.row()+1, column, index.parent());
//        model->setData(child, QVariant("[No data]"), Qt::EditRole);
//        qDebug() << "colomn";
//    }

}

void MainWindow::on_textEdit_textChanged()
{
   // ui->textEdit->textCursor()
   //qDebug() << ui->textEdit->textCursor().position();

   //Simple for now: Parse through entire document --> optimize with position later
   //Very inneficient
    if (editTriggered) {
        QVector<InputVariable> inputVariables;
        QString textDocument = ui->textEdit->toPlainText();
        int sentinelCount = 0;
        for (int i = 0; i < textDocument.length(); i++) {
            if (textDocument.at(i) == '[') {
                sentinelCount++;
                InputVariable temp; temp.variableName = "";
                inputVariables.push_back(temp);

            } else if (textDocument.at(i) == ']') {
                sentinelCount = (sentinelCount < 0) ? 0 : sentinelCount - 1;
            }

            if (sentinelCount > 0) {
                if (textDocument.at(i) != '[' && textDocument.at(i) != ']')
                     inputVariables.last().variableName += textDocument.at(i);
            }
        }
        //qDebug() << inputVariables;

        for (int i = 0; i < inputVariables.size(); i++) {
            if (!ui->treeView->model()->hasIndex(i, 0)) {
                insertRow();
            }
            QModelIndex insertion = ui->treeView->model()->index(i,0,ui->treeView->selectionModel()->currentIndex().parent());
            ui->treeView->model()->setData(insertion, QVariant(inputVariables.at(i).variableName), Qt::EditRole);
        }
        //move later
        if (currentProcess) {
            qDebug() << inputVariables.size();
            for (int i = 0; i < inputVariables.size(); i++)
                if (i < currentProcess->buildSteps.last().sequenceSteps.at(0).stepVariables.size())
                    currentProcess->buildSteps.last().sequenceSteps.first().stepVariables.value(i) = inputVariables.value(i);
                else
                    currentProcess->buildSteps.last().sequenceSteps.first().stepVariables.push_back(inputVariables.value(i));

            for (int z = 0; z < currentProcess->buildSteps.last().sequenceSteps.size(); z++) {
                qDebug() << currentProcess->buildSteps.last().sequenceSteps.first().stepVariables.at(z).variableName;
            }
        }



    }

}

//edit
void MainWindow::on_pushButton_clicked()
{
    if (!editTriggered) {
        editTriggered = true;
        ui->pushButton->setText("End Editing");
        ui->pushButton_2->setText("Add Step");
        ui->pushButton_3->setText("Save"); //for now index that is slicked on
        ui->statusBar->showMessage("Edit Mode Active");

        //load process OR create new process
        currentProcess = new Process();
    } else {
        //add saving step here

        editTriggered = false;
        ui->pushButton->setText("Edit");
        ui->pushButton_2->setText("Open");
        ui->pushButton_3->setText("New");
        ui->statusBar->showMessage("View Mode Active");
    }
}

//open-addstep
void MainWindow::on_pushButton_2_clicked()
{
    //see previously saved processes
    if (!editTriggered) {


    //add step
    } else {
        ui->textEdit->clear();
        removeAllTreeView();
        addStepToProcess();
    }
}

//new-save
void MainWindow::on_pushButton_3_clicked()
{
    if (!editTriggered) {
        //file dialogs are here
    } else {
        //save the template text file
    }

}
