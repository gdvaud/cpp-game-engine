#include "LayerStack.h"

namespace Neon {
    
    LayerStack::LayerStack() {
        _layerInsertIndex = 0;
    }
    
    LayerStack::~LayerStack() {
        for (Layer *layer : _layers) {
            delete layer;
        }
        _layers.clear();
    }
    
    void LayerStack::PushLayer(Layer *layer) {
        if (layer != nullptr) {
            _layers.emplace(_layers.begin() + _layerInsertIndex, layer);
            _layerInsertIndex++;
            layer->OnAttach();
        }
    }
    
    void LayerStack::PopLayer(Layer *layer) {
        auto it = std::find(begin(), end(), layer);
        if (it != end()) {
            _layers.erase(it);
            _layerInsertIndex--;
            
            layer->OnDetach();
        }
    }
    
    void LayerStack::PushOverlay(Layer *layer) {
        _layers.emplace_back(layer);
        layer->OnAttach();
    }
    
    void LayerStack::PopOverlay(Layer *layer) {
        auto it = std::find(begin(), end(), layer);
        if (it != end()) {
            _layers.erase(it);
            
            layer->OnDetach();
        }
    }
}