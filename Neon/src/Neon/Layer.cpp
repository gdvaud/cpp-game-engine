#include "neon_pch.h"

#include "Layer.h"

namespace Neon {
    Layer::Layer(const std::string &name)
            : _debugName(name) {}
    
    Layer::~Layer() {}
}