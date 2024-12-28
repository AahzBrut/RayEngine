#include "EntryPoint.h"


int main() {
    const auto application = GetApplication();
    application->Run();
    delete application;

    return 0;
}
