#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <d3d11.h>
#include <tchar.h>
#include "../core/subsystem.h"
#include "engine/engine.h"

class GUISubsystem : public Subsystem {
    public:
        void Register()   override;
        void Render()     override;
        void Tick()       override;
        void DeRegister() override;
};