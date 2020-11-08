#include "neon_pch.h"

#include "WindowsWindow.h"

namespace Neon {
    static bool GLFWInitialized = false;
    
    Window *Window::Create(const WindowSettings &settings) {
        return new WindowsWindow(settings);
    }
    
    WindowsWindow::WindowsWindow(const WindowSettings &settings) {
        Init(settings);
    }
    
    WindowsWindow::~WindowsWindow() {
        Shutdown();
    }
    
    void WindowsWindow::Init(const WindowSettings &settings) {
        _data.Title = settings.Title;
        _data.Width = settings.Width;
        _data.Height = settings.Height;
        
        NEO_CORE_INFO("Creating window \"{0}\" with Height={1} and Width={2})",
                      settings.Title, settings.Width, settings.Height);
        
        if (!GLFWInitialized) {
            int success = glfwInit();
            NEO_CORE_ASSERT(success, "Could not init GLFW");
            
            GLFWInitialized = true;
        }
        
        _window = glfwCreateWindow(_data.Width, _data.Height, _data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, &_data);
        
        SetVSync(true);
    }
    
    void WindowsWindow::Shutdown() {
        glfwDestroyWindow(_window);
    }
    
    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(_window);
    }
    
    uint16_t WindowsWindow::GetWidth() const {
        return _data.Width;
    }
    
    uint16_t WindowsWindow::GetHeight() const {
        return _data.Height;
    }
    
    void WindowsWindow::SetEventCallback(std::function<bool(Event &)> callback) {
        _data.Callback = callback;
    }
    
    void WindowsWindow::SetVSync(bool enabled) {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
        
        _data.VSync = enabled;
    }
    
    bool WindowsWindow::IsVSync() {
        return _data.VSync;
    }
}