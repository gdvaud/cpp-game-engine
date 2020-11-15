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
        void OnDetach() override;
        virtual void OnImGuiRender() override;
        
        void Begin();
        void End();
        
    private:
        float _time = 0.0f;
    };
}


