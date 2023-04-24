#include "../headers/TreeEditor.h"
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QHeaderView>

TreeEditor::TreeEditor(QTreeWidget *tree) : tree(tree)
{
    // make all headers in the treewidget stretch to fill the available space and make them resizable by the user
    for (int i = 0; i < tree->columnCount() - 1; ++i)
    {
        tree->header()->setSectionResizeMode(i, QHeaderView::Interactive);
        tree->header()->resizeSection(i, 200);
    }
    tree->header()->setSectionResizeMode(tree->columnCount() - 1, QHeaderView::Stretch);
    // center the text in the header
    tree->header()->setDefaultAlignment(Qt::AlignCenter);
}

void TreeEditor::onComboboxChanged(QTreeWidgetItem *item)
{
    // get the value from the combobox
    QString value = static_cast<QComboBox *>(this->tree->itemWidget(item, 1))->currentText();
    if (value == QString("int") || value == QString("float"))
    {
        // make the third column hold 2 lineedits
        QWidget *widget = new QWidget(this->tree);
        QHBoxLayout *layout = new QHBoxLayout(widget);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(new QLineEdit(this->tree));
        layout->addWidget(new QLineEdit(this->tree));
        this->tree->setItemWidget(item, 2, widget);
    }
    else if (value == QString("string"))
    {
        // make the third column hold 1 lineedit
        QWidget *widget = new QWidget(this->tree);
        QHBoxLayout *layout = new QHBoxLayout(widget);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(new QLineEdit(this->tree));
        this->tree->setItemWidget(item, 2, widget);
    }
    else if (value == QString("bool") || value == QString("nested"))
    {
        // make the third column hold 1 disabled lineedit
        QWidget *widget = new QWidget(this->tree);
        QHBoxLayout *layout = new QHBoxLayout(widget);
        layout->setContentsMargins(0, 0, 0, 0);
        QLineEdit *line = new QLineEdit(this->tree);
        line->setDisabled(true);
        layout->addWidget(line);
        this->tree->setItemWidget(item, 2, widget);
    }
    if (value == QString("nested"))
    {
        // if the user selects "nested", insert a row into the tree
        this->makeRow(item);
        this->tree->expandItem(item);
    }
    else
    {
        // if the user selects anything else, remove all the children of the current item
        item->takeChildren();
    }
};

void TreeEditor::makeRow(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    // insert a row into the tree
    parent->addChild(item);
    this->tree->setItemWidget(item, 0, new QLineEdit(this->tree));
    QComboBox *box = new QComboBox(this->tree);
    box->addItems(this->paramTypes);
    QObject::connect(box, QOverload<int>::of(&QComboBox::currentIndexChanged), [this, item](int index)
                     { this->onComboboxChanged(item); });
    this->tree->setItemWidget(item, 1, box);
    // make the third column hold horizontal layout with a lineedit and a lineedit. Don't put any vertical margins between the layout and the cell it is in
    QWidget *widget = new QWidget(this->tree);
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new QLineEdit(this->tree));
    layout->addWidget(new QLineEdit(this->tree));
    this->tree->setItemWidget(item, 2, widget);
    this->tree->expandItem(item);
}

void TreeEditor::removeRow(QTreeWidgetItem *item)
{
    // remove the row from the tree
    delete item;
}

TreeEditor::~TreeEditor() {}
