#pragma once

#include "neon_pch.h"

#include "Layer.h"

#include "Neon/Event/ApplicationEvent.h"
#include "Neon/Event/KeyEvent.h"
#include "Neon/Event/MouseEvent.h"

namespace Neon {
    class LayerStack {
    public:
        LayerStack();
        ~LayerStack();
        
        void PushLayer(Layer *layer);
        void PopLayer(Layer *layer);
        
        void PushOverlay(Layer *layer);
        void PopOverlay(Layer *layer);
        
        std::vector<Layer *>::iterator begin() { return _layers.begin(); }
        
        std::vector<Layer *>::iterator end() { return _layers.end(); }
    
    private:
        std::vector<Layer *> _layers;
        uint32_t _layerInsertIndex;
    };
}