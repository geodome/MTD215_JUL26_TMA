#include "definitions.h"
#include "window.h"
#include "circle.h"

class App {
    private:
    Window* window;
    Circle* circle;
    public:
    App() {
        window = new Window(TITLE, WIDTH, HEIGHT);
        circle = new Circle(RADIUS, WIDTH/2 - RADIUS, HEIGHT/2 - RADIUS, RED);
        window->add(circle);
    }
    void mainloop() {
        window->mainloop();
    }
    ~App() {
        delete circle;
        delete window;
    }
};

int main() {
    try {
        // arrow keys are W,A,S,D
        // press Q to quit
        // press Space to pause
        auto app = App();
        app.mainloop();
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}