#include "headers/StateHandler.h"
#include <QDebug>
StateHandler *StateHandler::instance = nullptr;

StateHandler::StateHandler(IntermediateFormatHandler *intermediateFormatHandler, TreeParser *treeParser, std::function<void()> reset)
    : intermediateFormatHandler(intermediateFormatHandler), treeParser(treeParser), reset(reset)
{
    this->isLoadingState = false;
}

void StateHandler::init(IntermediateFormatHandler *intermediateFormatHandler, TreeParser *treeParser, std::function<void()> reset)
{
    instance = new StateHandler(intermediateFormatHandler, treeParser, reset);
}

StateHandler *StateHandler::getInstance()
{
    if (instance == nullptr)
    {
        throw std::runtime_error("StateHandler instance not initialized");
    }
    return instance;
}

void StateHandler::setLoadingState(bool isLoadingState)
{
    this->isLoadingState = isLoadingState;
}

void StateHandler::saveState()
{
    if (isLoadingState)
        return;
    auto rootConfig = this->treeParser->getInstance()->parseTree();
    json data = this->intermediateFormatHandler->getInstance()->rootConfigToJson(rootConfig);
    QDebug deb = qDebug();
    deb << "saving state";
    this->statesDone.push_back(data);
    if (this->statesDone.size() > MAX_STATES)
        this->statesDone.pop_front(); // remove the oldest state
    // clear the undone actions
    this->statesUndone.clear();
    deb << this->statesDone.size() << this->statesUndone.size();
}

void StateHandler::undo()
{
    QDebug deb = qDebug();
    if (this->statesDone.size() <= 1)
    {
        return;
    }
    deb << "undoing";
    // Pop to get the current state to save it in the undone states
    json state = this->statesDone.back();
    this->statesDone.pop_back(); // remove the current state and save it in the undone states
    this->statesUndone.push_back(state);

    // now load the previous state
    state = this->statesDone.back();
    isLoadingState = true;
    this->intermediateFormatHandler->getInstance()->loadJson(state);
    isLoadingState = false;
    deb << this->statesDone.size() << this->statesUndone.size();
}

void StateHandler::redo()
{
    QDebug deb = qDebug();
    if (this->statesUndone.empty())
        return;
    deb << "redoing";
    deb << this->statesUndone.size();
    json state = this->statesUndone.back();
    this->statesUndone.pop_back();
    this->statesDone.push_back(state);
    isLoadingState = true;
    this->intermediateFormatHandler->getInstance()->loadJson(state);
    isLoadingState = false;
    deb << this->statesDone.size() << this->statesUndone.size();
}

StateHandler::~StateHandler()
{
    delete instance;
}
