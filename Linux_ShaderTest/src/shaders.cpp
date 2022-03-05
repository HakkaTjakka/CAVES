#define SFML_STATIC
#define PI 3.141592653589793

#include <curses.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <map>


#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Texture.hpp>
#include <SFML/Network.hpp>
#include "shaders.hpp"


std::vector<shader_struct*> shader_struct_vector;

int init_shader(char* shader_name) {
    shader_struct* m_shader_struct = new shader_struct;

    if (!m_shader_struct->Shader.loadFromFile(shader_name, sf::Shader::Fragment)) {
        printf("Error loading %s\n", shader_name);
        delete m_shader_struct;
        return -1;
    }
    printf("Loaded %s\n", shader_name);
    m_shader_struct->Shader.setUniform("texture", sf::Shader::CurrentTexture);
    m_shader_struct->RenderStates=&m_shader_struct->Shader;
    shader_struct_vector.push_back(m_shader_struct);
    return shader_struct_vector.size()-1;
}

int run_cave_shader(int index, sf::Texture& texture_in, sf::Texture& texture_out) {
    shader_struct_vector[index]->Shader.setUniform("blur_radius", float(1.0));
    return 0;
}

void delete_shader(int index) {
    delete shader_struct_vector[index];
    shader_struct_vector[index]=NULL;
}
