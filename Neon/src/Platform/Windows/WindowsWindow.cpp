#include "WindowsWindow.h"

#include "Core.h"
#include "Neon/Event/ApplicationEvent.h"
#include "Neon/Event/KeyEvent.h"
#include "Neon/Event/MouseEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"

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
    
    static void GLFWErrorCallback(int error, const char *desc) {
        NEO_CORE_ERROR("GLFW Error {0}: {1}", error, desc);
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
            
            glfwSetErrorCallback(GLFWErrorCallback);
            GLFWInitialized = true;
        }
        
        _window = glfwCreateWindow(_data.Width, _data.Height, _data.Title.c_str(), nullptr, nullptr);
        
        _context = new OpenGLContext(_window);
        _context->Init();
        
        glfwSetWindowUserPointer(_window, &_data);
        
        int gladStatus = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        NEO_CORE_ASSERT(gladStatus, "Could not init Glad")
        
        SetVSync(true);
        
        InitEvents();
    }
    
    void WindowsWindow::InitEvents() {
        // Window
        glfwSetWindowCloseCallback(_window, [](GLFWwindow *window) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            WindowClosedEvent event;
            data.EventCallback(event);
        });
        glfwSetWindowSizeCallback(_window, [](GLFWwindow *window, int width, int height) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            WindowResizedEvent event(width, height);
            data.EventCallback(event);
        });
        
        // Key
        glfwSetKeyCallback(_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
            }
        });
        
        glfwSetCharCallback(_window, [](GLFWwindow *window, unsigned int keyCode) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keyCode);
            data.EventCallback(event);
        });
        
        // Mouse
        glfwSetMouseButtonCallback(_window, [](GLFWwindow *window, int button, int action, int mods) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            
            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });
        glfwSetCursorPosCallback(_window, [](GLFWwindow *window, double x, double y) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float) x, (float) y);
            data.EventCallback(event);
        });
        glfwSetScrollCallback(_window, [](GLFWwindow *window, double xOffset, double yOffset) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float) xOffset, (float) yOffset);
            data.EventCallback(event);
        });
    }
    
    void WindowsWindow::Shutdown() {
        glfwDestroyWindow(_window);
    }
    
    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        _context->SwapBuffers();
    }
    
    // == Accessors ==================
    uint16_t WindowsWindow::GetWidth() const {
        return _data.Width;
    }
    
    uint16_t WindowsWindow::GetHeight() const {
        return _data.Height;
    }
    
    void WindowsWindow::SetEventCallback(const EventCallbackFn &callback) {
        _data.EventCallback = callback;
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
    // ===============================
}