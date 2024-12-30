#pragma once
#include <raylib.h>
#include "core/Object.h"


namespace re {
    class Application;
    class GameStage;
    class HUD;

    // ReSharper disable once CppClassCanBeFinal
    class Scene : public Object {
    public:
        explicit Scene(Application *application);

        void InternalInitialize();
        void InternalUpdate(float deltaTime);
        void InternalRender() const;

        Application *GetApplication() { return application; }
        const Application *GetApplication() const { return application; }

        template<typename HUDType, typename... Args>
        Weak<HUDType> SpawnHUD(Args... args);

        void RenderHUD() const;
        [[nodiscard]] Vector2 GetWindowSize() const;

    private:
        Application *application;
        bool initialized;
        Shared<HUD> hud{};

        virtual void Render() const {}
        virtual void Initialize() {}
        virtual void Update(float deltaTime) {}
    };

    template<typename HUDType, typename... Args>
    Weak<HUDType> Scene::SpawnHUD(Args... args) {
        Shared<HUDType> newHUD{new HUDType(this, args...)};
        hud = newHUD;
        return newHUD;
    }
}
