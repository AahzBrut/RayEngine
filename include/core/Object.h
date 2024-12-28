#pragma once
#include <memory>

#include "Core.h"


namespace re {
    class Object : public std::enable_shared_from_this<Object> {
    public:
        Object() = default;
        virtual ~Object() = default;

        virtual void Destroy() { isPendingDestruction = true; }
        [[nodiscard]] bool IsPendingDestruction() const { return isPendingDestruction; }
        Weak<Object> GetWeakRef() { return shared_from_this(); }
        Weak<const Object> GetWeakRef() const { return shared_from_this(); }
        unsigned int GetUniqueID() const { return uniqueId; }

    private:
        bool isPendingDestruction = false;
        unsigned int uniqueId{GetNextUniqueId()};

        static unsigned int uniqueIdCounter;

        static unsigned int GetNextUniqueId() { return uniqueIdCounter++; }
    };
}
