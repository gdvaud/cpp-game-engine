#include "neon_pch.h"

#include "LayerStack.h"

namespace Neon {
    
    LayerStack::LayerStack() {
        _insertIterator = begin();
    }
    
    LayerStack::~LayerStack() {
        for (Layer *layer : _layers) {
            delete layer;
        }
        _layers.clear();
    }
    
    void LayerStack::PushLayer(Layer *layer) {
        _insertIterator = _layers.emplace(_insertIterator, layer);
        layer->OnAttach();
    }
    
    void LayerStack::PopLayer(Layer *layer) {
        auto it = std::find(begin(), end(), layer);
        if (it != end()) {
            _layers.erase(it);
            _insertIterator--;
            
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