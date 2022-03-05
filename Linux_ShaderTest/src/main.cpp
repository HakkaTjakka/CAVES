#define LINUX
#define SFML_STATIC

//#include <SFML/Main.hpp>
#include <SFML/System.hpp>
//#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/Network.hpp>
#include <X11/Xlib.h>
//#include <iostream>
#include <GL/glut.h>

extern void launch_MCEDITOR();
extern int MCEDITOR_running;
extern int MCEDITOR_stop;
extern void terminate_MCEDITOR();
extern int init_cave_shader();


sf::Texture* main_texture_pointer;
sf::Sprite* main_sprite_pointer;
sf::Mutex main_mutex;

int main() {
#if defined(LINUX)
    XInitThreads();
#endif

    int maxVertexTextureImageUnits;
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &maxVertexTextureImageUnits);
    printf("maxVertexTextureImageUnits=%d\n",maxVertexTextureImageUnits);

//    int shader_index=init_cave_shader();

    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;

    main_texture_pointer=&texture;
    sf::Sprite sprite;
    sprite.setTexture(texture,true);
    main_sprite_pointer=&sprite;

    launch_MCEDITOR();

    sf::sleep(sf::seconds(0.1));

    sf::RenderWindow app(sf::VideoMode(texture.getSize().x,texture.getSize().y), "SFML window");

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                if (MCEDITOR_running) {
                    terminate_MCEDITOR();
                    sf::sleep(sf::seconds(1.0));

                }
                app.close();
            }
        }

        app.clear();

        main_mutex.lock();
//        sprite.setTexture(*main_texture_pointer,true);
        app.draw(sprite);
        app.display();
        main_mutex.unlock();
        if (MCEDITOR_running==0) {
            terminate_MCEDITOR();
            sf::sleep(sf::seconds(1.0));
            app.close();
        }
    }
    printf("\n");
    return EXIT_SUCCESS;
}
