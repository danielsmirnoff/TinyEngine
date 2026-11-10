#pragma once

/// @brief A modular system that can be plugged into the engine
class Subsystem {
    public:
        virtual void Register() {}
        virtual void Tick() {}
        virtual void Render() {}
        virtual void DeRegister() {}
        virtual ~Subsystem() = default;
};