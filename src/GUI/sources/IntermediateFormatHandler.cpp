#include "headers\IntermediateFormatHandler.h"
#include "headers\TreeEditor.h"
#include <fstream>
#include <QDebug>

IntermediateFormatHandler *IntermediateFormatHandler::instance = nullptr;

IntermediateFormatHandler::IntermediateFormatHandler(QLineEdit *classNameEdit, QComboBox *typeComboBox, QTreeWidget *tree)
{
    this->classNameEdit = classNameEdit;
    this->typeComboBox = typeComboBox;
    this->tree = tree;
    this->treeEditor = TreeEditor::getInstance();
}

void IntermediateFormatHandler::init(QLineEdit *classNameEdit, QComboBox *typeComboBox, QTreeWidget *tree)
{
    instance = new IntermediateFormatHandler(classNameEdit, typeComboBox, tree);
}

IntermediateFormatHandler *IntermediateFormatHandler::getInstance()
{
    if (instance == nullptr)
    {
        throw std::runtime_error("IntermediateFormatHandler instance not initialized");
    }
    return instance;
}

json IntermediateFormatHandler::rootConfigToJson(const RootConfig *allConfig)
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
    json j = rootConfigToJson(allConfig);

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
    std::vector<std::string> constraints = config.getConstraints();
    if (constraints.size() == 1 && constraints[0] == "")
        return;

    for (auto constraint : constraints)
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

bool IntermediateFormatHandler::loadFile(QString filePath)
{
    std::ifstream file(filePath.toStdString());
    json j;
    file >> j;
    file.close();
    if (!checkJsonToLoad(j))
    {
        return false;
    }
    loadJson(j);
    return true;
}

void IntermediateFormatHandler::loadJson(json &j)
{
    this->treeEditor->reset();
    this->typeComboBox->setCurrentText(QString::fromStdString(j["type"]));
    this->classNameEdit->setText(QString::fromStdString(j["class_name"]));
    for (auto &element : j["parameters"].items())
    {
        this->loadChildren(element.value(), this->tree->invisibleRootItem());
    }
}

bool IntermediateFormatHandler::checkJsonToLoad(json &j)
{
    if (
        !j["class_name"].is_string() ||
        !j["type"].is_string() ||
        !j["parameters"].is_array() ||
        j.size() != 3)
    {
        return false;
    }
    return checkJsonChildren(j["parameters"]);
}

bool IntermediateFormatHandler::checkJsonChildren(json &j)
{
    std::set<std::string> names;
    for (auto &element : j.items())
    {
        auto name = element.value()["name"];
        auto type = element.value()["type"];
        auto constraints = element.value()["constraints"];
        auto children = element.value()["children"];
        // 1. Check if all the fields are present
        if (
            !name.is_string() ||
            !type.is_string() || type.get<std::string>().empty() ||
            !constraints.is_array() || constraints.size() > 2 ||
            !children.is_array() ||
            element.value().size() != 4)
        {
            return false;
        }
        // 2. Check if parameter has children but type is not nested
        if (type != "nested" && children.size() != 0)
        {
            return false;
        }
        // 3. Validate constraints size and type
        auto typeString = type.get<std::string>();
        if (typeString == "int")
        {
            if (constraints.size() != 2)
            {
                return false;
            }
            for (auto &constraint : constraints.items())
            {
                if (constraint.value().is_string() && constraint.value().get<std::string>().empty())
                {
                    continue;
                }
                if (!constraint.value().is_number_integer())
                {
                    return false;
                }
            }
        }
        else if (typeString == "float")
        {
            if (constraints.size() != 2)
            {
                return false;
            }
            for (auto &constraint : constraints.items())
            {
                if (constraint.value().is_string() && constraint.value().get<std::string>().empty())
                {
                    continue;
                }
                if (!constraint.value().is_number_float())
                {
                    return false;
                }
            }
        }
        else if (typeString == "string")
        {
            if (constraints.size() != 1)
            {
                return false;
            }
            for (auto &constraint : constraints.items())
            {
                if (!constraint.value().is_string())
                {
                    return false;
                }
            }
        }
        else if (typeString == "nested" || typeString == "bool")
        {
            if (constraints.size() != 0)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        // 4. Check if name is unique
        auto nameString = name.get<std::string>();
        if (!nameString.empty())
        {
            int size = names.size();
            names.insert(nameString);
            if (size == names.size())
            {
                return false;
            }
        }
        // 5. Check if children are valid
        if (!checkJsonChildren(element.value()["children"]))
        {
            return false;
        }
    }
    return true;
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

IntermediateFormatHandler::~IntermediateFormatHandler()
{
}
