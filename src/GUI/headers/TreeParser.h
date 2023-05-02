#ifndef TREEPARSER_H
#define TREEPARSER_H

#include <QTreeWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include "Config.h"
#include "rootconfig.h"
#define NAME_COL_INDX 0
#define TYPE_COL_INDX 1
#define CONS_COL_INDX 2

class TreeParser
{
public:
    TreeParser(QLineEdit *outDir, QLineEdit *className, QComboBox *fileType, QTreeWidget *tree);
    RootConfig *parseTree();
    void generateClass(); // generateClass should call parseTree and any other functions you need to generate the class
    ~TreeParser();

private:
    Config _parseItem(QTreeWidgetItem *item);
    QLineEdit *outDir;
    QLineEdit *className;
    QComboBox *fileType;
    QTreeWidget *tree;
};
#endif // TREEPARSER_H
