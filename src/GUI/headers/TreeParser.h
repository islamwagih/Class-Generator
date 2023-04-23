#ifndef TREEPARSER_H
#define TREEPARSER_H

#include <QTreeWidgetItem>
#include <QComboBox>
#include <QLineEdit>
class TreeParser
{
public:
    TreeParser(QLineEdit *outDir, QComboBox *fileType, QTreeWidget *tree);
    void parseTree();
    void generateClass(); // generateClass should call parseTree and any other functions you need to generate the class
    ~TreeParser();

private:
    QLineEdit *outDir;
    QComboBox *fileType;
    QTreeWidget *tree;
};
#endif // TREEPARSER_H
