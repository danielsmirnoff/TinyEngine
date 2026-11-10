#include "subsystemregistry.h"


void SubsystemRegistry::Initialize() {
	for(const auto& subsystem : subsystems)
	{
		subsystem->Register();
	}
}

void SubsystemRegistry::Uninitialize() {
	for (const auto& subsystem : subsystems)
	{
		subsystem->DeRegister();
	}
}

void SubsystemRegistry::Tick() {
	for (const auto& subsystem : subsystems)
	{
		subsystem->Tick();
	}
}

void SubsystemRegistry::Render() {
	for (const auto& subsystem : subsystems)
	{
		subsystem->Render();
	}
}

void SubsystemRegistry::AddSubsystem(Subsystem* subsystem) {
	subsystems.push_back(subsystem);
}

void SubsystemRegistry::RemoveSubsystem(Subsystem* subsystem) {
	std::erase(subsystems, subsystem);
}