#include "..\headers\mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QPropertyAnimation>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // make all headers in the treewidget stretch to fill the available space and make them resizable by the user
    for (int i = 0; i < ui->configTree->columnCount() - 1; ++i)
    {
        ui->configTree->header()->setSectionResizeMode(i, QHeaderView::Interactive);
        ui->configTree->header()->resizeSection(i, 200);
    }
    ui->configTree->header()->setSectionResizeMode(ui->configTree->columnCount() - 1, QHeaderView::Stretch);
    // center the text in the header
    ui->configTree->header()->setDefaultAlignment(Qt::AlignCenter);
}

void MainWindow::makeRow(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    // insert a row into the tree
    ui->configTree->insertTopLevelItem(0, item);
    ui->configTree->setItemWidget(item, 0, new QLineEdit(this));
    // put the values "int", "float", "string", "bool" into the combobox
    QComboBox *box = new QComboBox(this);
    box->addItem("int");
    box->addItem("float");
    box->addItem("string");
    box->addItem("bool");
    // connect the combobox to the slot that will be called when the user selects a value from the combobox. store the function in a lambda function
    auto slot = [this, item]()
    {
        // get the value from the combobox
        QString value = static_cast<QComboBox *>(ui->configTree->itemWidget(item, 1))->currentText();
        if (value == QString("int") || value == QString("float"))
        {
            // make the third column hold 2 lineedits
            QWidget *widget = new QWidget(this);
            QHBoxLayout *layout = new QHBoxLayout(widget);
            layout->setContentsMargins(0, 0, 0, 0);
            layout->addWidget(new QLineEdit(this));
            layout->addWidget(new QLineEdit(this));
            ui->configTree->setItemWidget(item, 2, widget);
        }
        else if (value == QString("string"))
        {
            // make the third column hold 1 lineedit
            QWidget *widget = new QWidget(this);
            QHBoxLayout *layout = new QHBoxLayout(widget);
            layout->setContentsMargins(0, 0, 0, 0);
            layout->addWidget(new QLineEdit(this));
            ui->configTree->setItemWidget(item, 2, widget);
        }
        else if (value == QString("bool") || value == QString("nested"))
        {
            // make the third column hold 1 disabled lineedit
            QWidget *widget = new QWidget(this);
            QHBoxLayout *layout = new QHBoxLayout(widget);
            layout->setContentsMargins(0, 0, 0, 0);
            QLineEdit *line = new QLineEdit(this);
            line->setDisabled(true);
            layout->addWidget(line);
            ui->configTree->setItemWidget(item, 2, widget);
        }
    };
    // connect the combobox to the slot
    connect(box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), slot);
    ui->configTree->setItemWidget(item, 1, box);
    // make the third column hold horizontal layout with a lineedit and a lineedit. Don't put any vertical margins between the layout and the cell it is in
    QWidget *widget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new QLineEdit(this));
    layout->addWidget(new QLineEdit(this));
    ui->configTree->setItemWidget(item, 2, widget);
}

void MainWindow::on_insertChildBtn_clicked()
{
    QTreeWidgetItem *item = ui->configTree->currentItem();
    if (item)
    {
        ui->configTree->itemWidget(item, 1)->setEnabled(false);
        static_cast<QComboBox *>(ui->configTree->itemWidget(item, 1))->addItem("nested");
        static_cast<QComboBox *>(ui->configTree->itemWidget(item, 1))->setCurrentText("nested");
    }
    else
    {
        // if no item is selected, insert a row into the root of the tree
        item = ui->configTree->invisibleRootItem();
    }
    makeRow(item);
    ui->configTree->expandItem(item);
}

MainWindow::~MainWindow()
{
    delete ui;
}
