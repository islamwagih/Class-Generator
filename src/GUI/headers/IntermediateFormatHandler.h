#ifndef INTERMEDIATEFORMATHANDLER_H
#define INTERMEDIATEFORMATHANDLER_H

#include <QTreeWidgetItem>
#include <QComboBox>
#include <QLineEdit>
class IntermediateFormatHandler
{
public:
    IntermediateFormatHandler(QTreeWidget *tree, QString filePath);
    void saveFile();
    void loadFile(); 
    ~IntermediateFormatHandler();

private:
    QTreeWidget *tree;
    QString filePath;
};
#endif // INTERMEDIATEFORMATHANDLER_H
