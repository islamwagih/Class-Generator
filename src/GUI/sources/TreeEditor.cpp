#include "../headers/TreeEditor.h"
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QHeaderView>

TreeEditor *TreeEditor::instance = nullptr;

TreeEditor::TreeEditor(QTreeWidget *tree, QStatusBar *statusBar)
{
    this->tree = tree;
    this->statusBar = statusBar;
    // make all headers in the treewidget stretch to fill the available space and make them resizable by the user
    for (int i = 0; i < tree->columnCount() - 1; ++i)
    {
        tree->header()->setSectionResizeMode(i, QHeaderView::Interactive);
        tree->header()->resizeSection(i, 300);
    }
    tree->header()->setSectionResizeMode(tree->columnCount() - 1, QHeaderView::Stretch);
    // center the text in the header
    tree->header()->setDefaultAlignment(Qt::AlignCenter);
}

void TreeEditor::init(QTreeWidget *tree, QStatusBar *statusBar)
{
    instance = new TreeEditor(tree, statusBar);
}

TreeEditor *TreeEditor::getInstance()
{
    if (instance == nullptr)
    {
        throw std::runtime_error("TreeEditor instance not initialized");
    }
    return instance;
}

void TreeEditor::onComboboxChanged(QTreeWidgetItem *item)
{
    this->createConstraintLineEdits(item);
    this->setLineEditsValidator(item);
};

void TreeEditor::createConstraintLineEdits(QTreeWidgetItem *item)
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
    if (value != QString("nested"))
    {
        // if the user selects anything other than nested, remove all the children of the current item
        item->takeChildren();
    }
}

#include <QDebug>
void TreeEditor::setLineEditsValidator(QTreeWidgetItem *item)
{
    // set validator of line edit in first column to any strings
    static_cast<QLineEdit *>(this->tree->itemWidget(item, 0))->setValidator(new QRegExpValidator(QRegExp(".*"), this->tree));
    // get the value from the combobox
    QString value = static_cast<QComboBox *>(this->tree->itemWidget(item, 1))->currentText();
    auto layout = static_cast<QHBoxLayout *>(this->tree->itemWidget(item, 2)->layout());
    if (value == QString("int"))
    {
        auto lineEdit1 = static_cast<QLineEdit *>(layout->itemAt(0)->widget());
        lineEdit1->setProperty("validator", QVariant::fromValue<QValidator *>(new QIntValidator(this->tree)));
        QObject::connect(static_cast<QLineEdit *>(layout->itemAt(0)->widget()), &QLineEdit::textChanged, [this, lineEdit1]()
                         { this->handleValidator(lineEdit1, lineEdit1->text()); });

        auto lineEdit2 = static_cast<QLineEdit *>(layout->itemAt(1)->widget());
        lineEdit2->setProperty("validator", QVariant::fromValue<QValidator *>(new QIntValidator(this->tree)));
        QObject::connect(static_cast<QLineEdit *>(layout->itemAt(1)->widget()), &QLineEdit::textChanged, [this, lineEdit2]()
                         { this->handleValidator(lineEdit2, lineEdit2->text()); });
    }
    else if (value == QString("float"))
    {
        auto lineEdit1 = static_cast<QLineEdit *>(layout->itemAt(0)->widget());
        lineEdit1->setProperty("validator", QVariant::fromValue<QValidator *>(new QDoubleValidator(this->tree)));
        QObject::connect(static_cast<QLineEdit *>(layout->itemAt(0)->widget()), &QLineEdit::textChanged, [this, lineEdit1]()
                         { this->handleValidator(lineEdit1, lineEdit1->text()); });

        auto lineEdit2 = static_cast<QLineEdit *>(layout->itemAt(1)->widget());
        lineEdit2->setProperty("validator", QVariant::fromValue<QValidator *>(new QDoubleValidator(this->tree)));
        QObject::connect(static_cast<QLineEdit *>(layout->itemAt(1)->widget()), &QLineEdit::textChanged, [this, lineEdit2]()
                         { this->handleValidator(lineEdit2, lineEdit2->text()); });
    }
    else if (value == QString("string"))
    {
        auto lineEdit = static_cast<QLineEdit *>(layout->itemAt(0)->widget());
        lineEdit->setProperty("validator", QVariant::fromValue<QValidator *>(new QRegExpValidator(QRegExp(".*"), this->tree)));
        QObject::connect(static_cast<QLineEdit *>(layout->itemAt(0)->widget()), &QLineEdit::textChanged, [this, lineEdit]()
                         { this->handleValidator(lineEdit, lineEdit->text()); });
    }
}

QTreeWidgetItem *TreeEditor::makeRow(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    // insert a row into the tree
    parent->addChild(item);
    this->tree->setItemWidget(item, 0, new QLineEdit(this->tree));
    QComboBox *box = new QComboBox(this->tree);
    QObject::connect(box, QOverload<int>::of(&QComboBox::currentIndexChanged), [this, item](int index)
                     { this->onComboboxChanged(item); });
    this->tree->setItemWidget(item, 1, box);
    box->addItems(this->paramTypes);
    this->tree->expandItem(item);
    return item;
}

QTreeWidgetItem *TreeEditor::makeRow(QTreeWidgetItem *parent, QString name, QString type, QPair<QString, QString> constraints)
{
    auto item = this->makeRow(parent);
    static_cast<QLineEdit *>(this->tree->itemWidget(item, 0))->setText(name);
    static_cast<QComboBox *>(this->tree->itemWidget(item, 1))->setCurrentText(type);
    if (type == QString("int") || type == QString("float"))
    {
        auto lineEdit1 = static_cast<QLineEdit *>(static_cast<QHBoxLayout *>(this->tree->itemWidget(item, 2)->layout())->itemAt(0)->widget());
        if (this->handleValidator(lineEdit1, constraints.first))
        {
            lineEdit1->setText(constraints.first);
        }
        else
        {
            throw std::invalid_argument("Invalid value for min constraint");
        }
        auto lineEdit2 = static_cast<QLineEdit *>(static_cast<QHBoxLayout *>(this->tree->itemWidget(item, 2)->layout())->itemAt(1)->widget());
        if (this->handleValidator(lineEdit2, constraints.second))
        {
            lineEdit2->setText(constraints.second);
        }
        else
        {
            throw std::invalid_argument("Invalid value for max constraint");
        }
    }
    else if (type == QString("string"))
    {
        static_cast<QLineEdit *>(static_cast<QHBoxLayout *>(this->tree->itemWidget(item, 2)->layout())->itemAt(0)->widget())->setText(constraints.first);
    }
    else if (type == QString("nested"))
    {
        item->takeChildren();
    }
    return item;
}

void TreeEditor::removeRow(QTreeWidgetItem *item)
{
    delete item;
}

void TreeEditor::reset()
{
    this->tree->clear();
}

bool TreeEditor::handleValidator(QLineEdit *edit, QString text)
{
    // retrieve the qintvalidator or the qdoublevalidator from the validator property of the lineedit
    auto validator = edit->property("validator").value<QValidator *>();
    int temp = 0;
    if (validator->validate(text, temp) == QValidator::Acceptable)
    {
        qDebug() << "valid";
        this->displayMessageOnStatusBar(QString(""), 0);
        return true;
    }
    else
    {
        // if text is "-" and the cursor is at second character, do nothing
        if ((text == QString("-") || text == QString("+")) && edit->cursorPosition() == 1)
        {
            qDebug() << "special case";
            this->displayMessageOnStatusBar(QString(""), 0);
            return true;
        }
        qDebug() << "invalid";
        // get the cursor position
        int pos = edit->cursorPosition();
        // remove the character behind the cursor
        // block signals to prevent infinite recursion
        edit->blockSignals(true);
        edit->setText(text.remove(pos - 1, 1));
        edit->blockSignals(false);
        // set the cursor position to the previous position
        edit->setCursorPosition(pos - 1);
        this->displayMessageOnStatusBar(QString("Invalid value"), 2000);
        return false;
    }
}

void TreeEditor::displayMessageOnStatusBar(QString message, int timeout)
{
    this->statusBar->showMessage(message, timeout);
}

TreeEditor::~TreeEditor()
{
}
