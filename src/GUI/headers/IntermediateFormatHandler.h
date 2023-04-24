#ifndef INTERMEDIATEFORMATHANDLER_H
#define INTERMEDIATEFORMATHANDLER_H

#include "..\..\..\lib\json.hpp"
#include "TreeEditor.h"
#include <QTreeWidgetItem>
#include <QComboBox>
#include <QLineEdit>
using json = nlohmann::json;

class IntermediateFormatHandler
{
public:
    IntermediateFormatHandler(QTreeWidget *tree);
    void saveFile(QString filePath);
    void loadChildren(json &j, QTreeWidgetItem *parent);
    void loadFile(QString filePath);
    ~IntermediateFormatHandler();

private:
    QTreeWidget *tree;
    TreeEditor *treeEditor;
};
#endif // INTERMEDIATEFORMATHANDLER_H
