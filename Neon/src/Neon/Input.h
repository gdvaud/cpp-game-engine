#pragma once

#include "neon_pch.h"

namespace Neon {
    class Input {
    public:
        inline static bool IsKeyPressed(int keyCode) { return _instance->IsKeyPressed_Impl(keyCode); }
        inline static bool IsMouseButtonPressed(int buttonCode) {
            return _instance->IsMouseButtonPressed_Impl(buttonCode);
        }
        
        inline static std::pair<float, float> GetMousePosition() {
            return _instance->GetMousePosition_Impl();
        }
        inline static float GetMouseX() { return _instance->GetMouseX_Impl(); }
        inline static float GetMouseY() { return _instance->GetMouseY_Impl(); }
    
    protected:
        virtual bool IsKeyPressed_Impl(int keyCode) = 0;
        
        virtual bool IsMouseButtonPressed_Impl(int keyCode) = 0;
        virtual std::pair<float, float> GetMousePosition_Impl() = 0;
        virtual float GetMouseX_Impl() = 0;
        virtual float GetMouseY_Impl() = 0;
    
    private:
        static Input *_instance;
    };
}