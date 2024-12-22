///////////////////////////////////////////////////////////////////////////////
// scenemanager.cpp
// ============
// manage the preparing and rendering of 3D scenes - textures, materials, lighting
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//  Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////

#include "SceneManager.h"
#include "ShapeMeshes.h" 

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include <glm/gtx/transform.hpp>

namespace
{
    const char* g_ModelName = "model";
    const char* g_ColorValueName = "objectColor";
    const char* g_TextureValueName = "objectTexture";
    const char* g_UseTextureName = "bUseTexture";
    const char* g_UseLightingName = "bUseLighting";
    const char* g_LightPositionName1 = "lightPos1";  // Light source 1 (back of the scene)
    const char* g_LightPositionName2 = "lightPos2";  // Light source 2 (top of the scene)
    const char* g_LightColorName1 = "lightColor1";  // White light color for light source 1
    const char* g_LightColorName2 = "lightColor2";  // White light color for light source 2
}

SceneManager::SceneManager(ShaderManager* pShaderManager)
{
    m_pShaderManager = pShaderManager;
    m_basicMeshes == new ShapeMeshes(); // Ensure no conflicting definitions here
}

SceneManager::~SceneManager()
{
    m_pShaderManager = NULL;
    delete m_basicMeshes;
    m_basicMeshes = NULL;
}

void SceneManager::PrepareScene()
{
    m_basicMeshes->LoadBoxMesh(); // Correctly using LoadBoxMesh
}

void SceneManager::RenderScene()
{
    glm::vec3 scaleXYZ;
    float XrotationDegrees = 0.0f;
    float YrotationDegrees = 0.0f;
    float ZrotationDegrees = 0.0f;
    glm::vec3 positionXYZ;

    // Step 1: Set up lighting
    glm::vec3 lightPos1(0.0f, 5.0f, -5.0f);  // Back of the scene light
    glm::vec3 lightPos2(0.0f, 10.0f, 0.0f);  // Top of the scene light
    glm::vec3 lightColor1(1.0f, 1.0f, 1.0f);  // White light color for light source 1
    glm::vec3 lightColor2(1.0f, 1.0f, 1.0f);  // White light color for light source 2

    // Pass light positions and colors to the shader
    glUniform3fv(glGetUniformLocation(m_pShaderManager->GetProgramID(), g_LightPositionName1), 1, &lightPos1[0]);
    glUniform3fv(glGetUniformLocation(m_pShaderManager->GetProgramID(), g_LightPositionName2), 1, &lightPos2[0]);
    glUniform3fv(glGetUniformLocation(m_pShaderManager->GetProgramID(), g_LightColorName1), 1, &lightColor1[0]);
    glUniform3fv(glGetUniformLocation(m_pShaderManager->GetProgramID(), g_LightColorName2), 1, &lightColor2[0]);

    // Step 2: Render the tabletop
    scaleXYZ = glm::vec3(5.0f, 0.1f, 3.0f);
    positionXYZ = glm::vec3(0.0f, 1.5f, 0.0f);

    SetTransformations(scaleXYZ, XrotationDegrees, YrotationDegrees, ZrotationDegrees, positionXYZ);
    SetShaderColor(0.0f, 0.0f, 0.0f, 1.0f);
    m_basicMeshes->DrawBoxMesh();  // Draw the box mesh

    // Step 3: Render the four legs of the desk (same as before)
    scaleXYZ = glm::vec3(0.2f, 1.0f, 0.2f);
    positionXYZ = glm::vec3(-2.0f, 0.5f, -1.0f);
    SetTransformations(scaleXYZ, XrotationDegrees, YrotationDegrees, ZrotationDegrees, positionXYZ);
    SetShaderColor(0.0f, 0.0f, 0.0f, 1.0f);
    m_basicMeshes->DrawBoxMesh();  // Draw the box mesh

    positionXYZ = glm::vec3(2.0f, 0.5f, -1.0f);
    SetTransformations(scaleXYZ, XrotationDegrees, YrotationDegrees, ZrotationDegrees, positionXYZ);
    m_basicMeshes->DrawBoxMesh();  // Draw the box mesh

    positionXYZ = glm::vec3(-2.0f, 0.5f, 1.0f);
    SetTransformations(scaleXYZ, XrotationDegrees, YrotationDegrees, ZrotationDegrees, positionXYZ);
    m_basicMeshes->DrawBoxMesh();  // Draw the box mesh

    positionXYZ = glm::vec3(2.0f, 0.5f, 1.0f);
    SetTransformations(scaleXYZ, XrotationDegrees, YrotationDegrees, ZrotationDegrees, positionXYZ);
    m_basicMeshes->DrawBoxMesh();  // Draw the box mesh

    // Step 4: Render the monitor stand
    scaleXYZ = glm::vec3(0.3f, 0.1f, 0.3f);  // Simple base
    positionXYZ = glm::vec3(0.0f, 2.5f, 0.0f); // Place at the center of the table
    SetTransformations(scaleXYZ, XrotationDegrees, YrotationDegrees, ZrotationDegrees, positionXYZ);
    SetShaderColor(0.3f, 0.3f, 0.3f, 1.0f);
    m_basicMeshes->DrawBoxMesh();  // Draw the stand base

    // Step 5: Render the monitor
    scaleXYZ = glm::vec3(1.0f, 0.6f, 0.1f);  // Monitor screen
    positionXYZ = glm::vec3(0.0f, 3.2f, 0.0f); // Positioned above the stand
    SetTransformations(scaleXYZ, XrotationDegrees, YrotationDegrees, ZrotationDegrees, positionXYZ);
    SetShaderColor(0.0f, 0.0f, 0.0f, 1.0f);
    m_basicMeshes->DrawBoxMesh();  // Draw the monitor

    // Step 6: Render the keyboard
    scaleXYZ = glm::vec3(1.0f, 0.1f, 0.5f);  // Keyboard shape
    positionXYZ = glm::vec3(0.0f, 1.0f, 0.0f); // Place it in front of the desk
    SetTransformations(scaleXYZ, XrotationDegrees, YrotationDegrees, ZrotationDegrees, positionXYZ);
    SetShaderColor(0.2f, 0.2f, 0.2f, 1.0f);
    m_basicMeshes->DrawBoxMesh();  // Draw the keyboard

    // Step 7: Render the mouse
    scaleXYZ = glm::vec3(0.1f, 0.1f, 0.2f);  // Simple mouse shape
    positionXYZ = glm::vec3(0.4f, 0.9f, 0.0f); // Place it near the keyboard
    SetTransformations(scaleXYZ, XrotationDegrees, YrotationDegrees, ZrotationDegrees, positionXYZ);
    SetShaderColor(0.1f, 0.1f, 0.1f, 1.0f);
    m_basicMeshes->DrawBoxMesh();  // Draw the mouse
}


///////////////////////////////////////////////////////////////////////////////
// ShapeMeshes.h
// ============
// A helper class to manage 3D shape meshes, specifically for a simple box
///////////////////////////////////////////////////////////////////////////////

#ifndef SHAPEMESHES_H
#define SHAPEMESHES_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class ShapeMeshes
{
public:
    ShapeMeshes();
    ~ShapeMeshes();

    void LoadBoxMesh();  // Method to load the box mesh (used for the desk)
    void DrawBoxMesh() const;  // Method to draw the box mesh

private:
    GLuint m_boxVAO;    // Vertex Array Object for the box
    GLuint m_boxVBO;    // Vertex Buffer Object for the box vertices
    GLuint m_textureID;  // Texture ID for the box
    GLuint m_textureUniformID;  // Uniform ID for texture in shader
};

#endif // SHAPEMESHES_H


///////////////////////////////////////////////////////////////////////////////
// ShapeMeshes.cpp
// ============
// This file contains the methods to handle loading and drawing a box mesh
///////////////////////////////////////////////////////////////////////////////

#include "ShapeMeshes.h"
#include <iostream>

// Box vertices (for a unit box)
static GLfloat boxVertices[] = {
    // Position data
    -0.5f, -0.5f, -0.5f,  // Bottom-left-back
     0.5f, -0.5f, -0.5f,  // Bottom-right-back
     0.5f,  0.5f, -0.5f,  // Top-right-back
    -0.5f,  0.5f, -0.5f,  // Top-left-back
    -0.5f, -0.5f,  0.5f,  // Bottom-left-front
     0.5f, -0.5f,  0.5f,  // Bottom-right-front
     0.5f,  0.5f,  0.5f,  // Top-right-front
    -0.5f,  0.5f,  0.5f   // Top-left-front
};

// Indices for the box faces
static GLuint boxIndices[] = {
    0, 1, 2,  2, 3, 0,  // Back face
    4, 5, 6,  6, 7, 4,  // Front face
    0, 1, 5,  5, 4, 0,  // Bottom face
    2, 3, 7,  7, 6, 2,  // Top face
    0, 3, 7,  7, 4, 0,  // Left face
    1, 2, 6,  6, 5, 1   // Right face
}
;
ShapeMeshes::ShapeMeshes()
    : m_boxVAO(0), m_boxVBO(0), m_textureID(0)
{
}

ShapeMeshes::~ShapeMeshes()
{
    if (m_boxVAO != 0)
    {
        glDeleteVertexArrays(1, &m_boxVAO);
    }

    if (m_boxVBO != 0)
    {
        glDeleteBuffers(1, &m_boxVBO);
    }

    if (m_textureID != 0)
    {
        glDeleteTextures(1, &m_textureID);
    }
}

void ShapeMeshes::LoadBoxMesh()
{
    glGenVertexArrays(1, &m_boxVAO);
    glBindVertexArray(m_boxVAO);

    glGenBuffers(1, &m_boxVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_boxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    GLuint boxEBO;
    glGenBuffers(1, &boxEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxIndices), boxIndices, GL_STATIC_DRAW);

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("7-1_FinalProjectMilestones/textures/metal.jpeg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ShapeMeshes::DrawBoxMesh() const{

    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glBindVertexArray(m_boxVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



