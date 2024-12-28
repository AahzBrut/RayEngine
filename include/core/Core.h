#pragma once
#include <map>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>


namespace re {
    using String = std::string;

    template<typename T>
    using Unique = std::unique_ptr<T>;

    template<typename T>
    using Shared = std::shared_ptr<T>;

    template<typename T>
    using Weak = std::weak_ptr<T>;

    template<typename T>
    using List = std::vector<T>;

    template<typename Key, typename Value, typename Compare = std::less<Key> >
    using Map = std::map<Key, Value, Compare>;

    template<typename Key, typename Value, typename Hasher = std::hash<Key> >
    using Dictionary = std::unordered_map<Key, Value, Hasher>;

    template<typename T>
    using Set = std::unordered_set<T>;

#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}
