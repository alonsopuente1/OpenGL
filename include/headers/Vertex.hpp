/*

Vertex.hpp

Defines a Vertex struct that is used for Vertex Buffer Objects

*/

// header guard
#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
    float pos[3] = {0.0f}; // Position Attribute
    float col[3] = {0.0f}; // Colour Attribute
    float tex[2] = {0.0f}; // Tex-Coord Attribute
};

#endif