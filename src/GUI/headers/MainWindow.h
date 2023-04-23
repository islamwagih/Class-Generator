#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "..\headers\treeEditor.h"
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
    ~MainWindow();

private slots:
    void on_insertChildBtn_clicked();

private:
    Ui::MainWindow *ui;
    TreeEditor *treeEditor;
};
#endif // MAINWINDOW_H
