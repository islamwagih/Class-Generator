#include "..\headers\IntermediateFormatHandler.h"
#include "..\headers\TreeEditor.h"
#include <fstream>
#include <QDebug>
IntermediateFormatHandler::IntermediateFormatHandler(QLineEdit *classNameEdit, QComboBox *typeComboBox, QTreeWidget *tree)
{
    this->tree = tree;
    this->typeComboBox = typeComboBox;
    this->treeEditor = TreeEditor::getInstance();
    this->classNameEdit = classNameEdit;
}

json IntermediateFormatHandler::_rootConfigToJson(const RootConfig *allConfig)
{
    // create json file
    json jsonData;
    jsonData["class_name"] = allConfig->getClassName();
    jsonData["type"] = allConfig->getFileType();

    jsonData["parameters"] = json::array();
    for (auto config : allConfig->getConfigs())
    {
        jsonData["parameters"].push_back(singleConfigToJson(config));
    }
    return jsonData;
}

void IntermediateFormatHandler::saveFile(QString filePath, const RootConfig *allConfig)
{
    // create json file
    json j = _rootConfigToJson(allConfig);

    std::ofstream ofs(filePath.toStdString());
    ofs << j.dump(4); // identation of 4 spaces
    ofs.close();
}

json IntermediateFormatHandler::singleConfigToJson(const Config &config)
{
    json jsonData;
    jsonData["name"] = config.getName();
    jsonData["type"] = config.getType();
    _InsertConstraints(jsonData, config);
    jsonData["children"] = json::array();
    for (auto child : config.getChildren())
    {
        jsonData["children"].push_back(singleConfigToJson(child));
    }
    return jsonData;
}
void IntermediateFormatHandler::_InsertConstraints(json &jsonData, const Config &config)
{
    jsonData["constraints"] = json::array();
    for (auto constraint : config.getConstraints())
    {
        bool isDouble = false;
        for (auto c : constraint)
        {
            if (c == '.')
            {
                isDouble = true;
                break;
            }
        }
        try
        {
            if (isDouble)
            {
                jsonData["constraints"].push_back(std::stod(constraint));
            }
            else
            {
                jsonData["constraints"].push_back(std::stoi(constraint));
            }
        }
        catch (std::exception e)
        {
            jsonData["constraints"].push_back(constraint);
        }
    }
}

void IntermediateFormatHandler::loadChildren(json &j, QTreeWidgetItem *parent)
{
    QString name = QString::fromStdString(j["name"]);
    QString type = QString::fromStdString(j["type"]);
    QPair<QString, QString> constraints = QPair<QString, QString>("", "");
    if (j["constraints"].size() > 0)
    {
        auto x = j["constraints"][0];
        if (x.is_string())
        {
            constraints.first = QString::fromStdString(x);
        }
        else
        {
            if (x.is_number_float())
            {
                constraints.first = QString::number(x.get<float>());
            }
            else
            {
                constraints.first = QString::number(x.get<int>());
            }
        }
        if (j["constraints"].size() > 1)
        {
            auto y = j["constraints"][1];
            if (y.is_string())
            {
                constraints.second = QString::fromStdString(y);
            }
            else
            {
                if (y.is_number_float())
                {
                    constraints.second = QString::number(y.get<float>());
                }
                else
                {
                    constraints.second = QString::number(y.get<int>());
                }
            }
        }
    }
    auto current = this->treeEditor->makeRow(parent, name, type, constraints);
    for (auto &element : j["children"].items())
    {
        this->loadChildren(element.value(), current);
    }
}

void IntermediateFormatHandler::loadFile(QString filePath)
{
    std::ifstream file(filePath.toStdString());
    json j;
    file >> j;
    file.close();
    this->treeEditor->reset();
    this->typeComboBox->setCurrentText(QString::fromStdString(j["type"]));
    this->classNameEdit->setText(QString::fromStdString(j["class_name"]));
    for (auto &element : j["parameters"].items())
    {
        this->loadChildren(element.value(), this->tree->invisibleRootItem());
    }
}

IntermediateFormatHandler::~IntermediateFormatHandler()
{
}
