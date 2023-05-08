#include "../headers/json_literals.h"

namespace json_literals
{

    // this in private section of JSONParser
    FormattableString GET_JSON_OBJ =
        R"(    nlohmann::json json_object;
)";

    FormattableString GET_JSON_VALUE = R"(
        nlohmann::json get_json_value(const nlohmann::json& json_object, const std::vector<std::string>& keys) {
        if (keys.size() == 0) {
            // If there are no more keys to access, return the JSON object
            return json_object;
        }
        else {
            // Get the first key in the vector
            std::string key = keys[0];
            // Check if the key exists in the JSON object
            if (json_object.find(key) != json_object.end()) {
                // If the key exists, recursively get the value of the next key
                return get_json_value(json_object[key], std::vector<std::string>(keys.begin() + 1, keys.end()));
            } else {
                // If the key doesn't exist, throw an runtime exception
                throw std::runtime_error("Key \"" + key + "\" does not exist in JSON object");
            }
        }
    }
)";

    FormattableString GET_FROM_FILE = R"(
        template <typename T>
    T getFromFile(const std::vector<std::string> &path){
        T value = get_json_value(this->json_object, path);
        return value;
    }
)";

    FormattableString SET_IN_FILE = R"(
            template <typename T>
    bool setInFile(const std::vector<std::string> &path, T value) {
        // Get JSON object
        nlohmann::json* oldValue = &(this->json_object);
        // Get path
        for (const std::string& key : path) {
            // Check if key exists
            try {
                oldValue = &((*oldValue)[key]);
            } catch (std::exception& e) {
                return false;
            }
        }
        // Set value
        *oldValue = value;
        // Save JSON file
        std::ofstream output(this->filePath);
        output << this->json_object;
        output.close();
        return true;
    }
)";

} // namespace json_literals
