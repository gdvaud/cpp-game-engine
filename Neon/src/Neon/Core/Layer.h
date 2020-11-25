#pragma once

#include <string>

#include "Neon/Event/Event.h"

namespace Neon {
    class Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnUpdate() {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}
        virtual void OnDetach() {}

        inline const std::string& GetName() const { return _debugName; }

    protected:
        std::string _debugName;
    };
}  // namespace Neon
