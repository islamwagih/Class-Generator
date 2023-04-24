#include "..\headers\MainWindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QPropertyAnimation>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TreeEditor::init(ui->configTree);
    this->treeEditor = TreeEditor::getInstance();
    this->intermediateFormatHandler = new IntermediateFormatHandler(ui->configTree);
}

void MainWindow::insertChild()
{
    QTreeWidgetItem *item = ui->configTree->currentItem();
    if (item)
    {
        int count = item->childCount();
        static_cast<QComboBox *>(ui->configTree->itemWidget(item, 1))->setCurrentText("nested");
        // If child count increased after changing combobox text, remove the last child.
        // This is done because choosing nested from the combobox calls makeRow() function
        // And this function already inserts a row into the tree.
        // So we delete the last row to avoid duplicates
        if (item->childCount() == count + 1)
        {
            item->takeChild(item->childCount() - 1);
        }
    }
    else
    {
        // if no item is selected, insert a row into the root of the tree
        item = ui->configTree->invisibleRootItem();
    }
    treeEditor->makeRow(item);
}

void MainWindow::on_insertChildBtn_clicked()
{
    insertChild();
}

void MainWindow::insertRow()
{
    QTreeWidgetItem *item = ui->configTree->currentItem();
    if (item)
    {
        // get the parent of the selected item
        item = item->parent();
        if (item)
        {
            // if the selected item has a parent, insert a row into the parent
            treeEditor->makeRow(item);
        }
        else
        {
            // if the selected item has no parent, insert a row into the root of the tree
            item = ui->configTree->invisibleRootItem();
            treeEditor->makeRow(item);
        }
    }
    else
    {
        // if no item is selected, insert a row into the root of the tree
        item = ui->configTree->invisibleRootItem();
        treeEditor->makeRow(item);
    }
}

void MainWindow::on_insertRowBn_clicked()
{
    insertRow();
}

void MainWindow::removeRow()
{
    QTreeWidgetItem *item = ui->configTree->currentItem();
    if (item)
    {
        treeEditor->removeRow(item);
    }
}

void MainWindow::on_removeRowBtn_clicked()
{
    removeRow();
}

void MainWindow::reset()
{
    treeEditor->reset();
}

void MainWindow::on_resetBtn_clicked()
{
    reset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSave_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "JSON File (*.json)");
    if (filePath.isEmpty())
        return;
    this->intermediateFormatHandler->saveFile(filePath);
}

void MainWindow::on_actionLoad_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", "", "JSON File (*.json)");
    if (filePath.isEmpty())
        return;
    this->intermediateFormatHandler->loadFile(filePath);
}

void MainWindow::on_actionInsert_Child_triggered()
{
    insertChild();
}

void MainWindow::on_actionInsert_Row_triggered()
{
    insertRow();
}

void MainWindow::on_actionRemove_Row_triggered()
{
    removeRow();
}

void MainWindow::on_actionReset_triggered()
{
    reset();
}
