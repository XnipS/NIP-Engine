#pragma once
#include "core.h"
#include <cstring>
#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
};

static inline void LoadOBJFromFile(const char* path, std::vector<glm::vec3>* vertices, std::vector<glm::vec2>* uvs, std::vector<glm::vec3>* normals)
{
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    // Load file
    FILE* file = fopen(path, "r");
    if (!file) {
        NE_LOG_ERROR("Model could not be loaded at %s\n", path);
    }

    // Read file to end
    while (true) {

        char lineHeader[128];
        // Read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF) {
            break; // EOF = End Of File. Quit the loop.
        }

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                NE_LOG_ERROR("Model is too advanced for this engine! (Requires triangulation!)\n");
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }
    // else : parse lineHeader

    // Index data
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        unsigned int index = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[index - 1];
        vertices->push_back(vertex);
    }
    for (unsigned int i = 0; i < uvIndices.size(); i++) {
        unsigned int index = uvIndices[i];
        glm::vec2 uv = temp_uvs[index - 1];
        uvs->push_back(uv);
    }
    for (unsigned int i = 0; i < normalIndices.size(); i++) {
        unsigned int index = normalIndices[i];
        glm::vec3 normal = temp_normals[index - 1];
        normals->push_back(normal);
    }
    NE_LOG_INFO("Model loaded: %s \n", path);

    // Cleanup
    fclose(file);
}

static inline void LoadOBJFromFileIndexed(const char* path, std::vector<glm::vec3>* vertices, std::vector<glm::vec2>* uvs, std::vector<glm::vec3>* normals, std::vector<unsigned int>* indexes)
{
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec3> sorted_vertices;
    std::vector<glm::vec2> sorted_uvs;
    std::vector<glm::vec3> sorted_normals;
    std::vector<Vertex> vertexGroup;

    std::vector<Vertex> indexedVertexGroup;

    // Load file
    FILE* file = fopen(path, "r");
    if (!file) {
        NE_LOG_ERROR("Model could not be loaded at %s\n", path);
    }

    // Read file to end
    while (true) {

        char lineHeader[128];
        // Read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF) {
            break; // EOF = End Of File. Quit the loop.
        }

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                NE_LOG_ERROR("Model is too advanced for this engine! (Requires triangulation!)\n");
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }
    // else : parse lineHeader

    // Index data
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        unsigned int index = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[index - 1];
        sorted_vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < uvIndices.size(); i++) {
        unsigned int index = uvIndices[i];
        glm::vec2 uv = temp_uvs[index - 1];
        sorted_uvs.push_back(uv);
    }
    for (unsigned int i = 0; i < normalIndices.size(); i++) {
        unsigned int index = normalIndices[i];
        glm::vec3 normal = temp_normals[index - 1];
        sorted_normals.push_back(normal);
    }

    NE_LOG_INFO("Loaded: %zu, %zu, %zu \n", sorted_vertices.size(), sorted_uvs.size(), sorted_normals.size());

    // Group data into vertices
    for (int i = 0; i < sorted_vertices.size(); i++) {
        Vertex vert;
        vert.position = sorted_vertices[i];
        vert.uv = sorted_uvs[i];
        vert.normal = sorted_normals[i];
        vertexGroup.push_back(vert);
    }
    // Index vertices
    bool found = false;
    for (int x = 0; x < vertexGroup.size(); x++) {
        found = false;
        for (int y = 0; y < vertices->size(); y++) {
            if (vertexGroup[x].position == (*vertices)[y] && vertexGroup[x].uv == (*uvs)[y] && vertexGroup[x].normal == (*normals)[y]) {
                // Then x should use y's index
                indexes->push_back(y);
                found = true;
                break;
            }
        }
        if (!found) {
            indexes->push_back(vertices->size());
            vertices->push_back(vertexGroup[x].position);
            uvs->push_back(vertexGroup[x].uv);
            normals->push_back(vertexGroup[x].normal);
        }
    }

    NE_LOG_INFO("Model loaded: %s \n", path);

    // Cleanup
    fclose(file);
}