#include "core/Application.h"

#include "core/AssetsManager.h"
#include "core/Scene.h"
#include "core/TimerManager.h"


namespace re {
    Application::Application(const int width, const int height, const String &title)
        : windowSize{static_cast<float>(width), static_cast<float>(height)} {
        InitWindow(width, height, title.c_str());
    }

    Application::~Application() {
        currentScene.reset();
        AssetsManager::Get().CleanCycle();
    }

    void Application::Run() {
        SetTargetFPS(60);

        auto lastAssetsClearTime = GetTime();
        while (!WindowShouldClose() && !quitRequested) {
            const auto deltaTime = GetFrameTime();
            InternalUpdate(deltaTime);
            InternalRender();

            TimerManager::Get().UpdateTimers(deltaTime);
            if (GetTime() - lastAssetsClearTime > cleanInterval) {
                lastAssetsClearTime = GetTime();
                AssetsManager::Get().CleanCycle();
            }
        }
        CloseWindow();
    }

    Vector2 Application::GetWindowSize() const {
        return windowSize;
    }

    void Application::InternalRender() const {
        if (currentScene) {
            currentScene->InternalRender();
        }
    }

    void Application::InternalUpdate(const float deltaTime) {
        Update(deltaTime);

        if (currentScene) {
            currentScene->InternalUpdate(deltaTime);
        }

        if (pendingScene && pendingScene != currentScene) {
            currentScene = pendingScene;
            currentScene->InternalInitialize();
        }
    }
}
