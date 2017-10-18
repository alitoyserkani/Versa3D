#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treeview.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TreeView * customTreeView = new TreeView();
    ui->treeView->setModel(customTreeView);


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

void MainWindow::on_textEdit_textChanged()
{
   // ui->textEdit->textCursor()
   //qDebug() << ui->textEdit->textCursor().position();

   //Simple for now: Parse through entire document --> optimize with position later
   //Very inneficient

   QVector<QString> inputVariables;
   QString textDocument = ui->textEdit->toPlainText();
   int sentinelCount = 0;
   for (int i = 0; i < textDocument.length(); i++) {
       if (textDocument.at(i) == '[') {
           sentinelCount++;
           inputVariables.push_back(QString(""));
       } else if (textDocument.at(i) == ']') {
           sentinelCount = (sentinelCount < 0) ? 0 : sentinelCount - 1;
       }

       if (sentinelCount > 0) {
           if (textDocument.at(i) != '[' && textDocument.at(i) != ']')
                inputVariables.back() += textDocument.at(i);
       }
   }
   qDebug() << inputVariables;

   for (int i = 0; i < inputVariables.size(); i++) {
       if (!ui->treeView->model()->hasIndex(i, 0)) {
           insertRow();
       }
       QModelIndex insertion = ui->treeView->model()->index(i,0,ui->treeView->selectionModel()->currentIndex().parent());
       ui->treeView->model()->setData(insertion, QVariant(inputVariables.at(i)), Qt::EditRole);
   }

}

void MainWindow::on_pushButton_clicked()
{
    insertRow();
}
