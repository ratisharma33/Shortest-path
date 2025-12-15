#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>



class FindPath {
public:
    static std::unordered_map<std::string, double> parm;
    static std::vector<std::string> printBill;

    static void findPath(std::unordered_map<std::string, double>& details) {
        printBill.clear();
        double Max_Value = getMaxValue(details);
        double Min_Value = getMinValue(details);

        if (Max_Value != Min_Value) {
            std::string Max_Key = getKeyFromValue(details, Max_Value);
            std::string Min_Key = getKeyFromValue(details, Min_Value);
            double result = Max_Value + Min_Value;
            result = round(result, 1);

            if (result >= 0.0) {
                std::cout << Min_Key << " needs to pay " << Max_Key << ": " << round(std::abs(Min_Value), 2) << std::endl;
                details.erase(Max_Key);
                details.erase(Min_Key);
                details[Max_Key] = result;
                details[Min_Key] = 0.0;
            } else {
                std::cout << Min_Key << " needs to pay " << Max_Key << ": " << round(std::abs(Max_Value), 2) << std::endl;
                details.erase(Max_Key);
                details.erase(Min_Key);
                details[Max_Key] = 0.0;
                details[Min_Key] = result;
            }
            findPath(details);
        }
    }

    static double round(double value, int places) {
        if (places < 0)
            throw std::invalid_argument("places cannot be negative");

        double factor = std::pow(10, places);
        return std::round(value * factor) / factor;
    }

    static double getMaxValue(const std::unordered_map<std::string, double>& details) {
        double max = -std::numeric_limits<double>::infinity();
        for (const auto& pair : details) {
            if (pair.second > max) {
                max = pair.second;
            }
        }
        return max;
    }

    static double getMinValue(const std::unordered_map<std::string, double>& details) {
        double min = std::numeric_limits<double>::infinity();
        for (const auto& pair : details) {
            if (pair.second < min) {
                min = pair.second;
            }
        }
        return min;
    }

    static std::string getKeyFromValue(const std::unordered_map<std::string, double>& hm, double value) {
        for (const auto& pair : hm) {
            if (pair.second == value) {
                return pair.first;
            }
        }
        return "";
    }
};

std::unordered_map<std::string, double> FindPath::parm;
std::vector<std::string> FindPath::printBill;

int main() {
    FindPath::parm["A"] = -5.0;
    FindPath::parm["B"] = 25.0;
    FindPath::parm["C"] = -20.0;
    FindPath::parm["D"] = 25.0;
    FindPath::parm["E"] = -20.0;
    FindPath::parm["F"] = -5.0;

    // Passing values to findPath Method.
    FindPath::findPath(FindPath::parm);

    // std::cout << printBill.toString() << std::endl;

    return 0;
}
