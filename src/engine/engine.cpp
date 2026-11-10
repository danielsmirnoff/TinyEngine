#include "engine.h"


int main(void)
{
    Engine app;
    return app.Run();
}

int Engine::Run() {
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(720, 540, "Game Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    SubsystemRegistry subsystemRegistry = SubsystemRegistry();
    subsystemRegistry.Initialize();

    // Init
    Start();

    // Loop
    while (!glfwWindowShouldClose(window))
    {
        Update();
        Render();

        glClear(GL_COLOR_BUFFER_BIT);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    Cleanup();

    // Cleanup
    glfwTerminate();
    return 0;
}

void Engine::Start() {

}

void Engine::Update() {

}

void Engine::Render() {

}

void Engine::Cleanup() {

}