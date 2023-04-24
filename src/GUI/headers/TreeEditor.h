#ifndef TREEEDITOR_H
#define TREEEDITOR_H

#include <QTreeWidgetItem>

class TreeEditor
{
private:
    TreeEditor(const TreeEditor &) = delete;
    TreeEditor &operator=(const TreeEditor &) = delete;
    TreeEditor(QTreeWidget *tree);
    static TreeEditor *instance;

public:
    QTreeWidgetItem *makeRow(QTreeWidgetItem *parent);
    QTreeWidgetItem *makeRow(QTreeWidgetItem *parent, QString name, QString type, QPair<QString, QString> constraints);
    void removeRow(QTreeWidgetItem *item);
    void onComboboxChanged(QTreeWidgetItem *item);
    static TreeEditor *getInstance();
    static void init(QTreeWidget *tree);
    void reset();
    ~TreeEditor();

private:
    QTreeWidget *tree;
    // TODO: Add/Remove types depending on the type of the file type (JSON, INI, etc.)
    QStringList paramTypes = {"int", "float", "string", "bool", "nested"};
};
#endif // TREEEDITOR_H
