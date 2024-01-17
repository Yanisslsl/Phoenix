// LayerStack.h

#pragma once
#include <vector>

#include "../../../Core.h"
#include "../../Layer/include/Layer.h"
// #include "Windows/Core/Application/include/Application.h"


namespace Phoenix
{
    class PHOENIX_API LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<Layer*> m_Layers;
        std::vector<Layer*> m_Overlays;

        // @TODO: change this to a vector of unique_ptr // Add badge to Layer
        friend class Application;
    };
}
