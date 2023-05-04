#ifndef TREEEDITOR_H
#define TREEEDITOR_H

#include <QTreeWidgetItem>
#include <QObject>
#include <QStatusBar>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QHeaderView>

class TreeEditor : public QObject
{
    Q_OBJECT
public:
    QTreeWidgetItem *makeRow(QTreeWidgetItem *parent);
    QTreeWidgetItem *makeRow(QTreeWidgetItem *parent, QString name, QString type, QPair<QString, QString> constraints);
    void removeRow(QTreeWidgetItem *item);
    void onComboboxChanged(QTreeWidgetItem *item);
    static TreeEditor *getInstance();
    static void init(QTreeWidget *tree, QStatusBar *statusBar, std::function<void()> saveState);
    void reset();
    ~TreeEditor();

private slots:
    bool handleValidator(QLineEdit *edit, QString text);

private:
    QTreeWidget *tree;
    std::function<void()> saveState;
    // TODO: Add/Remove types depending on the type of the file type (JSON, INI, etc.)
    QStringList paramTypes = {"int", "float", "string", "bool", "nested"};
    TreeEditor(const TreeEditor &) = delete;
    TreeEditor &operator=(const TreeEditor &) = delete;
    TreeEditor(QTreeWidget *tree, QStatusBar *statusBar, std::function<void()> saveState);
    void createConstraintLineEdits(QTreeWidgetItem *item);
    void setLineEditsValidator(QTreeWidgetItem *item);
    static TreeEditor *instance;
    QStatusBar *statusBar;
    void displayMessageOnStatusBar(QString message, int timeout);
};
#endif // TREEEDITOR_H
