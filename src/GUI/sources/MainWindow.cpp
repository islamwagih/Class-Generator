#include "headers\MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // initialize singleton classes
    TreeEditor::init(ui->configTree, ui->statusBar, [this]()
                     { this->stateHandler->saveState(); });
    TreeParser::init(ui->outEdit, ui->classNameEdit, ui->typeComboBox, ui->configTree);
    IntermediateFormatHandler::init(ui->classNameEdit, ui->typeComboBox, ui->configTree);
    StateHandler::init(this->intermediateFormatHandler, this->treeParser, [this]()
                       { this->reset(); });

    // initialize member variables
    this->saveFilePath = "";

    this->treeEditor = TreeEditor::getInstance();
    this->treeParser = TreeParser::getInstance();
    this->intermediateFormatHandler = IntermediateFormatHandler::getInstance();
    this->stateHandler = StateHandler::getInstance();

    this->stateHandler->saveState();

    // Set QValidators
    ui->classNameEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z_][a-zA-Z0-9_]*"), this));
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
    this->stateHandler->saveState();
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
    this->stateHandler->saveState();
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
    this->stateHandler->saveState();
}

void MainWindow::on_removeRowBtn_clicked()
{
    removeRow();
}

void MainWindow::reset()
{
    treeEditor->reset();
    //    ui->outEdit->clear();
    ui->classNameEdit->clear();
    ui->typeComboBox->setCurrentIndex(0);
    this->stateHandler->saveState();
}

void MainWindow::on_resetBtn_clicked()
{
    reset();
}

void MainWindow::on_generateBtn_clicked()
{
    if (ui->classNameEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please enter a class name");
        return;
    }
    if (ui->outEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please choose an output directory");
        return;
    }
    int status = this->treeParser->validateTree(ui->configTree->invisibleRootItem());
    switch (status)
    {
    case TreeParser::VALIDATION_DUPLICATE_NAME:
        QMessageBox::warning(this, "Warning", "Please use unique parameter names");
        break;
    case TreeParser::VALIDATION_EMPTY_FIELD:
        QMessageBox::warning(this, "Warning", "Please fill parameter names");
        break;
    case TreeParser::VALIDATION_SUCCESS:
        Controller::getInstance()->generateClasses(*this->treeParser->parseTree(), ui->outEdit->text().toStdString());
        QMessageBox::information(this, "Success", "Classes generated successfully");
        break;
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (!this->treeParser->checkForDuplicateNames(ui->configTree->invisibleRootItem()))
    {
        QMessageBox::warning(this, "Warning", "Please use unique parameter names");
        return;
    }
    if (this->saveFilePath.isEmpty())
    {
        if (!getSaveFilePath())
        {
            return;
        }
    }
    this->intermediateFormatHandler->saveFile(this->saveFilePath, this->treeParser->parseTree());
}

void MainWindow::on_actionSave_As_triggered()
{
    if (!this->treeParser->checkForDuplicateNames(ui->configTree->invisibleRootItem()))
    {
        QMessageBox::warning(this, "Warning", "Please use unique parameter names");
        return;
    }
    if (!getSaveFilePath())
        return;
    this->intermediateFormatHandler->saveFile(this->saveFilePath, this->treeParser->parseTree());
}

bool MainWindow::getSaveFilePath()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "JSON File (*.json)");
    if (filePath.isEmpty())
        return false;
    this->saveFilePath = filePath;
    return true;
}

void MainWindow::on_actionLoad_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", "", "JSON File (*.json)");
    if (filePath.isEmpty())
        return;
    this->stateHandler->setLoadingState(true);
    if (!this->intermediateFormatHandler->loadFile(filePath))
    {
        QMessageBox::warning(this, "Warning", "Invalid File");
        this->stateHandler->setLoadingState(false);
        return;
    }
    this->stateHandler->setLoadingState(false);
    this->stateHandler->saveState();
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

void MainWindow::on_outBrowseBtn_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select Output Directory", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (dir.isEmpty())
        return;
    ui->outEdit->setText(dir);
    // this->stateHandler->saveState();
}

void MainWindow::on_actionUndo_triggered()
{
    this->stateHandler->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    this->stateHandler->redo();
}

void MainWindow::on_typeComboBox_currentIndexChanged(int index)
{
    this->stateHandler->saveState();
}

void MainWindow::on_classNameEdit_textEdited(const QString &arg1)
{
    this->stateHandler->saveState();
}

MainWindow::~MainWindow()
{
    delete ui;
}
