#pragma once

#include "Layer.h"
#include "Neon/Event/ApplicationEvent.h"
#include "Neon/Event/KeyEvent.h"
#include "Neon/Event/MouseEvent.h"

namespace Neon {
    class LayerStack {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

        void PushOverlay(Layer* layer);
        void PopOverlay(Layer* layer);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

        std::vector<Layer*>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Layer*> m_Layers;
        uint32_t m_LayerInsertIndex;
    };
}  // namespace Neon
