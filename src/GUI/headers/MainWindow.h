#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers\TreeEditor.h"
#include "headers\IntermediateFormatHandler.h"
#include "headers\TreeParser.h"
#include "headers\StateHandler.h"
#include "..\..\controller\controller.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTreeWidgetItem>
#include <QComboBox>
#include <QPropertyAnimation>
#include <QDebug>
#include <QFileDialog>

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

    void on_outBrowseBtn_clicked();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_typeComboBox_currentIndexChanged(int index);

    void on_classNameEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QString saveFilePath;
    TreeEditor *treeEditor;
    TreeParser *treeParser;
    IntermediateFormatHandler *intermediateFormatHandler;
    StateHandler *stateHandler;
    bool getSaveFilePath();
};
#endif // MAINWINDOW_H
