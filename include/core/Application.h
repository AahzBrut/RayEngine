#pragma once
#include <raylib.h>
#include "core/Core.h"

namespace re {
    class Scene;

    // ReSharper disable once CppClassCanBeFinal
    class Application {
    public:
        Application(int width, int height, const String &title);
        virtual ~Application();

        void Run();
        void Quit() { quitRequested = true; }
        void SetCleanInterval(const float newCleanInterval) { cleanInterval = newCleanInterval; }
        [[nodiscard]] Vector2 GetWindowSize() const;

        template<typename SceneType>
        Weak<SceneType> CreateScene();
    private:
        Shared<Scene> currentScene;
        Shared<Scene> pendingScene;
        double cleanInterval{2.5f};
        Vector2 windowSize;
        bool quitRequested{false};

        void InternalUpdate(float deltaTime);
        void InternalRender() const;
        virtual void Render() {}
        virtual void Update(float deltaTime) {}
    };

    template<typename SceneType>
    Weak<SceneType> Application::CreateScene() {
        Shared<SceneType> newScene{new SceneType{this}};
        pendingScene = newScene;
        return newScene;
    }
}