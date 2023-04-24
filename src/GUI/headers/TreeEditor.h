#ifndef TREEEDITOR_H
#define TREEEDITOR_H

#include <QTreeWidgetItem>

class TreeEditor
{
public:
    TreeEditor(QTreeWidget *tree);
    void makeRow(QTreeWidgetItem *parent);
    void removeRow(QTreeWidgetItem *item);
    void onComboboxChanged(QTreeWidgetItem *item);
    ~TreeEditor();

private:
    QTreeWidget *tree;
    // TODO: Add/Remove types depending on the type of the file type (JSON, INI, etc.)
    QStringList paramTypes = {"int", "float", "string", "bool", "nested"};
};
#endif // TREEEDITOR_H
