#include "..\headers\mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QPropertyAnimation>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    treeEditor = new TreeEditor(ui->configTree);
}

void MainWindow::on_insertChildBtn_clicked()
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

MainWindow::~MainWindow()
{
    delete ui;
}
