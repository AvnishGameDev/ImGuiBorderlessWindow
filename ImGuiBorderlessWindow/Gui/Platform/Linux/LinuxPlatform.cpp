#include "LinuxPlatform.h"
#include "../../Gui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdlib>
#include <GL/gl.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#include <GLFW/glfw3native.h>

LinuxPlatform* LinuxPlatform::instance = nullptr;

// Window dragging variables
static bool isDragging = false;
static double dragStartX = 0;
static double dragStartY = 0;

// Function to set window properties for transparency and shape
static void SetupWindow(GLFWwindow* window) {
    Display* display = glfwGetX11Display();
    if (!display) return;

    Window xwindow = glfwGetX11Window(window);
    if (!xwindow) return;

    // Get atoms
    Atom wm_type = XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    Atom wm_type_dialog = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
    Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
    Atom wm_state_skip_taskbar = XInternAtom(display, "_NET_WM_STATE_SKIP_TASKBAR", False);
    Atom wm_state_skip_pager = XInternAtom(display, "_NET_WM_STATE_SKIP_PAGER", False);
    Atom wm_state_stays_on_top = XInternAtom(display, "_NET_WM_STATE_STAYS_ON_TOP", False);
    Atom wm_state_above = XInternAtom(display, "_NET_WM_STATE_ABOVE", False);
    Atom wm_state_modal = XInternAtom(display, "_NET_WM_STATE_MODAL", False);
    Atom wm_opacity = XInternAtom(display, "_NET_WM_WINDOW_OPACITY", False);

    // Set window type to dialog
    XChangeProperty(display, xwindow, wm_type, XA_ATOM, 32, PropModeReplace, (unsigned char*)&wm_type_dialog, 1);

    // Set window states
    Atom states[] = {
        wm_state_skip_taskbar,
        wm_state_skip_pager,
        wm_state_stays_on_top,
        wm_state_above,
        wm_state_modal
    };
    XChangeProperty(display, xwindow, wm_state, XA_ATOM, 32, PropModeReplace, (unsigned char*)states, 5);

    // Set window opacity to fully opaque
    unsigned long opacity = 0xffffffff;
    XChangeProperty(display, xwindow, wm_opacity, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)&opacity, 1);
}

// GLFW callback for mouse button events
static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            // Check if click is in title bar area (top 19 pixels)
            if (y <= 19) {
                isDragging = true;
                dragStartX = x;
                dragStartY = y;
            }
        } else if (action == GLFW_RELEASE) {
            isDragging = false;
        }
    }
}

// GLFW callback for cursor movement
static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    if (isDragging) {
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        glfwSetWindowPos(window, 
            x + (int)(xpos - dragStartX),
            y + (int)(ypos - dragStartY));
    }
}

bool LinuxPlatform::CreatePlatformWindow(const std::string& windowName) {
    // Initialize GLFW
    if (!glfwInit()) {
        return false;
    }

    // Create window with OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // Borderless window
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);   // Keep window on top
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Disable resizing
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);    // Make sure window is visible
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);    // Give it focus
    glfwWindowHint(GLFW_ALPHA_BITS, 8);         // Enable alpha channel
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // Enable transparent framebuffer

    window = glfwCreateWindow(Gui::WIDTH, Gui::HEIGHT, windowName.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return false;
    }

    // Set up window dragging callbacks
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    glfwMakeContextCurrent(window);

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Setup window properties
    SetupWindow(window);

    return true;
}

void LinuxPlatform::InitImguiImpl() {
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void LinuxPlatform::ShutdownImguiImpl() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
}

bool LinuxPlatform::DestroyPlatformWindow() {
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
    return true;
}

void LinuxPlatform::BeginRender() {
    glfwPollEvents();
    
    if (glfwWindowShouldClose(window)) {
        isRunning = false;
        return;
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
}

void LinuxPlatform::EndRender() {
    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    
    // Clear with transparent background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Enable blending for ImGui rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

std::string LinuxPlatform::GetAssetPath(const std::string& relativePath) {
    return "Assets/"+relativePath;
}

void LinuxPlatform::LaunchURL(const std::string& URL) {
    std::string command = "xdg-open " + URL;
    system(command.c_str());
}


