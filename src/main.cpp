#include "headers/game.hpp"

int main(int argc, char** argv)
{
    Game game("Hello OpenGL", WINDOW_WIDTH, WINDOW_HEIGHT);

    game.MakeCam();

    float old_time = (float)glfwGetTime() / 1000.0f;

    while(game.Run()) 
    {  
        float new_time = (float)glfwGetTime() / 1000.0f;
        float delta_time = new_time - old_time;
        old_time = new_time;

        game.HandleEvents();
        game.Update(delta_time);
        game.Draw();
    }

    return 0;
}