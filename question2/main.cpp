#include "calculator.h"


int main() {
    try {
        auto app = CalculatorApp();
        app.mainloop();
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}