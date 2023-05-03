#ifndef INTERMEDIATEFORMATHANDLER_H
#define INTERMEDIATEFORMATHANDLER_H

#include "..\..\..\lib\json.hpp"
#include "..\headers\rootconfig.h"
#include "TreeEditor.h"
#include <QTreeWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include <set>

using json = nlohmann::ordered_json;

class IntermediateFormatHandler
{
public:
    IntermediateFormatHandler(QLineEdit *classNameEdit, QComboBox *typeComboBox, QTreeWidget *tree);
    void saveFile(QString filePath, const RootConfig *allConfig);
    void saveFileAs(QString filePath, const RootConfig *allConfig);
    bool loadFile(QString filePath);
    ~IntermediateFormatHandler();

private:
    QTreeWidget *tree;
    QLineEdit *classNameEdit;
    QComboBox *typeComboBox;
    TreeEditor *treeEditor;
    bool checkJsonToLoad(json &j);
    bool checkJsonChildren(json &j);
    json singleConfigToJson(const Config &config);
    void loadChildren(json &j, QTreeWidgetItem *parent);
    json _rootConfigToJson(const RootConfig *allConfig);
    void _InsertConstraints(json &jsonData, const Config &config);
};
#endif // INTERMEDIATEFORMATHANDLER_H
