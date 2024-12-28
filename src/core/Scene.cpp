#include "core/Scene.h"
#include "core/Application.h"
#include "ui/HUD.h"

namespace re {
    Scene::Scene(Application *application)
        : application(application),
          initialized(false) {}

    void Scene::InternalInitialize() {
        if (!initialized) {
            initialized = true;
            Initialize();
        }
    }

    void Scene::InternalUpdate(const float deltaTime) {
        Update(deltaTime);

        if (hud) {
            if (!hud->IsInitialized()) hud->Initialize();
            hud->Update(deltaTime);
        }
    }

    void Scene::RenderHUD() const {
        if (hud) hud->Draw();
    }

    void Scene::Render() const {
        BeginDrawing();
        ClearBackground(BLACK);

        RenderHUD();

        EndDrawing();
    }

    Vector2 Scene::GetWindowSize() const {
        return application->GetWindowSize();
    }
}