#include "LayerStack.h"

namespace Neon {

    LayerStack::LayerStack() {
        m_LayerInsertIndex = 0;
    }

    LayerStack::~LayerStack() {
        for (Layer* layer : m_Layers) {
            delete layer;
        }
        m_Layers.clear();
    }

    void LayerStack::PushLayer(Layer* layer) {
        if (layer != nullptr) {
            m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
            m_LayerInsertIndex++;
            layer->OnAttach();
        }
    }

    void LayerStack::PopLayer(Layer* layer) {
        auto it = std::find(begin(), begin() + m_LayerInsertIndex, layer);
        if (it != end()) {
            layer->OnDetach();

            m_Layers.erase(it);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PushOverlay(Layer* layer) {
        m_Layers.emplace_back(layer);
        layer->OnAttach();
    }

    void LayerStack::PopOverlay(Layer* layer) {
        auto it = std::find(begin() + m_LayerInsertIndex, end(), layer);
        if (it != end()) {
            layer->OnDetach();
            m_Layers.erase(it);
        }
    }
}  // namespace Neon
