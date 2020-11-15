#pragma once

#include <Neon/Layer/Layer.h>

#include "Neon/Event/Event.h"
#include "Neon/Event/ApplicationEvent.h"
#include "Neon/Event/MouseEvent.h"
#include "Neon/Event/KeyEvent.h"

namespace Neon {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override {}
    
        void OnAttach() override;
        void OnUpdate() override;
        void OnEvent(Event &event) override;
        void OnDetach() override;
    
    // Events
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event);
        bool OnMouseMovedEvent(MouseMovedEvent &event);
        bool OnMouseScrolledEvent(MouseScrolledEvent &event);
        bool OnKeyPressedEvent(KeyPressedEvent &event);
        bool OnKeyReleasedEvent(KeyReleasedEvent &event);
        bool OnKeyTypedEvent(KeyTypedEvent &event);
        bool OnWindowResizedEvent(WindowResizedEvent &event);
    private:
        bool _show = true;
        float _time;
    };
}


