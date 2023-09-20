/*

settings.hpp

Stores the settings of the application

*/

// header guard
#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE #OpenGL Engine

#define MOVE_SPEED 500.0f
#define ROTATE_SPEED 1000.0f


// If this macro is undefined, the GLCall() macro will be undefined too, leading to higher performance because of less checks of errors
#define DEBUG

#endif