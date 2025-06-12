#include "StudentEnrollmentApp.h"
#include <iostream>

int main() {
    StudentEnrollmentApp app;
    
    if (!app.initialize()) {
        std::cerr << "Failed to initialize application\n";
        return -1;
    }
    
    app.run();
    return 0;
} 