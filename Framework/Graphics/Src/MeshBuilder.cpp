#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace DubEngine;
using namespace DubEngine::Graphics;

namespace
{
    Color GetNextColor(int& index)
    {
        constexpr Color colorTable[] = {
            Colors::DarkMagenta,
            Colors::LightSkyBlue,
            Colors::Coral,
            Colors::Red,
            Colors::Green,
            Colors::Yellow,
            Colors::DarkTurquoise,
            Colors::Snow
        };

        index = (index + 1) % std::size(colorTable);
        return colorTable[index];
    }

    void CreateCubeIndices(std::vector<uint32_t>& indices)
    {
        indices = {
            // front face
            0, 1, 3,
            1, 2, 3,

            // back
            5, 4, 7,
            5, 7, 6,

            // right
            1, 5, 2,
            5, 6, 2,

            // left
            4, 0, 3,
            4, 3, 7,

            // top
            0, 4, 1,
            4, 5, 1,

            // bottom
            6, 7, 3,
            6, 3, 2
        };
    }

    void CreatePlaneIndices(std::vector<uint32_t>& indices, int numRows, int numColumns)
    {
        for (int r = 0; r < numRows; ++r)
        {
            for (int c = 0; c < numColumns; ++c)
            {
                int i = r * (numColumns + 1) + c;

                // triangle 1
                indices.push_back(i);
                indices.push_back(i + numColumns + 1);
                indices.push_back(i + 1);

                // triangle 2
                indices.push_back(i + 1);
                indices.push_back(i + numColumns + 1);
                indices.push_back(i + numColumns + 2);
            }
        }
    }

    void CreateCapsIndices(std::vector<uint32_t>& indices, int slices, int topIndex)
    {
        int bottomIndex = topIndex + 1;
        // top indices
        for (int s = 0; s < slices; ++s)
        {
            // bottom triangle
            indices.push_back(s);
            indices.push_back(s + 1);
            indices.push_back(bottomIndex);

            // top triangle
            int topRow = topIndex - slices - 1 + s;
            indices.push_back(topIndex);
            indices.push_back(topRow + 1);
            indices.push_back(topRow);
        }
    }

    void CreateCapsPC(MeshPC& mesh, int slices, float halfHeight)
    {
        int index = rand() % 100;

        uint32_t topIndex = mesh.vertices.size();
        uint32_t bottomIndex = topIndex + 1;
        // top center
        mesh.vertices.push_back({ {0.0f, halfHeight, 0.0f}, GetNextColor(index) });
        // bottom center
        mesh.vertices.push_back({ {0.0f, -halfHeight, 0.0f}, GetNextColor(index) });

        CreateCapsIndices(mesh.indices, slices, topIndex);
    }
}

MeshPC MeshBuilder::CreateCubePC(float size, Color color)
{
    MeshPC mesh;

    const float hs = size * 0.5;
    // front
    mesh.vertices.push_back({ { -hs, hs, -hs }, color });  // FTL  0
    mesh.vertices.push_back({ { hs, hs, -hs }, color });   // FTR  1
    mesh.vertices.push_back({ { hs, -hs, -hs }, color });  // FBR  2
    mesh.vertices.push_back({ { -hs, -hs, -hs }, color }); // FBL  3

    // back
    mesh.vertices.push_back({ { -hs, hs, hs }, color });   // BTL  4
    mesh.vertices.push_back({ { hs, hs, hs }, color });    // BTR  5
    mesh.vertices.push_back({ { hs, -hs, hs }, color });   // BBR  6
    mesh.vertices.push_back({ { -hs, -hs, hs }, color });  // BBL  7

    CreateCubeIndices(mesh.indices);

    return mesh;
}

MeshPC MeshBuilder::CreateRectanglePC(float width, float height, float depth)
{
    MeshPC mesh;

    int index = rand() % 100;
    const float hw = width * 0.5;
    const float hh = height * 0.5;
    const float hd = depth * 0.5;

    // front
    mesh.vertices.push_back({ { -hw, hh, -hd }, GetNextColor(index) });  // FTL  0
    mesh.vertices.push_back({ { hw, hh, -hd }, GetNextColor(index) });   // FTR  1
    mesh.vertices.push_back({ { hw, -hh, -hd }, GetNextColor(index) });  // FBR  2
    mesh.vertices.push_back({ { -hw, -hh, -hd }, GetNextColor(index) }); // FBL  3

    // back
    mesh.vertices.push_back({ { -hw, hh, hd }, GetNextColor(index) });   // BTL  4
    mesh.vertices.push_back({ { hw, hh, hd }, GetNextColor(index) });    // BTR  5
    mesh.vertices.push_back({ { hw, -hh, hd }, GetNextColor(index) });   // BBR  6
    mesh.vertices.push_back({ { -hw, -hh, hd }, GetNextColor(index) });  // BBL  7

    CreateCubeIndices(mesh.indices);

    return mesh;
}
MeshPC MeshBuilder::CreatePlanePC(int numRows, int numColumns, float spacing)
{
    MeshPC mesh;
    int index = rand() % 100;

    const float halfPlaneWidth = static_cast<float>(numColumns) * spacing * 0.5f;
    const float halfPlaneHeight = static_cast<float>(numRows) * spacing * 0.5f;

    float x = -halfPlaneWidth;
    float y = -halfPlaneHeight;

    for (int r = 0; r <= numRows; ++r)
    {
        for (int c = 0; c <= numColumns; ++c)
        {
            mesh.vertices.push_back({ {x, y, 0.0f}, GetNextColor(index) });
            x += spacing;
        }
        x = -halfPlaneWidth;
        y += spacing;
    }

    CreatePlaneIndices(mesh.indices, numRows, numColumns);

    return mesh;
}
MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
{
    MeshPC mesh;
    int index = rand() % 100;
    const float halfHeight = static_cast<float>(rings) * 0.5f;

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        for (int s = 0; s < slices + 1; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / static_cast<float>(slices)) * DEMath::Constants::TwoPi;

            mesh.vertices.push_back({
                {
                    sin(rotation),
                    ring - halfHeight,
                    -cos(rotation)
                }, 
                GetNextColor(index) });
        }
    }


    CreatePlaneIndices(mesh.indices, rings, slices);

    CreateCapsPC(mesh, slices, halfHeight);

    return mesh;
}
MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
{
    MeshPC mesh;
    int index = rand() % 100;

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = ring * (DEMath::Constants::Pi / static_cast<float>((rings - 1)));
        for (int s = 0; s < slices + 1; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / static_cast<float>(slices)) * DEMath::Constants::TwoPi;

            mesh.vertices.push_back({
                {
                    radius * sin(rotation) * sin(phi),
                    radius * cos(phi),
                    radius * cos(rotation) * sin(phi)
                },
                GetNextColor(index) });
        }
    }


    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}


MeshPX MeshBuilder::CreateCubePX(float size)
{
    MeshPX mesh;

    const float hs = size * 0.5;
    // front
    mesh.vertices.push_back({ { -hs, hs, -hs }, { 0.25f, 0.33f } });  // FTL  0
    mesh.vertices.push_back({ { hs, hs, -hs }, { 0.5f, 0.33f } });   // FTR  1
    mesh.vertices.push_back({ { hs, -hs, -hs }, { 0.5f, 0.66f } });  // FBR  2
    mesh.vertices.push_back({ { -hs, -hs, -hs }, { 0.25f, 0.66f } }); // FBL  3

    // back
    mesh.vertices.push_back({ { -hs, hs, hs }, { 0.0f, 0.33f } });   // BTL  4
    mesh.vertices.push_back({ { hs, hs, hs }, { 0.5f, 0.0f } });    // BTR  5
    mesh.vertices.push_back({ { hs, -hs, hs }, { 0.5f, 1.0f } });   // BBR  6
    mesh.vertices.push_back({ { -hs, -hs, hs }, { 0.25f, 1.0f } });  // BBL  7

    CreateCubeIndices(mesh.indices);

    return mesh;
}

MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
{
    MeshPX mesh;

    float uStep = 1.0f / static_cast<float>(slices);
    float vStep = 1.0f / static_cast<float>(rings);

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = ring * (DEMath::Constants::Pi / static_cast<float>((rings - 1)));
        for (int s = 0; s < slices + 1; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / static_cast<float>(slices)) * DEMath::Constants::TwoPi;

            float u = 1.0f - (uStep * slice);
            float v = vStep * ring;
            mesh.vertices.push_back({
                {
                    radius * sin(rotation) * sin(phi),
                    radius * cos(phi),
                    radius * cos(rotation) * sin(phi)
                },
                { u, v } });
        }
    }


    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}
Mesh MeshBuilder::CreateSphere(int slices, int rings, float radius)
{
    Mesh mesh;

    float uStep = 1.0f / static_cast<float>(slices);
    float vStep = 1.0f / static_cast<float>(rings);

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = ring * (DEMath::Constants::Pi / static_cast<float>((rings - 1)));
        for (int s = 0; s < slices + 1; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / static_cast<float>(slices)) * DEMath::Constants::TwoPi;

            float u = 1.0f - (uStep * slice);
            float v = vStep * ring;

            float x = radius * sin(rotation) * sin(phi);
            float y = radius * cos(phi);
            float z = radius * cos(rotation) * sin(phi);
            const DEMath::Vector3 pos = {x, y, z};
            const DEMath::Vector3 norm = DEMath::Normalize(pos);
            const DEMath::Vector3 tan = DEMath::Normalize({ -z, 0.0f, x });
            mesh.vertices.push_back( { pos, norm, tan, { u, v } });
        }
    }

    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}

Mesh MeshBuilder::CreatePlane(int numRows, int numColumns, float spacing)
{
    Mesh mesh;

    const float halfPlaneWidth = static_cast<float>(numColumns) * spacing * 0.5f;
    const float halfPlaneHeight = static_cast<float>(numRows) * spacing * 0.5f;

    float x = -halfPlaneWidth;
    float z = -halfPlaneHeight;

    const float uStep = 1.0f / static_cast<float>(numColumns);
    const float vStep = 1.0f / static_cast<float>(numRows);

    const DEMath::Vector3 n = DEMath::Vector3::YAxis;
    const DEMath::Vector3 t = DEMath::Vector3::XAxis;

    for (int r = 0; r <= numRows; ++r)
    {
        float rf = static_cast<float>(r);
        for (int c = 0; c <= numColumns; ++c)
        {
            float cf = static_cast<float>(c);

            float u = uStep * cf;
            float v = 1.0f - (vStep * rf);

            mesh.vertices.push_back({ {x, 0.0f, z}, n, t, DEMath::Vector2(u, v) });
            x += spacing;
        }
        x = -halfPlaneWidth;
        z += spacing;
    }

    CreatePlaneIndices(mesh.indices, numRows, numColumns);

    return mesh;
}

Mesh MeshBuilder::CreateCube(float size)
{
    Mesh mesh;


    float hs = size * 0.5f;


    // FRONT
    mesh.vertices.push_back({ DEMath::Vector3{  hs,  hs, -hs }, DEMath::Vector3::ZAxis, DEMath::Vector3::XAxis, DEMath::Vector2(0.5f, 0.33f) }); // Top Right Close
    mesh.vertices.push_back({ DEMath::Vector3{ -hs, -hs, -hs }, DEMath::Vector3::ZAxis, DEMath::Vector3::XAxis, DEMath::Vector2(0.25f, 0.66f) }); // Bottom Left Close
    mesh.vertices.push_back({ DEMath::Vector3{  hs, -hs, -hs }, DEMath::Vector3::ZAxis, DEMath::Vector3::XAxis, DEMath::Vector2(0.5f, 0.66f) }); // Bottom Right Close


    mesh.vertices.push_back({ DEMath::Vector3{  hs,  hs, -hs }, DEMath::Vector3::ZAxis, DEMath::Vector3::XAxis, DEMath::Vector2(0.5f, 0.33f) }); // Top Right Close
    mesh.vertices.push_back({ DEMath::Vector3{ -hs,  hs, -hs }, DEMath::Vector3::ZAxis, DEMath::Vector3::XAxis, DEMath::Vector2(0.25f, 0.33f) }); // Top Left Close
    mesh.vertices.push_back({ DEMath::Vector3{ -hs, -hs, -hs }, DEMath::Vector3::ZAxis, DEMath::Vector3::XAxis, DEMath::Vector2(0.25f, 0.66f) }); // Bottom Left Close


    // BACK
    mesh.vertices.push_back({ DEMath::Vector3{ -hs,  hs,  hs }, -DEMath::Vector3::ZAxis, -DEMath::Vector3::XAxis, DEMath::Vector2(1.0f, 0.33f) }); // Top Left Far
    mesh.vertices.push_back({ DEMath::Vector3{  hs, -hs,  hs }, -DEMath::Vector3::ZAxis, -DEMath::Vector3::XAxis, DEMath::Vector2(0.75f, 0.66f) }); // Bottom Right Far
    mesh.vertices.push_back({ DEMath::Vector3{ -hs, -hs,  hs }, -DEMath::Vector3::ZAxis, -DEMath::Vector3::XAxis, DEMath::Vector2(1.0f, 0.66f) }); // Bottom Left Far


    mesh.vertices.push_back({ DEMath::Vector3{ -hs,  hs,  hs }, -DEMath::Vector3::ZAxis, -DEMath::Vector3::XAxis, DEMath::Vector2(1.0f, 0.33f) }); // Top Left Far
    mesh.vertices.push_back({ DEMath::Vector3{  hs,  hs,  hs }, -DEMath::Vector3::ZAxis, -DEMath::Vector3::XAxis, DEMath::Vector2(0.75f, 0.33f) }); // Top Right Far
    mesh.vertices.push_back({ DEMath::Vector3{  hs, -hs,  hs }, -DEMath::Vector3::ZAxis, -DEMath::Vector3::XAxis, DEMath::Vector2(0.75f, 0.66f) }); // Bottom Right Far


    // RIGHT
    mesh.vertices.push_back({ DEMath::Vector3{  hs,  hs,  hs }, DEMath::Vector3::XAxis, DEMath::Vector3::ZAxis, DEMath::Vector2(0.75f, 0.33f) }); // Top Right Far
    mesh.vertices.push_back({ DEMath::Vector3{  hs, -hs, -hs }, DEMath::Vector3::XAxis, DEMath::Vector3::ZAxis, DEMath::Vector2(0.5f, 0.66f) }); // Bottom Right Close
    mesh.vertices.push_back({ DEMath::Vector3{  hs, -hs,  hs }, DEMath::Vector3::XAxis, DEMath::Vector3::ZAxis, DEMath::Vector2(0.75f, 0.66f) }); // Bottom Right Far


    mesh.vertices.push_back({ DEMath::Vector3{  hs,  hs,  hs }, DEMath::Vector3::XAxis, DEMath::Vector3::ZAxis, DEMath::Vector2(0.75f, 0.33f) }); // Top Right Far
    mesh.vertices.push_back({ DEMath::Vector3{  hs,  hs, -hs }, DEMath::Vector3::XAxis, DEMath::Vector3::ZAxis, DEMath::Vector2(0.5f, 0.33f) }); // Top Right Close
    mesh.vertices.push_back({ DEMath::Vector3{  hs, -hs, -hs }, DEMath::Vector3::XAxis, DEMath::Vector3::ZAxis, DEMath::Vector2(0.5f, 0.66f) }); // Bottom Right Close


    // Left
    mesh.vertices.push_back({ DEMath::Vector3{ -hs,  hs, -hs }, -DEMath::Vector3::XAxis, -DEMath::Vector3::ZAxis, DEMath::Vector2(0.25f, 0.33f) }); // Top Left Close
    mesh.vertices.push_back({ DEMath::Vector3{ -hs, -hs,  hs }, -DEMath::Vector3::XAxis, -DEMath::Vector3::ZAxis, DEMath::Vector2(0.0f, 0.66f) }); // Bottom Left Far
    mesh.vertices.push_back({ DEMath::Vector3{ -hs, -hs, -hs }, -DEMath::Vector3::XAxis, -DEMath::Vector3::ZAxis, DEMath::Vector2(0.25f, 0.66f) }); // Bottom Left Close


    mesh.vertices.push_back({ DEMath::Vector3{ -hs,  hs, -hs }, -DEMath::Vector3::XAxis, -DEMath::Vector3::ZAxis, DEMath::Vector2(0.25f, 0.33f) }); // Top Left Close
    mesh.vertices.push_back({ DEMath::Vector3{ -hs,  hs,  hs }, -DEMath::Vector3::XAxis, -DEMath::Vector3::ZAxis, DEMath::Vector2(0.0f, 0.33f) }); // Top Left Far
    mesh.vertices.push_back({ DEMath::Vector3{ -hs, -hs,  hs }, -DEMath::Vector3::XAxis, -DEMath::Vector3::ZAxis, DEMath::Vector2(0.0f, 0.66f) }); // Bottom Left Far


    // Top
    mesh.vertices.push_back({ DEMath::Vector3{  hs,  hs,  hs }, DEMath::Vector3::YAxis, DEMath::Vector3::XAxis, DEMath::Vector2(0.5f,  0.0f) }); // Top Right Far
    mesh.vertices.push_back({ DEMath::Vector3{ -hs,  hs, -hs }, DEMath::Vector3::YAxis, DEMath::Vector3::XAxis, DEMath::Vector2(0.25f, 0.33f) }); // Top Left Close
    mesh.vertices.push_back({ DEMath::Vector3{  hs,  hs, -hs }, DEMath::Vector3::YAxis, DEMath::Vector3::XAxis, DEMath::Vector2(0.5f, 0.33f) }); // Top Right Close


    mesh.vertices.push_back({ DEMath::Vector3{  hs,  hs,  hs }, DEMath::Vector3::YAxis, DEMath::Vector3::XAxis, DEMath::Vector2(0.5f,  0.0f) }); // Top Right Far
    mesh.vertices.push_back({ DEMath::Vector3{ -hs,  hs,  hs }, DEMath::Vector3::YAxis, DEMath::Vector3::XAxis, DEMath::Vector2(0.25f,  0.0f) }); // Top Left Far
    mesh.vertices.push_back({ DEMath::Vector3{ -hs,  hs, -hs }, DEMath::Vector3::YAxis, DEMath::Vector3::XAxis, DEMath::Vector2(0.25f, 0.33f) }); // Top Left Close


    // Bottom
    mesh.vertices.push_back({ DEMath::Vector3{  hs, -hs, -hs }, -DEMath::Vector3::YAxis, -DEMath::Vector3::XAxis, DEMath::Vector2(0.5f, 0.66f) }); // Bottom Right Close
    mesh.vertices.push_back({ DEMath::Vector3{ -hs, -hs,  hs }, -DEMath::Vector3::YAxis, -DEMath::Vector3::XAxis, DEMath::Vector2(0.25f,  1.0f) }); // Bottom Left Far
    mesh.vertices.push_back({ DEMath::Vector3{  hs, -hs,  hs }, -DEMath::Vector3::YAxis, -DEMath::Vector3::XAxis, DEMath::Vector2(0.5f,  1.0f) }); // Bottom Right Far


    mesh.vertices.push_back({ DEMath::Vector3{  hs, -hs, -hs }, -DEMath::Vector3::YAxis, -DEMath::Vector3::XAxis, DEMath::Vector2(0.5f, 0.66f) }); // Bottom Right Close
    mesh.vertices.push_back({ DEMath::Vector3{ -hs, -hs, -hs }, -DEMath::Vector3::YAxis, -DEMath::Vector3::XAxis, DEMath::Vector2(0.25f, 0.66f) }); // Bottom Left Close
    mesh.vertices.push_back({ DEMath::Vector3{ -hs, -hs,  hs }, -DEMath::Vector3::YAxis, -DEMath::Vector3::XAxis, DEMath::Vector2(0.25f,  1.0f) }); // Bottom Left Far


    int i = 0;
    for (const auto& vertex : mesh.vertices)
    {
        mesh.indices.push_back(i);
        ++i;
    }


    return mesh;
}

MeshPX MeshBuilder::CreateScreenQuad()
{
    MeshPX mesh;
    mesh.vertices.push_back({ {-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f} });
    mesh.vertices.push_back({ {-1.0f,  1.0f, 0.0f}, {0.0f, 0.0f} });
    mesh.vertices.push_back({ { 1.0f,  1.0f, 0.0f}, {1.0f, 0.0f} });
    mesh.vertices.push_back({ { 1.0f, -1.0f, 0.0f}, {1.0f, 1.0f} });
    mesh.indices = { 0, 1, 2, 0, 2, 3 };
    return mesh;
}