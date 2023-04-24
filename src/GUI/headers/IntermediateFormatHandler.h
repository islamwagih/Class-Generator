#ifndef INTERMEDIATEFORMATHANDLER_H
#define INTERMEDIATEFORMATHANDLER_H

#include <QTreeWidgetItem>
#include <QComboBox>
#include <QLineEdit>
class IntermediateFormatHandler
{
public:
    IntermediateFormatHandler(QTreeWidget *tree);
    void saveFile(QString filePath);
    void loadFile(QString filePath);
    ~IntermediateFormatHandler();

private:
    QTreeWidget *tree;
};
#endif // INTERMEDIATEFORMATHANDLER_H
