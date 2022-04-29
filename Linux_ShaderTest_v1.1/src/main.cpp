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
#include "functions.hpp"


sf::Texture* main_texture_pointer;
sf::Sprite* main_sprite_pointer;
sf::Mutex main_mutex;

int argc_global;
char** argv_global;
extern bool fix;
extern bool teleport;

int main(int argc, char** argv) {
//    setvbuf(stdout, NULL, _IOLBF, 0);
    argc_global=argc;
    argv_global=argv;
    for (int n=0; n<argc; n++) printf("argv[%d]=\"%s\"\n",n,argv[n]);
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
    sprite.setOrigin(texture.getSize().x/2.0,texture.getSize().y/2.0);
    sprite.setPosition(texture.getSize().x/2.0,texture.getSize().y/2.0);
    main_sprite_pointer=&sprite;

    launch_MCEDITOR();

    sf::sleep(sf::seconds(0.1));

    while (argc_global>2) {
        if (MCEDITOR_running==0) {
            terminate_MCEDITOR();
            sf::sleep(sf::seconds(0.1));
            printf("\n");
            return EXIT_SUCCESS;
        }
        sf::sleep(sf::seconds(1.0));
    }

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
