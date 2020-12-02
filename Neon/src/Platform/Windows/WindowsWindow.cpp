#include "WindowsWindow.h"

#include "Neon/Event/ApplicationEvent.h"
#include "Neon/Event/KeyEvent.h"
#include "Neon/Event/MouseEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Neon {
    static bool GLFWInitialized = false;

    Ref<Window> Window::Create(const WindowSettings& settings) { return CreateRef<WindowsWindow>(settings); }

    WindowsWindow::WindowsWindow(const WindowSettings& settings) { Init(settings); }

    WindowsWindow::~WindowsWindow() { Shutdown(); }

    static void GLFWErrorCallback(int error, const char* desc) { NEO_CORE_ERROR("GLFW Error {0}: {1}", error, desc); }

    void WindowsWindow::Init(const WindowSettings& settings) {
        m_Data.Title = settings.Title;
        m_Data.Width = settings.Width;
        m_Data.Height = settings.Height;

        NEO_CORE_INFO("Creating window \"{0}\" with Height={1} and Width={2})", settings.Title, settings.Width,
                      settings.Height);

        if (!GLFWInitialized) {
            int success = glfwInit();
            NEO_CORE_ASSERT(success, "Could not init GLFW");

            glfwSetErrorCallback(GLFWErrorCallback);
            GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

        m_Context = CreateScope<OpenGLContext>(m_Window);
        m_Context->Init();

        glfwSetWindowUserPointer(m_Window, &m_Data);

        int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        NEO_CORE_ASSERT(gladStatus, "Could not init Glad")

        SetVSync(true);

        InitEvents();
    }

    void WindowsWindow::InitEvents() {
        // Window
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowClosedEvent event;
            data.EventCallback(event);
        });
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowResizedEvent event(width, height);
            data.EventCallback(event);
        });

        // Key
        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

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

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keyCode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keyCode);
            data.EventCallback(event);
        });

        // Mouse
        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

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
        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)x, (float)y);
            data.EventCallback(event);
        });
        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });
    }

    void WindowsWindow::Shutdown() { glfwDestroyWindow(m_Window); }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    // == Accessors ==================
    uint16_t WindowsWindow::GetWidth() const { return m_Data.Width; }

    uint16_t WindowsWindow::GetHeight() const { return m_Data.Height; }

    void WindowsWindow::SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

    void WindowsWindow::SetVSync(bool enabled) {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }

        m_Data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() { return m_Data.VSync; }
    // ===============================
}  // namespace Neon
