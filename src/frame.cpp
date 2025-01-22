#include <iostream>

#include "frame.h"
#include "draw.h"
#include "movement.h"
#include "settings.h"

namespace FRAME
{
    int width = 600;
    int height = 500;
    GLFWwindow* window = nullptr;
    DRAW* draw = nullptr;
    MOVEMENT* movement = nullptr;
    std::thread playerControl;
}

inline void FRAME::InitGlfwFlags()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}

inline void FRAME::RenderLoop()
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start frame
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Rendering
        draw->Update();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);

    }
}

inline void FRAME::SetupFrame()
{
    InitGlfwFlags();
    
    window = glfwCreateWindow(width, height, "Pong Ex", NULL, NULL);


    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // access settings (reference to imguiio struc) - can use this for keyboard/mouse and gamepad navigation
    ImGuiIO& io = ImGui::GetIO();
    // avoid warnings
    (void)io;

    draw = new DRAW(width, height);
    movement = new MOVEMENT(window, draw, width, height);

    glMatrixMode(GL_PROJECTION);  // Switch to projection matrix
    glLoadIdentity();             // Reset the projection matrix
    glOrtho(0, width, 0, height, -1, 1);  // Set the orthographic projection
    glMatrixMode(GL_MODELVIEW);   // Switch back to modelview matrix
    glLoadIdentity();             // Reset the modelview matrix

    glViewport(0, 0, width, height);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    playerControl = std::thread(&MOVEMENT::StartMovement, movement);
    RenderLoop();
}

inline void FRAME::UnloadFrame()
{
    delete movement;
    playerControl.join();
    delete draw;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}