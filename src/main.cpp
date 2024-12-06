#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <iostream>

int main() {
    nlohmann::json jsonObj = {
        {"name", "John Doe"},
        {"age", 30},
        {"is_student", false}
    };

    fmt::print("Serialized JSON: {}\n", jsonObj.dump(4));

    return 0;
}
