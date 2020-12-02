#include "LayerStack.h"

namespace Neon {

    LayerStack::LayerStack() { m_LayerInsertIndex = 0; }

    LayerStack::~LayerStack() { m_Layers.clear(); }

    void LayerStack::PushLayer(const Ref<Layer>& layer) {
        if (layer != nullptr) {
            m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
            m_LayerInsertIndex++;
            layer->OnAttach();
        }
    }

    void LayerStack::PopLayer(const Ref<Layer>& layer) {
        auto it = std::find(begin(), begin() + m_LayerInsertIndex, layer);
        if (it != begin() + m_LayerInsertIndex) {
            layer->OnDetach();

            m_Layers.erase(it);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PushOverlay(const Ref<Layer>& layer) {
        m_Layers.emplace_back(layer);
        layer->OnAttach();
    }

    void LayerStack::PopOverlay(const Ref<Layer>& layer) {
        auto it = std::find(begin() + m_LayerInsertIndex, end(), layer);
        if (it != end()) {
            layer->OnDetach();
            m_Layers.erase(it);
        }
    }
}  // namespace Neon
