#pragma once

#include <string>

#include "Neon/Core/TimeStep.h"
#include "Neon/Event/Event.h"

namespace Neon {
    class Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnUpdate(TimeStep timeStep) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}
        virtual void OnDetach() {}

        inline const std::string& GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };
}  // namespace Neon
