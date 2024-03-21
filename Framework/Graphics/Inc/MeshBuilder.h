#pragma once
#include "MeshTypes.h"

namespace DubEngine::Graphics
{
    class MeshBuilder
    {
    public:
        // Position and Color
        static MeshPC CreateCubePC(float size, Color color);
        static MeshPC CreateRectanglePC(float width, float height, float depth);
        static MeshPC CreatePlanePC(int numRows, int numColumns, float spacing);
        static MeshPC CreateCylinderPC(int slices, int rings);
        static MeshPC CreateSpherePC(int slices, int rings, float radius);

        // Position and UV
        static MeshPX CreateCubePX(float size);
        static MeshPX CreateSpherePX(int slices, int rings, float radius);
        static Mesh CreateSphere(int slices, int rings, float radius);
        static Mesh CreatePlane(int numRows, int numColumns, float spacing);
        static Mesh CreateCube(float size);

        static MeshPX CreateScreenQuad();
    };
}