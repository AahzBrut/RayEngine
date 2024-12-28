#pragma once
#include <raylib.h>
#include "core/Core.h"

namespace re {
    class AssetsManager {
    public:
        static AssetsManager& Get();
        Shared<Texture2D> GetTexture(const String& path);
        void CleanCycle();
        Shared<Font> GetFont(const String& path);

    protected:
        AssetsManager() = default;

    private:
        static Unique<AssetsManager> instance;
        Dictionary<String, Shared<Texture2D>> textures{};
        Dictionary<String, Shared<Font>> fonts{};

        template<typename T>
        Shared<T> LoadAsset(const String& path, Dictionary<String, Shared<T>>& container, T (*loadAssetPtr)(const char*));

        template<typename T>
        void CleanUnusedAssets(Dictionary<String, Shared<T>> &container, void (*cleanAssetPtr)(T));
    };

    template<typename T>
    Shared<T> AssetsManager::LoadAsset(const String &path, Dictionary<String, Shared<T>> &container, T (*loadAssetPtr)(const char*)) {
        if (const auto asset = container.find(path); asset != container.end()) {
            return asset->second;
        }
        const auto asset = std::make_shared<T>(loadAssetPtr(path.c_str()));
        container.insert({path, asset});
        return asset;
    }

    template<typename T>
    void AssetsManager::CleanUnusedAssets(Dictionary<String, Shared<T>> &container, void(*cleanAssetPtr)(T)) {
        for (auto iterator = container.begin(); iterator != container.end();) {
            if (iterator->second.unique()) {
                cleanAssetPtr(*iterator->second);
                iterator = container.erase(iterator);
            } else {
                ++iterator;
            }
        }
    }
}