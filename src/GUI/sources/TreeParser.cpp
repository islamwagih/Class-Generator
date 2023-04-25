#include "headers/TreeParser.h"



TreeParser::TreeParser(QLineEdit *outDir, QComboBox *fileType, QTreeWidget *tree) : outDir(outDir), fileType(fileType), tree(tree)
{
}

RootConfig TreeParser::parseTree()
{

    std::vector<Config> allConfigs;
    for(int i=0; i<this->tree->topLevelItemCount(); i++){

        QTreeWidgetItem *item = this->tree->topLevelItem(i);

        allConfigs.push_back(this->_parseItem(item));
    }
    return RootConfig(allConfigs, fileType->currentText().toStdString());

}

Config TreeParser::_parseItem(QTreeWidgetItem *item){

    QLineEdit *name = qobject_cast<QLineEdit*>(this->tree->itemWidget(item,NAME_COL_INDX));
    QComboBox *type = qobject_cast<QComboBox*>(this->tree->itemWidget(item,TYPE_COL_INDX));
    QWidget *constraints_layout = qobject_cast<QWidget*>(this->tree->itemWidget(item,CONS_COL_INDX));
    QList<QLineEdit*> constraintsLineEdits = constraints_layout->findChildren<QLineEdit*>();


    std::string configName = name->text().toStdString();
    std::string configType = type->currentText().toStdString();

    std::vector<std::string> configConstraints;
    for(auto lineEdit : constraintsLineEdits){
        configConstraints.push_back(lineEdit->text().toStdString());
    }


    std::vector<Config> ConfigChildren;

    for(int i=0; i<item->childCount(); ++i){
        ConfigChildren.push_back( this->_parseItem(item->child(i)) );
    }
    return Config(configName, configType, configConstraints, ConfigChildren);


}
