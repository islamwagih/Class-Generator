#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "..\headers\TreeEditor.h"
#include "..\headers\IntermediateFormatHandler.h"
#include "..\headers\TreeParser.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void insertChild();
    void insertRow();
    void removeRow();
    void reset();
    ~MainWindow();

private slots:
    void on_insertChildBtn_clicked();

    void on_insertRowBn_clicked();

    void on_removeRowBtn_clicked();

    void on_resetBtn_clicked();

    void on_generateBtn_clicked();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_actionInsert_Child_triggered();

    void on_actionInsert_Row_triggered();

    void on_actionRemove_Row_triggered();

    void on_actionReset_triggered();

    void on_actionSave_As_triggered();

private:
    Ui::MainWindow *ui;
    QString saveFilePath;
    TreeEditor *treeEditor;
    TreeParser *treeParser;
    IntermediateFormatHandler *intermediateFormatHandler;
    bool getSaveFilePath();
};
#endif // MAINWINDOW_H
