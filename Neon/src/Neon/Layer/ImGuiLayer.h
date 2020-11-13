#pragma once

#include <Neon/Layer/Layer.h>

namespace Neon {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();
    
        void OnAttach() override;
        void OnUpdate() override;
        void OnEvent(Event &event) override;
        void OnDetach() override;
    private:
        bool _show = true;
        float _time;
    };
}


