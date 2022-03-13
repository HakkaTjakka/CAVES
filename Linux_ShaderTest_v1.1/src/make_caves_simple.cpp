#define SFML_STATIC
#define PI 3.141592653589793
#include <curses.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <SFML/Graphics.hpp>
#include "shaders.hpp"
#include "functions.hpp"
#include "MCEditor/MCEditor.h"

#define sin get_fast_sin

int main_CAVES_simple(int region_x, int region_z, unsigned char* mc, char* shader_name) {
    int load_leeg=0;
    sf::Clock m_clock;

    MCEditor *editor;
    if ( (editor=READ_REGION(region_x,region_z))==NULL ) return -1;

    MCRegion region(region_x, region_z, 0, 0, 0, 512, 512, 256);
    BlockInfo*** AX=region.A;

    if (!load_leeg) {
        printf("Ok. Testing: ");
        editor->mca_coder.getBlock_FAST(region);
        for (int x = 0; x < 512; x++) {
            BlockInfo** AZ=AX[x];
            for (int z = 0; z < 512; z++) {
                BlockInfo* AY=AZ[z];
                for (int y = 0; y < 256; y++) {
                    BlockInfo bi=AY[y];
                }
            }
        }
        printf(" Ok.\n");
    } else {
        for (int x = 0; x < 512; x++) {
            BlockInfo** AZ=AX[x];
            for (int z = 0; z < 512; z++) {
                BlockInfo* AY=AZ[z];
                for (int y = 0; y < 256; y++) {
                    BlockInfo A=AY[y];
//                    AY[y]=BlockInfo(20,0,0,0,0); //glass
                    AY[y]=BlockInfo(0,0,0,0,0); //air
                }
            }
        }
    }

//    unsigned char region_block[512*256*512*4];
//    size_t max_off=512*512*256*4;

//    srand(time(0));

    int xx,zz;
    int chunk_offsetx=region_x*32;
    int chunk_offsetz=region_z*32;
    int pos_offsetx=chunk_offsetx*16;
    int pos_offsetz=chunk_offsetz*16;

    double ARRAY[100][5];       read_array(ARRAY);
    static int c_ar[4096];      make_color_array(c_ar);
    static float d[35][35][35]; make_distance_array(d);

    char tmp[1024];

    int cave_shader_index=init_shader("shaders/metaballs2.frag");   printf("cave_shader_index=%d\n",cave_shader_index);
    int test_shader_index=init_shader("shaders/test.frag");         printf("test_shader_index=%d\n",test_shader_index);

    static sf::RenderWindow app(sf::VideoMode(1024,1024), "Caves window");
    app.setVerticalSyncEnabled(false);

    static sf::Vector2u app_size=app.getSize();
    static sf::Vector2i app_position=app.getPosition();

    static bool first;
    if (first) {
        first=false;
    } else {
        app.setSize(app_size);
        app.setPosition(app_position);
    }

    app.clear(sf::Color(0,0,0,0));

    sf::RenderTexture texture_y[256];
    sf::Sprite sprite_y[256];
    for (int t=0; t<256; t++) {
        printf("Creating texture_y #%d\r",t+1);
        fflush(stdout);
        texture_y[t].create(512,512);
        sprite_y[t].setTexture(texture_y[t].getTexture(),true);
    }

    printf("\n");

    sf::RenderTexture texture_ff[2];
    sf::Sprite sprite_ff[2];

//    main_mutex.lock();
//    main_texture_pointer->loadFromFile("cb.bmp");
//    main_mutex.unlock();

    for (int n=0; n<2; n++) {
        texture_ff[n].create(main_texture_pointer->getSize().x*5,main_texture_pointer->getSize().y*5);
        sprite_ff[n].setTexture(texture_ff[n].getTexture(),true);
        sprite_ff[n].setOrigin( texture_ff[n].getTexture().getSize().x/2.0, texture_ff[n].getTexture().getSize().y/2.0 );
        sprite_ff[n].setRotation(1.0);
        sprite_ff[n].setPosition(texture_ff[n].getTexture().getSize().x/2.0, texture_ff[n].getTexture().getSize().y/2.0);
    }

    sf::Texture* backup_main_texture_pointer=main_texture_pointer;
    sf::Sprite* backup_main_sprite_pointer=main_sprite_pointer;

    sf::Sprite main_sprite;
    main_sprite.setTexture(*main_texture_pointer,true);
    main_sprite.setScale(5.0,5.0);

    texture_ff[0].draw(main_sprite);
    texture_ff[1].draw(main_sprite);
    texture_ff[0].display();
    texture_ff[1].display();

    int flip_flop=0;

    main_sprite.setScale(512.0/main_texture_pointer->getSize().x,512.0/main_texture_pointer->getSize().y);

    shader_struct_vector[cave_shader_index]->Shader.setUniform("offsetx", pos_offsetx);
    shader_struct_vector[cave_shader_index]->Shader.setUniform("offsetz", pos_offsetz);

    sf::BlendMode MyBlendingMode(   sf::BlendMode::One, sf::BlendMode::One,         sf::BlendMode::Add,
                                    sf::BlendMode::One, sf::BlendMode::SrcAlpha,    sf::BlendMode::Add);

    shader_struct_vector[cave_shader_index]->RenderStates.blendMode=MyBlendingMode;

    sf::Texture texture_app[3];
    sf::Sprite sprite_app[3];
    for (int t=0; t<3; t++) {
        texture_app[t].create(512,512);
        sprite_app[t].setTexture(texture_app[t],true);
    }

    sprintf(tmp, "tiles/r.%d.%d.png", region_x-1, region_z-1);
    if (!file_exists(tmp)) {
        sprite_app[0].setTexture(texture_ff[0].getTexture(),true);
        sprite_app[0].setScale( 512.0/texture_ff[0].getTexture().getSize().x, 512.0/texture_ff[0].getTexture().getSize().y );
    } else texture_app[0].loadFromFile(tmp);
    sprite_app[0].setPosition(0,0);
    app.draw(sprite_app[0]); app.display();
    app.display();

    sprintf(tmp, "tiles/r.%d.%d.png", region_x-1, region_z);
    if (!file_exists(tmp)) {
        sprite_app[1].setTexture(texture_ff[0].getTexture(),true);
        sprite_app[1].setScale( 512.0/texture_ff[0].getTexture().getSize().x, 512.0/texture_ff[0].getTexture().getSize().y );
    } else texture_app[1].loadFromFile(tmp);
    sprite_app[1].setPosition(0,512);
    app.draw(sprite_app[1]); app.display();
    app.display();

    sprintf(tmp, "tiles/r.%d.%d.png", region_x, region_z-1);
    if (!file_exists(tmp)) {
        sprite_app[2].setTexture(texture_ff[0].getTexture(),true);
        sprite_app[2].setScale( 512.0/texture_ff[0].getTexture().getSize().x, 512.0/texture_ff[0].getTexture().getSize().y );
    } else texture_app[2].loadFromFile(tmp);
    sprite_app[2].setPosition(512,0);
    app.draw(sprite_app[2]); app.display();
    app.display();

    for (int y = 0; y < 256; y++) {
        update_caves_region(texture_y[y],sprite_y[y], y, cave_shader_index);
    }

//    sf::BlendMode MyBlendingMode(sf::BlendAlpha);

    main_sprite.setScale(1.0,1.0);
    main_sprite.setPosition(512.0,512.0);

    for (int y = 0; y < 256; y++) {
        texture_y[y].display();
        main_sprite.setTexture(texture_y[y].getTexture(),true);
        app.draw(main_sprite,MyBlendingMode);
        app.display();
    }
    printf("Textures created\n");

    printf("time: %.1f seconds\n",m_clock.getElapsedTime().asSeconds());

    sf::RenderTexture cp_texture;
    cp_texture.create(main_texture_pointer->getSize().x,main_texture_pointer->getSize().y);
    sf::Sprite cp_sprite;

    sf::Event event;

    bool gpu=true;
    if (gpu) {

//        sf::Texture main_texture;

    //    app.setVerticalSyncEnabled(true);

        int flop_flip=(flip_flop+1)%2;

        update_main_texture(texture_ff, sprite_ff, flip_flop, test_shader_index);

        cp_sprite.setTexture(texture_ff[flip_flop].getTexture(),true);
        cp_sprite.setScale(0.2,0.2);
        cp_texture.draw(cp_sprite);
        cp_texture.display();

        main_mutex.lock();
        main_texture_pointer->update(cp_texture.getTexture());
        main_mutex.unlock();

        main_sprite.setPosition(512.0,512.0);

        sf::Image image_y;
        for (int y = 0; y < 256; y++) {

            image_y = texture_y[y].getTexture().copyToImage();
            int id;
            sf::Color pixel;

            bool resized=false;
            while (app.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    delete_shader(cave_shader_index);
                    delete_shader(test_shader_index);
                    MCEDITOR_running=0;
                    sf::sleep(sf::seconds(2.0));
                } else if (event.type == sf::Event::Resized) {
                    resized=true;
                }
            }

            for (int x = 0; x < 512; x++) {
                toggle2();
                for (int z = 0; z < 512; z++) {
                    pixel=image_y.getPixel(x,z);
                    if (pixel.r>0) {
                        if (pixel.g==0)
                            AX[x][z][y]=BlockInfo(89,0,0,0); //glow_stone
                        else {
                            AX[x][z][y]=BlockInfo(251,0,int(pixel.r/16),0); //concrete
                        }
                    }
                }
            }

//            app.clear();
            main_sprite.setTexture(texture_y[y].getTexture(),true);
            app.draw(main_sprite);
//            app.draw(main_sprite,MyBlendingMode);

            if (resized) {
                app.draw(sprite_app[0]);  app.draw(sprite_app[1]); app.draw(sprite_app[2]);

//                for (int y = 0; y < 256; y++) {
                    main_sprite.setTexture(texture_y[y].getTexture(),true);
                    app.draw(main_sprite,MyBlendingMode);
//                }
            }
            app.display();
        }

        sf::RenderTexture m_texture;
        m_texture.create(512,512);
        m_texture.clear(sf::Color(0,0,0,1));
        main_sprite.setPosition(0.0,0.0);


        main_sprite.setTexture(texture_y[255].getTexture(),true);
        m_texture.draw(main_sprite,sf::BlendAdd);

        sprintf(tmp, "tiles/r.%d.%d.png", region_x, region_z);
        mkdir("tiles", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        m_texture.display();
        m_texture.getTexture().copyToImage().saveToFile(tmp);

        for (int y = 0; y < 256; y++) {
            sprite_y[y].setPosition(512,512);
        }

/*
        app.setVerticalSyncEnabled(true);
        for (int n=0; n<1; n++) {
            for (int y = 255; y >= 0; y--) {
                app.clear();
                app.draw(sprite_app[0]); app.draw(sprite_app[1]); app.draw(sprite_app[2]);
                app.draw(sprite_y[y]);
                app.display();
                while (app.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        n=2; y=-1;
                    }
                }
            }
            if (n<1) {
                for (int y = 0; y < 256; y++) {
                    app.clear();
                    app.draw(sprite_app[0]); app.draw(sprite_app[1]); app.draw(sprite_app[2]);
                    app.draw(sprite_y[y]);
                    app.display();
                    while (app.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            n=2; y=256;
                        }
                    }
                }
            }
        }
*/
        app.clear();
        app.draw(sprite_app[0]); app.draw(sprite_app[1]); app.draw(sprite_app[2]);
        main_sprite.setTexture(m_texture.getTexture(),true);
        main_sprite.setPosition(512.0,512.0);
        app.draw(main_sprite);
        app.display();
    }

    app.setVerticalSyncEnabled(false);

    for (int x = 0; x < 512; x++) {
        BlockInfo** AZ=AX[x];
        for (int z = 0; z < 512; z++) {
            BlockInfo* AY=AZ[z];
            toggle2();
            for (int y = 0; y < 256; y++) {
                if (y==0) {
                    AY[y] = BlockInfo(7, 0, 0, 0);
                } else if (y<=5) {
                    if (AY[y].id==0) {
                        if (!(rand()%10000)) AY[y] = BlockInfo(8, 0, 0, 0);
                        else AY[y] = BlockInfo(8, 0, 0, 0);
                    }
                }
            }
        }
    }

    printf("\n");
    printf("REGION=[%d][%d]  XX=[%3d-%3d] Y=[%3d-%3d] ZZ=[%3d-%3d] ",region_x,region_z,0,511,0,255,0,255);

    sprintf(tmp, "saves/caves/region/r.%d.%d.mca", region_x, region_z);
    editor->mca_coder.current_filename_mca=tmp;

    if (file_exists(editor->mca_coder.current_filename_mca.c_str())) {
        char cmd[200];
        sprintf(cmd,"rm %s",editor->mca_coder.current_filename_mca.c_str());
        system(cmd);
    }
    editor->setRegion(region);
    printf("Region ready, returning\n");

    while (app.pollEvent(event)) {
        if (event.type == sf::Event::Resized) {
        }
    }

    app_size=app.getSize();
    app_position=app.getPosition();

    delete_shader(cave_shader_index);
    delete_shader(test_shader_index);
    delete editor;
    printf("Total time: %.1f seconds\n",m_clock.getElapsedTime().asSeconds());
    return 0;
}
