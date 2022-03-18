#define SFML_STATIC
#define PI 3.141592653589793

//#include <conio.h>
#include <curses.h>
#include "MCEditor/MCEditor.h"
#include "MCEditor/BlockEntity.h"
#include "MCEditor/MCACoder.h"
#include <math.h>
#include <cstring>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <SFML/System/Thread.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "shaders.hpp"
#include "functions.hpp"

//unsigned char region_block[512*256*512*4];

int make_caves(char* shader_name) {
    mkdir("saves", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("saves/caves", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("saves/caves/region", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    int region_x=0,region_z=0;
    int size_regions=0;
    char tmp[512];

    if (argc_global>2) {
        if (strcmp(argv_global[1],"repack")==0) {
            if ( file_exists(argv_global[2]) ) {
                printf("Repacking %s ",argv_global[2]);
                if (main_REPACK(argv_global[2])==-1) {
                    printf("Error repacking %s\n",argv_global[2]);
                    sf::sleep(sf::seconds(2.0));
                    return -1;
                }
                return 0;
            } else {
                printf("File does not exist %s\n",argv_global[2]);
                return -1;
            }
        } else {
            printf("Syntax error\n");
            return -1;
        }
    }

    while (size_regions<60) {
        size_regions++;
        for (region_x=0; region_x<size_regions && MCEDITOR_stop==0; region_x++) {
            for (region_z=0; region_z<size_regions && MCEDITOR_stop==0; region_z++) {
                if (region_x<size_regions-1 && region_z<size_regions-1) {
                    continue;
                }
                sprintf(tmp, "saves/caves/region/r.%d.%d.mca", region_x, region_z);

                if ( file_exists(tmp) ) {
                    printf("File exists, skipping %s\n",tmp);
                    continue;
                }
                sf::Clock m_clock;
                printf("Creating caves: region.%d.%d.mca\n",region_x,region_z);

unsigned char* region_block;

//                if (main_CAVES_simple(region_x, region_z, region_block, shader_name)==-1) return -1;
                if (main_CAVES(region_x, region_z, region_block, shader_name)==-1) return -1;
//                if (main_CAVES(region_x, region_z, region_block, shader_name)==-1) return;
                printf("time: %.1f seconds\n",m_clock.getElapsedTime().asSeconds());
            }
        }
    }
}

#define sin get_fast_sin
bool create_path;
extern bool load_empty;

int main_CAVES(int region_x, int region_z, unsigned char* mc, char* shader_name) {
    bool nodisp=false;
    if (file_exists("nodisp.on")) nodisp=true;
//    int load_leeg=0;
    create_path=false;

    if (argc_global>1) {
        if (strcmp(argv_global[1],"path")==0) {
            printf("Creating path\n");
            create_path=true;
        }
    }

    MCEditor *editor;
    MCRegion region(region_x, region_z, 0, 0, 0, 512, 512, 256);
    BlockInfo*** AX=region.A;
    if ( (editor=READ_REGION(region_x,region_z))==NULL ) return -1;
    if (!create_path) {
        if (!load_empty) {
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
                        AY[y]=BlockInfo(1,0,0,0,0); //stone
                    }
                }
            }
        }
    } else {
        for (int x = 0; x < 512; x++) {
            BlockInfo** AZ=AX[x];
            for (int z = 0; z < 512; z++) {
                BlockInfo* AY=AZ[z];
                for (int y = 0; y < 256; y++) {
                    BlockInfo A=AY[y];
                    AY[y]=BlockInfo(0,0,0,0,0); //stone
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

    int cave_shader_index=init_shader(shader_name);         printf("\n%s index=%d\n",shader_name,cave_shader_index);
    int test_shader_index=init_shader("shaders/test.frag"); printf("\n%s index=%d\n","shaders/test.frag",test_shader_index);

    sf::RenderWindow app(sf::VideoMode(1024,1024), "Caves window");
    app.setVerticalSyncEnabled(false);

    static sf::Vector2u app_size=app.getSize();
//    static sf::Vector2i app_position=app.getPosition();
    static sf::Vector2i app_position=sf::Vector2i(1000,0);

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
        texture_y[t].clear(sf::Color(0,0,0,0));
        texture_y[t].display();
    }
    printf("\n");

    sf::RenderTexture texture_ff[2];
    sf::Sprite sprite_ff[2];

    main_mutex.lock();
    main_texture_pointer->loadFromFile("cb.bmp");
    main_mutex.unlock();

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

    if (create_path) {
//        shader_struct_vector[cave_shader_index]->Shader.setUniform("phase", int(3));
        shader_struct_vector[cave_shader_index]->Shader.setUniform("phase", int(2));
    } else {
        shader_struct_vector[cave_shader_index]->Shader.setUniform("phase", int(0));
    }
    shader_struct_vector[cave_shader_index]->Shader.setUniform("offsetx", pos_offsetx);
    shader_struct_vector[cave_shader_index]->Shader.setUniform("offsetz", pos_offsetz);

    sf::BlendMode MyBlendingMode(   sf::BlendMode::One, sf::BlendMode::One,         sf::BlendMode::Add,
                                    sf::BlendMode::One, sf::BlendMode::SrcAlpha,    sf::BlendMode::Add);

//    shader_struct_vector[cave_shader_index]->RenderStates.blendMode=MyBlendingMode;

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

    sf::RenderStates* renderstates_p=&shader_struct_vector[cave_shader_index]->RenderStates;
    sf::Shader* shader_p=&shader_struct_vector[cave_shader_index]->Shader;

    sf::Event event;

    int n1,n2;
    if (create_path) { n1=-17; n2=18; }
    else { n1=0; n2=1; }

    sf::RenderTexture t_dummy;
    t_dummy.create(512,512);
    t_dummy.clear(sf::Color(0,0,0,0));
    t_dummy.display();
    sf::Sprite s_dummy;
    s_dummy.setTexture(t_dummy.getTexture(),true);

    main_sprite.setScale(1.0,1.0);
    main_sprite.setPosition(512.0,512.0);
    main_sprite.setTexture(t_dummy.getTexture(),true);

    printf("\n");
//    for (int yyy=-17; yyy<18; yyy++) {
//        shader_p->setUniform("yyy", yyy);
        for (int y = 0; y < 256; y++) {
            shader_p->setUniform("height", y);

            texture_y[y].draw(s_dummy,*renderstates_p);
            texture_y[y].display();

//            t_dummy.clear(sf::Color(0,0,0,0));
//            t_dummy.draw(sprite_y[y]);
//            t_dummy.display();
//            s_dummy.setTexture(texture_y[y].getTexture(),true);

            main_sprite.setTexture(texture_y[y].getTexture(),true);
            app.draw(main_sprite,MyBlendingMode);
            app.display();
//
//            printf("1: yyy=%3d y=%3d\r",yyy,y);
            printf("1: y=%d\r",y);
            fflush(stdout);
            while (app.pollEvent(event));
            sf::sleep(sf::seconds(0.005));
        }
//    }
    printf("1: Done         \n");
    while (app.pollEvent(event));
    fflush(stdout);
    sf::sleep(sf::seconds(0.001));

    printf("\n");
    {
        sf::RenderTexture m_texture;
        m_texture.create(512,512);
        m_texture.clear(sf::Color(0,0,0,1));
        m_texture.display();

        for (int y = 0; y < 256; y++) {
            texture_y[y].display();
            m_texture.draw(sprite_y[y],MyBlendingMode);
    //        m_texture.draw(main_sprite,sf::BlendAdd);
//            sprite_y[y].setPosition(512,512);
            main_sprite.setTexture(texture_y[y].getTexture(),true);
            app.draw(main_sprite,MyBlendingMode);
            printf("2: Displaying %d   \r",y);
            fflush(stdout);
            app.display();
        }
        m_texture.display();

        printf("2: Displaying done    \r");
        fflush(stdout);

/*
        sf::sleep(sf::seconds(1.0));

        app.setVerticalSyncEnabled(true);
        for (int n=0; n<1; n++) {
            for (int y = 0; y < 256; y++) {
                app.clear();
                app.draw(sprite_app[0]); app.draw(sprite_app[1]); app.draw(sprite_app[2]);
                main_sprite.setTexture(texture_y[y].getTexture(),true);
                app.draw(main_sprite);
                app.display();
                while (app.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        n=2; y=256;
                    }
                }
                printf("3: Displaying y=%d   \r",y);
                fflush(stdout);
            }
            if (n<2) {
                for (int y = 255; y >= 0; y--) {
                    app.clear();
                    app.draw(sprite_app[0]); app.draw(sprite_app[1]); app.draw(sprite_app[2]);
                    main_sprite.setTexture(texture_y[y].getTexture(),true);
                    app.draw(main_sprite);
                    app.display();
                    while (app.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            n=2; y=-1;
                        }
                    }
                    printf("3: Displaying y=%d   \r",y);
                    fflush(stdout);
                }
            }
        }
        app.clear(sf::Color(0,0,0,0));
        app.draw(sprite_app[0]);  app.draw(sprite_app[1]); app.draw(sprite_app[2]);

        main_sprite.setTexture(m_texture.getTexture(),true);
        app.draw(main_sprite,MyBlendingMode);
        app.display();
*/
    }


//    for (int y = 0; y < 256; y++) {
//        texture_y[y].display();
//        main_sprite.setTexture(texture_y[y].getTexture(),true);
//        app.draw(main_sprite,MyBlendingMode);
//        app.display();
//    }
    printf("Textures created 1\n");
    fflush(stdout);

    sf::RenderTexture cp_texture;
    cp_texture.create(main_texture_pointer->getSize().x,main_texture_pointer->getSize().y);
    sf::Sprite cp_sprite;

    bool cpu=true;
    if (create_path) cpu=false;

    if (cpu) {
        sf::Clock m_clock;

        int counter1=0;
        int counter2=0;

        float b_var1,b_var2,b_var3;

        int r1_a, r2_a, r3_a;
        int r1_p_a, r2_p_a, r3_p_a;
        int r1_q_a, r2_q_a, r3_q_a;
        int r1_r_a, r2_r_a, r3_r_a;
        int r1_s_a, r2_s_a, r3_s_a;

        int r1_b, r2_b, r3_b;
        int r1_p_b, r2_p_b, r3_p_b;
        int r1_q_b, r2_q_b, r3_q_b;
        int r1_r_b, r2_r_b, r3_r_b;
        int r1_s_b, r2_s_b, r3_s_b;

        float f_x,f_y,f_z;
        float var1,var2,var3;
        float x_a,y_a,z_a;

        for (int x = 0; x < 512; x++) {

            if (app.isOpen()) {
                while (app.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        delete_shader(cave_shader_index);
                        delete_shader(test_shader_index);
                        MCEDITOR_running=0;
                        sf::sleep(sf::seconds(2.0));
                    }
                }
            }

            int flop_flip=(flip_flop+1)%2;

            update_main_texture(texture_ff, sprite_ff, flip_flop, test_shader_index);

            cp_sprite.setTexture(texture_ff[flip_flop].getTexture(),true);
            cp_sprite.setScale(0.2,0.2);
            cp_texture.draw(cp_sprite);
            cp_texture.display();

            main_mutex.lock();
            main_texture_pointer->update(cp_texture.getTexture());
            main_mutex.unlock();

    //        app.clear();

    //        app.draw(sprite_ff[flip_flop]);
    //        app.display();

            sf::Event event;
            while (app.pollEvent(event));

            BlockInfo** AZ=AX[x];
            xx=x+pos_offsetx;
            printf("\rx=%3d => %d/%d ",x,counter1,counter2);
    //        for (int i=0; i<16; i++ ) {
    //            printf("%d=%d ",i,col_a[i]);
    //        }
            printf("\r");
            fflush(stdout);
            for (int z = 0; z < 512; z++) {
                zz=z+pos_offsetz;
                BlockInfo* AY=AZ[z];
    /*
                app.display();
                app.clear();
                sprite_y[128].setRotation(angle);
                angle+=0.01;
                app.draw(sprite_y[128]);
    */

                for (int y = 0; y < 256; y++) {

                    for (int n=0; n<4; n++) {
                        if (n==0)       { x_a=xx;   y_a=y;   z_a=zz;   }
                        else if (n==1)  { x_a=xx+1; y_a=y;   z_a=zz;   }
                        else if (n==2)  { x_a=xx;   y_a=y+1; z_a=zz;   }
                        else            { x_a=xx;   y_a=y;   z_a=zz+1; }

                        var1=1.0+0.24*sin(float(999+ x_a+y_a+z_a)/120.53 );
                        var2=1.0+0.24*sin(float(899+ x_a+y_a-z_a)/117.32 );
                        var3=1.0+0.24*sin(float(799+-x_a-y_a+z_a)/ 93.21 );

                        var1=var1+ 0.02*sin(float( x_a+y_a+1.5*z_a)/64.53 );
                        var2=var2+ 0.02*sin(float( 1.5*x_a+y_a-z_a)/75.32 );
                        var3=var3+ 0.02*sin(float(-x_a-1.5*y_a+z_a)/53.21 );

                        f_x=376.0*sin(float(x_a + z_a/2 + y_a   +200)/142.79);
                        f_y=200.0*sin(float(y_a + x_a   + z_a       )/130.54);
                        f_z=336.0*sin(float(z_a + y_a   + x_a/2     )/165.59);

                        r3_b= 1+int(115.0 + 114.0*sin( (
                                 0.8*( var2 * f_x/1.44  + var3*f_z/2.36 )             /  (93.3 * (1.0+var2*0.4*sin((var1*f_z/1.3 + f_y/2.4 + f_x    ) / 77.0)))   +
                                       var3 * 0.7*( var1*f_x/1.14  + var2*f_z/1.17 )  /  (89.4 * (1.0+var3*0.4*sin((f_z/1.7 + f_y     - var2*f_x    ) / 90.0)))   +
                                       var1 * 3.10*sin( (var1*f_x/1.36 + f_z/1.55 )   /  (112.6 * (1.0+0.4*sin((var3*f_z     + f_y     + f_x/2.1)     / 51.0)))   ) +
                                       var2 * 4.15*sin( (f_x/1.67 + var1*f_z/1.64 )   /  (52.4 * (1.0+0.4*sin((f_z     - var2*f_y/2.7 + f_x/1.2)      / 87.0)))   )
                            )*0.5 ) );
                        r1_b= 255+int( 230.0*sin( (
                                   0.7*( var3*f_z/2.23  +  f_x/2.3 )                 /   ( 97.3 * (1.0+var3*0.4*sin((-var1*f_z/1.2 + f_y     + f_x/1.5) / 133.0)))   +
                                         var3*0.6*( var3*f_z/1.44  +  f_x/1.5 )      /   (113.3 * (1.0+var1*0.4*sin((-f_z-      var3*f_y/1.6 + f_x/1.3) / 124.0)))   +
                                         var1*1.8*sin( (var3*f_z/1.53 + f_x/1.1 )    /   ( 86.0 * (1.0+0.4*sin(( f_z + f_y     - var2*f_x/2.1    )      /  83.0)))   ) +
                                         var3*2.15*sin( (f_z/1.33 + var1*f_x/1.4 )   /   ( 98.0 * (1.0+0.4*sin(( f_z/1.8 - var1*f_y     + f_x/1.4)      /  87.0)))   )
                            )*0.40  ) );
                        r2_b= 255+int( 230.0*sin( (
                               0.7*( var1 * f_x/2.02   +  f_z/2.30 )              / (126.3 * (1.0+var1*0.3*sin(( f_z/1.2 + f_y/2.2 + var3*f_x      )  /117.0)))    +
                                     var1 * 0.6*( f_x/1.12   +  var3*f_z/1.22 )   / (118.3 * (1.0+var2*0.4*sin((-var1*f_z/1.3 - f_y     + f_x/1.7  )  /125.0)))    +
                                     var3 * 1.8*sin( (var2*f_x/1.0 + f_z/1.5 )    / (99.0  * (1.0+0.4*sin(( f_z/1.32 - f_y     + var1*f_x          )  / 85.0)))    ) +
                                     var2 * 2.15*sin( (f_x/1.5 + var1*f_z/1.7 )   / (83.0  * (1.0+0.4*sin(( var2*f_z/1.5 + f_y/2.1 - f_x           )  / 83.0)))    )
                            )*0.40 ) );


                        f_x=250.0*(
                                       sin(float(x_a/2 + y_a + z_a  ) / 120.53 ) +
                                   0.2*sin(float(x_a   + y_a + z_a/2) / (631.34+ 60.43*sin(float(x_a-z_a)/86) ))
                                   ) +
                                    0.1*sin(float(x_a + z_a/2 + y_a  ) / (466.79+120.48*sin(float(x_a-y_a)/145.5) ));

                        f_y=250.0*(
                                       sin(float(x_a +y_a/2+z_a   ) / 88.32 ) +
                                   0.2*sin(float(x_a +z_a)          / (610.13+25*sin(float(x_a-y_a)/84) ))
                                   );

                        f_z=250.0*(
                                       sin(float(x_a  +y_a  +z_a/2)/143.21 ) +
                                   0.2*sin(float(y_a+z_a)/(730.72+37*sin(float(y_a-x_a)/95) ))
                                   );

                        r3_a= 1+int(95.0 + 134.0*sin( (
                                 0.8*( var1*f_z/1.44  + var2*f_x/2.36 )       /  ( 93.3 * (1.0+var1*0.4*sin((var3*f_x/1.3 + f_y/2.4 + f_z    ) / 67.0)))   +
                                 var2*0.7*( var2*f_z/1.14  + var3*f_x/1.17 )  /  ( 89.4 * (1.0+var2*0.4*sin((f_x/1.7 + f_y     - var1*f_z    ) / 90.0)))   +
                                 var3*3.10*sin( (var3*f_z/1.36 + f_x/1.55 )   /  (112.6 * (1.0+0.4*sin((var2*f_x     + f_y     + f_z/2.1) / 71.0)))   ) +
                                 var1*4.15*sin( (f_z/1.67 + var3*f_x/1.64 )   /  ( 52.4 * (1.0+0.4*sin((f_x     - var1*f_y/2.7 + f_z/1.2) / 87.0)))   )
                            )*0.5 ) );

                        if (r3_a>229) r3_a=229;
                        else if (r3_a<3) r3_a=3;

                        r2_a= 255+int( 230.0*sin( (
                                   0.7*( var2*f_x/2.23  +  f_z/2.3 )                       /   (97.3 * (1.0+var2*0.4*sin((-var3*f_x/1.2 + f_y     + f_z/1.5) / 133.0)))   +
                                   var2*0.6*( var3*f_x/1.44  +  f_z/1.5 )                            /   (113.3 * (1.0+var3*0.4*sin((-f_x-      var2*f_y/1.6 + f_z/1.3) / 124.0)))   +
                                   var3*1.8*sin( (var3*f_x/1.53 + f_z/1.1 )                /   (86.0 * (1.0+0.4*sin(( f_x + f_y     - var1*f_z/2.1    ) / 83.0)))   ) +
                                   var1*2.15*sin( (f_x/1.33 + var2*f_z/1.4 )                /   (98.0 * (1.0+0.4*sin(( f_x/1.8 - var3*f_y     + f_z/1.4) / 87.0)))   )
                            )*0.6  ) );
                        r1_a= 255+int( 230.0*sin( (
                               0.7*( var3*f_z/2.02   +  f_x/2.30 )              / (126.3*(1.0+var3*0.3*sin(( f_x/1.2 + f_y/2.2 + var2*f_z      )  /117.0)))    +
                               var3*0.6*( f_z/1.12   +  var1*f_x/1.22 )                  / (118.3*(1.0+var1*0.4*sin((-var3*f_x/1.3 - f_y     + f_z/1.7  )  /125.0)))    +
                               var2*1.8*sin( (var2*f_z/1.0 + f_x/1.5 )          / (99.0*(1.0+0.4*sin(( f_x/1.32 - f_y     + var3*f_z      )  /115.0)))    ) +
                               var1*2.15*sin( (f_z/1.5 + var3*f_x/1.7 )          / (83.0*(1.0+0.4*sin(( var1*f_x/1.5 + f_y/2.1 - f_z      )  /83.0)))    )
                            )*0.5 ) );


                        if (n==0) {
                                r3_p_a = r3_a;   r1_p_a = r1_a;    r2_p_a = r2_a;
                                r3_p_b = r3_b;   r1_p_b = r1_b;    r2_p_b = r2_b;
                        } else if (n==1)  {
                                r3_q_a = r3_a;   r1_q_a = r1_a;    r2_q_a = r2_a;
                                r3_q_b = r3_b;   r1_q_b = r1_b;    r2_q_b = r2_b;
                        } else if (n==2)  {
                                r3_r_a = r3_a;   r1_r_a = r1_a;    r2_r_a = r2_a;
                                r3_r_b = r3_b;   r1_r_b = r1_b;    r2_r_b = r2_b;
                        } else  {
                                r3_s_a = r3_a;   r1_s_a = r1_a;    r2_s_a = r2_a;
                                r3_s_b = r3_b;   r1_s_b = r1_b;    r2_s_b = r2_b;
                        }
                    }

                    bool hit=false;

                    if ( !((r3_p_a>y && r3_q_a>y && r3_r_a>y && r3_s_a>y) || (r3_p_a<y && r3_q_a<y && r3_r_a<y && r3_s_a<y)) ) {
                        if (
                                ((r1_p_a>x && r1_q_a>x && r1_r_a>x && r1_s_a>x) || (r1_p_a<x && r1_q_a<x && r1_r_a<x && r1_s_a<x))
                             &&
                                ((r2_p_a>z && r2_q_a>z && r2_r_a>z && r2_s_a>z) || (r2_p_a<z && r2_q_a<z && r2_r_a<z && r2_s_a<z))
                            ) {
                            hit=false;
                        } else hit=true;
                    }
                    if (!hit) {
                        if ( !((r3_p_b>y && r3_q_b>y && r3_r_b>y && r3_s_b>y) || (r3_p_b<y && r3_q_b<y && r3_r_b<y && r3_s_b<y)) ) {
                            if (
                                    ((r1_p_b>x && r1_q_b>x && r1_r_b>x && r1_s_b>x) || (r1_p_b<x && r1_q_b<x && r1_r_b<x && r1_s_b<x))
                                 &&
                                    ((r2_p_b>z && r2_q_b>z && r2_r_b>z && r2_s_b>z) || (r2_p_b<z && r2_q_b<z && r2_r_b<z && r2_s_b<z))
                                ) {
                                hit=false;
                            } else hit=true;
                        }
                    }

                    counter2++;
                    if (hit) {
                        counter1++;
                        if (y<256) AY[y]=BlockInfo(254,0,0,0);

                        for (int xxx=-17; xxx<18; xxx++) {
                            if (xxx+x>=0 && xxx+x<512) {
                                BlockInfo** AZ=AX[xxx+x];
                                for (int zzz=-17; zzz<18; zzz++) {
                                    if (zzz+z>=0 && zzz+z<512) {
                                        BlockInfo* AY=AZ[zzz+z];
                                        for (int yyy=-17; yyy<18; yyy++) {
                                            if (yyy+y>=0 && yyy+y<256) {
                                                BlockInfo* hoppa=&(AY[yyy+y]);
//                                                        BlockInfo* hoppa=&AX[x+xxx][z+zzz][y+yyy];
                                                if (hoppa->id!=254 ) {
                                                    float dd2=10000.0;
                                                    if (yyy+17-3 > 0) dd2=d[xxx+17][zzz+17][yyy+17-3];
                                                    if ( dd2<=1.0) {
                                                        *hoppa=BlockInfo(46,0,0,0);
                                                    } else if (!(hoppa->id==46)) {
                                                        if (dd2<3.5) {
                                                            if ( (rand()%2000)==0 ) *hoppa=BlockInfo(89, 0, 0, 0);
                                                            else *hoppa=BlockInfo(5, 0, 0, 0);
                                                        } else if (!(hoppa->id==5)) {
                                                            float dd=d[xxx+17][zzz+17][yyy+17];
                                                            if (dd<20.0 || dd2<20 ) {
                                                                int h=(int)dd-13;
                                                                if (h<0) h=0;
                                                                h=2000 - h*200;
                                                                if ( ! ( rand()%h ) ) {
                                                                    *hoppa=BlockInfo(89, 0, 0, 0);
                                                                } else {
                                                                    float ch= (var1*var2*var3*75)*(1.0+sin( ((f_x*var1+f_y*var2+f_z*var3)/4 + float(((xxx+xx)*var2-(yyy+y)*var3+(zzz+zz)*var1)))/300 ) );
                                                                    int c=int( (abs(xxx+xx)+abs(yyy+y)+abs(zzz+zz)+rand()%20 + (f_x+f_y+f_z)/4 + ch ) / (20.0+25.0*var1+15.0*var2+15.0*var3) + 5500 )%4096;
                                                                    *hoppa=BlockInfo(95,0,c_ar[c],0);
//                                                                    col_a[c_ar[c]]++;
                                                                }
                                                            } else if (!(hoppa->id==95)) {
                                                                if (dd<21.0 || dd2<21.0) {
                                                                    if (rand()%3000 < int(  30.0  +20.0*sin( (f_x+f_y+f_z)/100.07       ) + 10.0*sin( (f_x/2+f_y/2+f_z/2)/55.07       ) ) ) *hoppa=BlockInfo(89,0,0,0);
                                                                }
                                                                if (dd<23.0 || dd2<23.0) {
                                                                    if (rand()%3000 < int(  30.0  +20.0*sin( (f_x+f_y+f_z)/100.07 + 0.1 ) + 10.0*sin( (f_x/2+f_y/2+f_z/2)/55.07 + 0.1 ) ) ) *hoppa=BlockInfo(89,0,0,0);
                                                                }
                                                                if (dd<25.0 || dd2<25.0) {
                                                                    if (rand()%3000 < int(  30.0  +20.0*sin( (f_x+f_y+f_z)/100.07 + 0.2 ) + 10.0*sin( (f_x/2+f_y/2+f_z/2)/55.07 + 0.2 ) ) ) *hoppa=BlockInfo(89,0,0,0);
                                                                }
                                                                if (dd<29.0 || dd2<29.0) {
                                                                    if (rand()%9000 < int(  30.0  +20.0*sin( (f_x+f_y+f_z)/100.07 + 0.2 ) + 10.0*sin( (f_x/2+f_y/2+f_z/2)/55.07 + 0.2 ) ) ) *hoppa=BlockInfo(89,0,0,0);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if (y<256)
                            if ((!(rand()%500)) && AY[y].id==1) AY[y]=BlockInfo(89,0,0,0); //glowstone
//                                    if ((!(rand()%500)) && AY[y].id==95) AY[y]=BlockInfo(89,0,0,0); //glowstone
                    }
                }
            }
        }
        printf("\ntime: %.1f seconds\n",m_clock.getElapsedTime().asSeconds());
    }


    int pixel_count_t=0,match_plus_t=0,no_match_t=0,id_count_t=0,draws_t=0;

    bool gpu=false;

    if (create_path) {
        int match_plus_t=0;
        gpu=false;
        sf::Image image_y;
        for (int y = 0; y < 256; y++) {
            sf::Color pixel;
            int c;
            int pixel_count=0,match_plus=0,no_match=0,id_count=0,draws=0;
            printf("Reading textures y=%3d ",y);
            fflush(stdout);

            image_y = texture_y[y].getTexture().copyToImage();
            for (int x = 0; x < 512; x++) {
                toggle2();
                for (int z = 0; z < 512; z++) {
                    pixel=image_y.getPixel(x,z);
                    if (pixel.a!=0) {
                        int c=pixel.b;
                        int cb=( ((c&128)==128) + ((c&64)==64)*2 + ((c&32)==32)*4 + ((c&16)==16)*8  );
                        cb=15-cb;
                        if ((c&8)==8) {
                            if (!(rand()%1000)) AX[x][z][y]=BlockInfo(89,0,0,0); //glowstone
                            AX[x][z][y]=BlockInfo(95,0,cb,0); //stained_glass
                        } else {
//                            AX[x][z][y]=BlockInfo(46,0,0,0); //tnt
                            AX[x][z][y]=BlockInfo(251,0,cb,0); //concrete
                            match_plus++;
                        }
//                    } else {
//                        AX[x][z][y]=BlockInfo(1,0,0,0); //stone
                    }
                }
            }
            match_plus_t    +=match_plus;
            printf("tnt_blocks=%6d total=%d   \r",match_plus,match_plus_t);
            fflush(stdout);
        }
        printf("\ntotal tnt_blocks=%8d\n",match_plus_t);
    }

    if (gpu) {
//        sf::RenderStates* renderstates_p=&shader_struct_vector[cave_shader_index]->RenderStates;
//        sf::Shader* shader_p=&shader_struct_vector[cave_shader_index]->Shader;

        sf::Clock m_clock;
        shader_p->setUniform("phase", int(1));

        sf::Texture main_texture;
        main_texture.create(35,35);
        main_sprite.setTexture(main_texture,true);
        main_sprite.setScale(1.0,1.0);

        sf::RenderTexture texture_fill[256];
        sf::Sprite sprite_fill[256];
        for (int t=0; t<256; t++) {
            printf("Creating texture_fill #%d\r",t+1);
            fflush(stdout);
            texture_fill[t].create(512,512);
            texture_fill[t].clear(sf::Color(0,0,0,0));
            texture_fill[t].draw(sprite_y[t]);
            sprite_fill[t].setTexture(texture_fill[t].getTexture(),true);
        }
        for (int t=0; t<256; t++) {
            texture_fill[t].display();
        }
        printf("\n");

        int pixel_count_t=0,match_plus_t=0,no_match_t=0,id_count_t=0,draws_t=0;
    //    app.setVerticalSyncEnabled(true);
        sf::Image image_y;
        for (int y = 0; y < 256; y++) {
            shader_p->setUniform("height", y);

            int flop_flip=(flip_flop+1)%2;

            update_main_texture(texture_ff, sprite_ff, flip_flop, test_shader_index);

            cp_sprite.setTexture(texture_ff[flip_flop].getTexture(),true);
            cp_sprite.setScale(0.2,0.2);
            cp_texture.draw(cp_sprite);
            cp_texture.display();

            main_mutex.lock();
            main_texture_pointer->update(cp_texture.getTexture());
            main_mutex.unlock();

//            image_y = texture_y[y].getTexture().copyToImage();
            image_y = texture_fill[y].getTexture().copyToImage();
            int pixel,id;
            int pixel_count=0,match_plus=0,no_match=0,id_count=0,draws=0;

    //        sf::RenderStates renderstate;
    //        renderstate.blendMode=MyBlendingMode;

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
                shader_p->setUniform("deltax", x);
                for (int z = 0; z < 512; z++) {
                    pixel=image_y.getPixel(x,z).r;
                    id=AX[x][z][y].id;
                    if (id==254 && pixel!=0) {
                        match_plus++;
                    } else if (id!=254 && pixel==0) {
                    } else {
                        no_match++;
                    }
                    if (id==254) {
                        id_count++;
                    }
                    if (pixel!=0) {
                        shader_p->setUniform("deltaz", z);

                        main_sprite.setPosition(float(x)-17,float(z)-17);
                        main_sprite.setTextureRect({x-17,z-17,35,35});

                        for (int yyy=-17; yyy<18; yyy++) {
                            if (yyy+y>=0 && yyy+y<256) {
                                shader_p->setUniform("deltay", yyy);
                                texture_y[y+yyy].display();
                                main_sprite.setTexture(texture_y[y+yyy].getTexture());
                                texture_y[y+yyy].draw(main_sprite,*renderstates_p);
                                draws++;
                            }
                        }

                        pixel_count++;
                    }
                }
            }

            pixel_count_t   +=pixel_count;
            match_plus_t    +=match_plus;
            no_match_t      +=no_match;
            id_count_t      +=id_count;
            draws_t         +=draws;

            printf("%3d match_plus=%8d no_match=%8d id_count=%8d pixel_count=%8d draws=%8d tot.draws=%8d\r",y,match_plus,no_match,id_count,pixel_count,draws,draws_t);
            fflush(stdout);

            main_sprite.setPosition(512.0,512.0);


            if (resized) {
                app.clear();

                for (int y = 0; y < 256; y++) {
                    main_sprite.setTexture(texture_y[y].getTexture(),true);
//                    app.draw(main_sprite,MyBlendingMode);
//                    app.draw(main_sprite,sf::BlendAdd);
                    app.draw(main_sprite);
                }
            }
            if (!nodisp) {
                if (!resized) {
                    for (int yyy=-17; yyy<18; yyy++) {
                        if (yyy+y>=0 && yyy+y<256) {
                            main_sprite.setTexture(texture_y[yyy+y].getTexture(),true);
    //                        app.draw(main_sprite,MyBlendingMode);
    //                        app.draw(main_sprite,sf::BlendAdd);
                            app.draw(main_sprite);
                        }
                    }
                }
            }

            app.draw(sprite_app[0]);  app.draw(sprite_app[1]); app.draw(sprite_app[2]);
            app.display();
        }

        printf("\n");

        sf::RenderTexture m_texture;
        m_texture.create(512,512);
        m_texture.clear(sf::Color(0,0,0,0));
//        m_texture.clear(sf::Color(0,0,0,1));
        main_sprite.setPosition(0.0,0.0);

        for (int y = 0; y < 256; y++) {
            texture_y[y].display();
            main_sprite.setTexture(texture_y[y].getTexture(),true);
            m_texture.draw(main_sprite);
//            m_texture.draw(main_sprite,MyBlendingMode);
    //        m_texture.draw(main_sprite,sf::BlendAdd);
            sprite_y[y].setPosition(512,512);
        }

        main_sprite.setPosition(512.0,512.0);
        main_sprite.setTexture(m_texture.getTexture());
        app.draw(main_sprite);

/*
        sprintf(tmp, "tiles/r.%d.%d.png", region_x, region_z);
        mkdir("tiles", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        m_texture.display();
        m_texture.getTexture().copyToImage().saveToFile(tmp);
*/
        app.setVerticalSyncEnabled(true);
        for (int n=0; n<1; n++) {
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
            if (n<1) {
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
            }
        }
        app.clear();
        app.draw(sprite_app[0]); app.draw(sprite_app[1]); app.draw(sprite_app[2]);
        main_sprite.setTexture(m_texture.getTexture(),true);
        main_sprite.setPosition(512.0,512.0);
        app.draw(main_sprite);
        app.display();

        printf("TOT match_plus=%8d no_match=%8d id_count=%8d pixel_count=%8d draws=%8d\n",match_plus_t,no_match_t,id_count_t,pixel_count_t,draws_t);

        printf("time: %.1f seconds\n",m_clock.getElapsedTime().asSeconds());

//        int match_plus_t=0;
//        gpu=false;
//        sf::Image image_y;
        for (int y = 0; y < 256; y++) {
            sf::Color pixel;
            int c;
            int pixel_count=0,match_plus=0,no_match=0,id_count=0,draws=0;
            printf("Reading textures y=%3d ",y);
            fflush(stdout);

            image_y = texture_y[y].getTexture().copyToImage();
            for (int x = 0; x < 512; x++) {
                toggle2();
                for (int z = 0; z < 512; z++) {
                    pixel=image_y.getPixel(x,z);
                    if (pixel.a!=0) {
                        if (pixel.r==255) {
                            AX[x][z][y]=BlockInfo(5,0,0,0); //planks
                            match_plus++;
                        } else if (pixel.r==254) {
                            AX[x][z][y]=BlockInfo(46,0,0,0); //tnt
                        } else if (pixel.g==255) {
                            AX[x][z][y]=BlockInfo(5,0,0,0); //planks
                        } else if (pixel.b!=0) {
                            if (!(rand()%1000)) AX[x][z][y]=BlockInfo(89,0,0,0); //glowstone
                            else AX[x][z][y]=BlockInfo(95,0,int(pixel.b/16),0); //stained_glass
//                            AX[x][z][y]=BlockInfo(95,0,0,0); //stained_glass
                        }
                    } else {
//                        if (!(rand()%1000)) AX[x][z][y]=BlockInfo(89,0,0,0); //glowstone

                        AX[x][z][y]=BlockInfo(1,0,0,0); //stone
                    }
                }
            }
            match_plus_t    +=match_plus;
            printf("tnt_blocks=%6d total=%d   \r",match_plus,match_plus_t);
            fflush(stdout);
        }
        printf("\ntotal tnt_blocks=%8d\n",match_plus_t);


    }

    sf::RenderTexture m_texture;
    m_texture.create(512,512);
    m_texture.clear(sf::Color(0,0,0,1));
    main_sprite.setPosition(0.0,0.0);

    for (int y = 0; y < 256; y++) {
        main_sprite.setTexture(texture_y[y].getTexture(),true);
//        m_texture.draw(main_sprite,MyBlendingMode);
//        m_texture.draw(main_sprite,sf::BlendAdd);
        m_texture.draw(main_sprite);
//        sprite_y[y].setPosition(512,512);
    }

    sprintf(tmp, "tiles/r.%d.%d.png", region_x, region_z);
    mkdir("tiles", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    m_texture.display();
    m_texture.getTexture().copyToImage().saveToFile(tmp);

    for (int x = 0; x < 512; x++) {
        xx=x+pos_offsetx;
        BlockInfo** AZ=AX[x];
        for (int z = 0; z < 512; z++) {
            zz=z+pos_offsetz;
            BlockInfo* AY=AZ[z];
            toggle2();
            for (int y = 0; y < 256; y++) {
                if (y<3) {
                    AY[y] = BlockInfo(7, 0, 0, 0);
                } else if (AY[y].id==254) {
                    AY[y]=BlockInfo(5,0,0,0);
                } else if (AY[y].id==95) {
                    if (!(rand()%10)) {
                        for (int xxx = -1; xxx < 2; xxx++) {
                            for (int zzz = -1; zzz < 2; zzz++) {
                                for (int yyy = -1; yyy < 2; yyy++) {
                                    if (xxx+x>=0 && xxx+x<512 && yyy+y>=0 && yyy+y<256 && zzz+z>=0 && zzz+z<512) {
                                        if (AX[xxx+x][zzz+z][yyy+y].id==1) {
                                            AX[xxx+x][zzz+z][yyy+y]=BlockInfo(89,0,0,0);
                                            yyy=2;zzz=2;xxx=2;
                                        }
                                    }
                                }
                            }
                        }
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

    app_size=app.getSize();
    app_position=app.getPosition();

    delete_shader(cave_shader_index);
    delete_shader(test_shader_index);
    delete editor;

    return 0;
}

void update_main_texture(sf::RenderTexture* texture, sf::Sprite* sprite, int& flip_flop, int shader_index) {
    int flop_flip=(flip_flop+1)%2;
    shader_struct_vector[shader_index]->Shader.setUniform("blur_radius", float(1.0/512.0));
    texture[flop_flip].draw(sprite[flip_flop],shader_struct_vector[shader_index]->RenderStates);
    texture[flop_flip].display();
    flip_flop=flop_flip;
}

void update_caves_region(sf::RenderTexture& texture, sf::Sprite& sprite, int texture_index, int shader_index) {
    shader_struct_vector[shader_index]->Shader.setUniform("height", texture_index);
    texture.draw(sprite,shader_struct_vector[shader_index]->RenderStates);
}

int main_REPACK(char* region_filename) {
    bool nodisp=false;
    if (file_exists("nodisp.on")) nodisp=true;
//    int load_leeg=0;

    int num;
    int region_x;
    int region_z;
    std::string path=GetBaseDir(std::string() + region_filename);
    std::string name=GetFileName(std::string() + region_filename);

    if ( (num=sscanf(name.c_str(), "r.%d.%d.mca", &region_x, &region_z))!=2) {
        printf("Can't sscanf filename: path=%s x=%d y=%d\n",path.c_str(), region_x, region_z);
        return -1;
    } else {
//        printf("sscanf: %s/r.%d.%d.mca\n", path.c_str(), region_x, region_z);
    }

    if (file_exists(region_filename) ) {
        printf(" File %s exists.",region_filename);
        fflush(stdout);
    } else {
        printf(" File %s does not exists... \n",region_filename);
        return -1;
    }

    MCEditor *editor;
    editor = new MCEditor(region_x,region_z);
    editor->mca_coder.reset_block(region_x,region_z);
    remove_block_entities=0;

    editor->mca_coder.loadMCA(region_filename);
    printf("Ok. Testing: ");

    MCRegion region(region_x, region_z, 0, 0, 0, 512, 512, 256);
    BlockInfo*** AX=region.A;

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

    editor->mca_coder.current_filename_mca=region_filename;

    if (file_exists(editor->mca_coder.current_filename_mca.c_str())) {
        char cmd[200];
        sprintf(cmd,"rm %s",editor->mca_coder.current_filename_mca.c_str());
        system(cmd);
    }
    editor->setRegion(region);
    printf(" Region ready, returning\n");

    delete editor;
    return 0;
}

