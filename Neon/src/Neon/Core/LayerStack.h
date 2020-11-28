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

        void PushLayer(const Ref<Layer>& layer);
        void PopLayer(const Ref<Layer>& layer);

        void PushOverlay(const Ref<Layer>& layer);
        void PopOverlay(const Ref<Layer>& layer);

        std::vector<Ref<Layer>>::iterator begin() { return m_Layers.begin(); }

        std::vector<Ref<Layer>>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Ref<Layer>> m_Layers;
        uint32_t m_LayerInsertIndex;
    };
}  // namespace Neon
