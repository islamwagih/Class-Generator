#include <deque>
#include "..\..\..\lib\json.hpp"
#include "TreeParser.h"
#include "IntermediateFormatHandler.h"
using json = nlohmann::ordered_json;

class StateHandler
{
public:
    static StateHandler *getInstance();
    // init takes in a pointer to the intermediateFormatHandler and treeParser and lambda function to reset the tree
    static void init(IntermediateFormatHandler *intermediateFormatHandler, TreeParser *treeParser, std::function<void()> reset);
    void saveState();
    void setLoadingState(bool isLoadingState);
    void undo();
    void redo();
    ~StateHandler();

private:
    static const int MAX_STATES = 200;
    StateHandler(IntermediateFormatHandler *intermediateFormatHandler, TreeParser *treeParser, std::function<void()> reset);
    StateHandler(const StateHandler &other) = delete;
    StateHandler &operator=(const StateHandler &other) = delete;
    static StateHandler *instance;
    std::deque<json> statesDone;
    std::deque<json> statesUndone;
    IntermediateFormatHandler *intermediateFormatHandler;
    TreeParser *treeParser;
    std::function<void()> reset;
    bool isLoadingState;
};
