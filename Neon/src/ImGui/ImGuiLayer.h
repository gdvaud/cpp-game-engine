#pragma once

#include <Neon/Core/Layer.h>

#include "Neon/Event/ApplicationEvent.h"
#include "Neon/Event/Event.h"
#include "Neon/Event/KeyEvent.h"
#include "Neon/Event/MouseEvent.h"

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
        float m_Time = 0.0f;
    };
}  // namespace Neon
