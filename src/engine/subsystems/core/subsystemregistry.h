#pragma once

#include <vector>
#include "subsystem.h"

class SubsystemRegistry {
    public:
        void Initialize();
        void Uninitialize();
        void Tick();
        void Render();

        void AddSubsystem(Subsystem* subsystem);
        void RemoveSubsystem(Subsystem* subsystem);
    private:
        std::vector<Subsystem*> subsystems;

};