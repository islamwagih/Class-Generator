#ifndef INTERMEDIATEFORMATHANDLER_H
#define INTERMEDIATEFORMATHANDLER_H

#include "..\..\..\lib\json.hpp"
#include "..\headers\rootconfig.h"
#include "TreeEditor.h"
#include <QTreeWidgetItem>
#include <QComboBox>
#include <QLineEdit>
using json = nlohmann::ordered_json;

class IntermediateFormatHandler
{
public:
    IntermediateFormatHandler(QLineEdit *classNameEdit, QComboBox *typeComboBox, QTreeWidget *tree);
    void saveFile(QString filePath, const RootConfig *allConfig);
    void saveFileAs(QString filePath, const RootConfig *allConfig);
    void loadFile(QString filePath);
    ~IntermediateFormatHandler();

private:
    QTreeWidget *tree;
    QLineEdit *classNameEdit;
    QComboBox *typeComboBox;
    TreeEditor *treeEditor;
    json singleConfigToJson(const Config &config);
    void loadChildren(json &j, QTreeWidgetItem *parent);
};
#endif // INTERMEDIATEFORMATHANDLER_H
