#pragma once
#include <cstddef>
#include <functional>

#include "core/Core.h"
#include "core/Object.h"


namespace re {
    class TimerHandle {
    public:
        TimerHandle() = default;
        [[nodiscard]] unsigned int GetTimerKey() const { return timerKey; }

    private:
        static unsigned int timerKeyCounter;
        unsigned int timerKey{GetNextTimerKey()};

        static unsigned int GetNextTimerKey() { return ++timerKeyCounter; }
    };

    struct TimerHandleHashFunction {
        std::size_t operator()(const TimerHandle &key) const { return std::hash<unsigned int>()(key.GetTimerKey()); }
    };

    inline bool operator==(const TimerHandle &lhs, const TimerHandle &rhs) {
        return lhs.GetTimerKey() == rhs.GetTimerKey();
    }

    class Timer {
    public:
        Timer(const Weak<Object> &object, const std::function<void()> &callback, float duration, bool repeat);
        void Tick(float deltaTime);

        [[nodiscard]] bool Expired() const {
            return expired || listener.first.expired() || listener.first.lock()->IsPendingDestruction();
        }

        void SetExpired() { expired = true; }

    private:
        std::pair<Weak<Object>, std::function<void()> > listener;
        float duration;
        bool repeat;
        float elapsedTime;
        bool expired;
    };

    class TimerManager {
    public:
        static TimerManager &Get();

        template<typename ClassName>
        TimerHandle SetTimer(const Weak<Object>& object, void (ClassName::*callback)(), float duration, bool repeat = false) {
            TimerHandle handler{};
            timers.emplace(handler, Timer(
                object,
                [=] { (static_cast<ClassName *>(object.lock().get())->*callback)(); },
                duration,
                repeat));
            return handler;
        }

        void UpdateTimers(float deltaTime);
        void ClearTimer(TimerHandle timerHandler);

    protected:
        TimerManager() = default;

    private:
        static Unique<TimerManager> instance;
        Dictionary<TimerHandle, Timer, TimerHandleHashFunction> timers;
    };
}
