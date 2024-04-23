#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>

/* Globals */
int gScreenHeight = 640;
int gScreenWidth = 480;
SDL_Window*     gGraphicsApplicationWindow = nullptr;
SDL_GLContext   gOpenGLContext = nullptr;

bool gQuit = false;

void GetOpenGLVersionInfo()
{
    std::cout << "Vendor: " << glGetString(GL_VENDOR) <<  std::endl;
    std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void InitializeProgram()
{
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        std::cout << "SDL2 could not initialize video subsystem" << std::endl;
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    gGraphicsApplicationWindow = SDL_CreateWindow("OpenGL First Program", 30, 30,
        gScreenWidth, gScreenHeight,
        SDL_WINDOW_OPENGL);

    if (gGraphicsApplicationWindow == nullptr)
    {
        std::cout << "SDL_Window was not able to be created" << std::endl;
        exit(1);   
    }

    gOpenGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);

    if (gOpenGLContext == nullptr)
    {
        std::cout << "OpenGL context not available!" << std::endl;
    }

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cout << "Glad was not initialized" << std::endl;
        exit(1);
    }

    GetOpenGLVersionInfo();
}

void Input()
{
    SDL_Event e;

    while ( SDL_PollEvent(&e) != 0 )
    {
        if ( e.type == SDL_QUIT )
        {
            std::cout << "Goodbye!" << std::endl;
            gQuit = true;
        }
    }
}

void PreDraw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT );
}

void Draw()
{

}

void MainLoop()
{
    while (!gQuit)
    {
        Input();
        PreDraw();
        Draw();
        SDL_GL_SwapWindow(gGraphicsApplicationWindow);
    }
}

void CleanUp()
{
    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    InitializeProgram();
    MainLoop();
    CleanUp();
    return EXIT_SUCCESS;
}