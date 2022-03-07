#ifndef FUNCTIONS_HPP_INCLUDED
#define FUNCTIONS_HPP_INCLUDED

#include "shaders.hpp"
#include "MCEditor/MCEditor.h"

void make_color_array(int* c_ar);
int repl_str(char *str, char *orig, char *rep);
//extern int toggle2();
bool file_exists(const char * filename);
void reset_block(int region_x, int region_z);
int init_shader(char* shader_name);
void toggle2();

int main_CAVES(int region_x, int region_z, unsigned char* mc, char* shader_name);
int main_CAVES_simple(int region_x, int region_z, unsigned char* mc, char* shader_name);

void launch_MCEDITOR();
void make_caves(char* shader_name);
MCEditor* READ_REGION(int region_x, int region_z);


void update_main_texture(sf::RenderTexture *texture, sf::Sprite *sprite, int& flip_flop, int shader_index);
void update_caves_region(sf::RenderTexture *texture, sf::Sprite& sprite, int texture_index, int shader_index);
int main_mceditor();
float get_fast_sin(float rot);
void fast_sin_init();
void launch_MCEDITOR();
int init_cave_shader();
void terminate_MCEDITOR();
void delete_shader(int index);
int read_array(double ARRAY[100][5]);
void make_distance_array(float d[35][35][35]);


extern int MCEDITOR_running;
extern int MCEDITOR_stop;

extern float fast_sin[4096];
extern sf::Texture* main_texture_pointer;
extern sf::Sprite* main_sprite_pointer;
extern sf::Mutex main_mutex;
extern std::string file_name_MCA;
extern std::vector<shader_struct*> shader_struct_vector;
extern int remove_block_entities;
//extern int chunk_offsetx, chunk_offsetz;
//extern int region_xxx,region_zzz;
extern int MCEDITOR_running;
extern int MCEDITOR_stop;



#endif // FUNCTIONS_HPP_INCLUDED
