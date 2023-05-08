#ifndef INTERMEDIATEFORMATHANDLER_H
#define INTERMEDIATEFORMATHANDLER_H

#include "..\..\..\lib\json.hpp"
#include "..\headers\rootconfig.h"
#include "TreeEditor.h"
#include <QTreeWidgetItem>
#include <QComboBox>
#include <stdexcept>
#include <QLineEdit>
#include <set>

using json = nlohmann::ordered_json;

class IntermediateFormatHandler
{
public:
    static IntermediateFormatHandler *getInstance();
    static void init(QLineEdit *classNameEdit, QComboBox *typeComboBox, QTreeWidget *tree);
    void saveFile(QString filePath, const RootConfig *allConfig);
    void saveFileAs(QString filePath, const RootConfig *allConfig);
    json rootConfigToJson(const RootConfig *allConfig);
    bool loadFile(QString filePath);
    void loadJson(json &j);
    ~IntermediateFormatHandler();

private:
    QTreeWidget *tree;
    QLineEdit *classNameEdit;
    QComboBox *typeComboBox;
    TreeEditor *treeEditor;
    IntermediateFormatHandler(QLineEdit *classNameEdit, QComboBox *typeComboBox, QTreeWidget *tree);
    IntermediateFormatHandler(const IntermediateFormatHandler &other) = delete;
    IntermediateFormatHandler &operator=(const IntermediateFormatHandler &other) = delete;
    static IntermediateFormatHandler *instance;
    bool checkJsonToLoad(json &j);
    bool checkJsonChildren(json &j);
    json singleConfigToJson(const Config &config);
    void loadChildren(json &j, QTreeWidgetItem *parent);
    void _InsertConstraints(json &jsonData, const Config &config);
};
#endif // INTERMEDIATEFORMATHANDLER_H
