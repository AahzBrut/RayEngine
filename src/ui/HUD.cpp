#include "ui/HUD.h"


namespace re {
    void HUD::Initialize() {
        if (!initialized) {
            initialized = true;
            OnInitialize();
        }
    }
}
