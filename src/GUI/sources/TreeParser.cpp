#include "headers/TreeParser.h"

TreeParser *TreeParser::instance = nullptr;

TreeParser::TreeParser(QLineEdit *outDir, QLineEdit *className, QComboBox *fileType, QTreeWidget *tree)
    : outDir(outDir), className(className), fileType(fileType), tree(tree)
{
}

void TreeParser::init(QLineEdit *outDir, QLineEdit *className, QComboBox *fileType, QTreeWidget *tree)
{
    if (instance == nullptr)
    {
        instance = new TreeParser(outDir, className, fileType, tree);
    }
}

TreeParser *TreeParser::getInstance()
{
    if (instance == nullptr)
    {
        throw std::runtime_error("TreeParser instance not initialized");
    }
    return instance;
}

int TreeParser::validateTree(QTreeWidgetItem *item)
{
    if (!this->checkForEmptyFields(item))
        return VALIDATION_EMPTY_FIELD;
    if (!this->checkForDuplicateNames(item))
        return VALIDATION_DUPLICATE_NAME;
    return VALIDATION_SUCCESS;
}

bool TreeParser::checkForEmptyFields(QTreeWidgetItem *item)
{
    for (int i = 0; i < item->childCount(); i++)
    {
        QLineEdit *name = qobject_cast<QLineEdit *>(this->tree->itemWidget(item->child(i), NAME_COL_INDX));
        if (name->text().isEmpty())
        {
            return false;
        }
        if (!this->checkForEmptyFields(item->child(i)))
        {
            return false;
        }
    }
    return true;
}

bool TreeParser::checkForDuplicateNames(QTreeWidgetItem *item)
{
    std::set<std::string> names;
    // check that names in each level are unique
    for (int i = 0; i < item->childCount(); i++)
    {
        QLineEdit *name = qobject_cast<QLineEdit *>(this->tree->itemWidget(item->child(i), NAME_COL_INDX));
        if (!name->text().isEmpty())
        {
            int size = names.size();
            names.insert(name->text().toStdString());
            if (size == names.size())
            {
                return false;
            }
        }
        if (!checkForDuplicateNames(item->child(i)))
        {
            return false;
        }
    }
    return true;
}

RootConfig *TreeParser::parseTree()
{

    std::vector<Config> allConfigs;
    for (int i = 0; i < this->tree->topLevelItemCount(); i++)
    {

        QTreeWidgetItem *item = this->tree->topLevelItem(i);

        allConfigs.push_back(this->_parseItem(item));
    }
    return RootConfig::InitInstance(allConfigs, fileType->currentText().toStdString(), className->text().toStdString());
}

Config TreeParser::_parseItem(QTreeWidgetItem *item)
{

    QLineEdit *name = qobject_cast<QLineEdit *>(this->tree->itemWidget(item, NAME_COL_INDX));
    QComboBox *type = qobject_cast<QComboBox *>(this->tree->itemWidget(item, TYPE_COL_INDX));
    QWidget *constraints_layout = qobject_cast<QWidget *>(this->tree->itemWidget(item, CONS_COL_INDX));
    QList<QLineEdit *> constraintsLineEdits = constraints_layout->findChildren<QLineEdit *>();

    std::string configName = name->text().toStdString();
    std::string configType = type->currentText().toStdString();

    std::vector<std::string> configConstraints;
    for (auto lineEdit : constraintsLineEdits)
    {
        configConstraints.push_back(lineEdit->text().toStdString());
    }

    std::vector<Config> ConfigChildren;

    for (int i = 0; i < item->childCount(); ++i)
    {
        ConfigChildren.push_back(this->_parseItem(item->child(i)));
    }
    return Config(configName, configType, configConstraints, ConfigChildren);
}
