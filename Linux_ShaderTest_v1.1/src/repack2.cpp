#define SFML_STATIC
#define PI 3.141592653589793

//#include <conio.h>
#include <curses.h>
#include "MCEditor/MCEditor.h"
#include "MCEditor/BlockEntity.h"
#include "MCEditor/MCACoder.h"
#include <math.h>
#include <cstring>
#include <string>

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <map>
#include <vector>

#include <SFML/System/Thread.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "shaders.hpp"
#include "functions.hpp"
#include <algorithm>

int main_REPACK2(char* region_filename) {
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
    region_xxx_glob=region_x;
    region_zzz_glob=region_z;

    if (file_exists(region_filename) ) {
        printf(" File %s exists. ",region_filename);
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


    if (teleport2) {
        std::vector<Chunk_struct> Chunk_vector;
        std::vector<Chunk_struct> Chunk_vector_move;
        std::vector<Fly_struct> Fly_vector;

//        std::vector<struct Chunk_struct> Chunk_vector_interpolate;
//        std::map<int, struct Chunk_map_struct> Chunk_map;

        struct Chunk_struct OneChunk;
        struct Fly_struct OneFly;
//        struct Chunk_map_struct OneChunk_map;

        int num_chunks_air = 0;
        int num_chunks_none = 0;
        int num_chunks = 0;

        printf("\n");

        bool first = true;
        bool first2 = true;

        int index_first=-1;
        int index_first2=-1;
        int index=-1;

        bool to_save=false;
        for (int chunk_x = 0; chunk_x < 32; chunk_x++) {
            for (int chunk_z = 0; chunk_z < 32; chunk_z++) {
                for (int chunk_y = 0; chunk_y < 16; chunk_y++) {

                    bool redstone=false;

                    int air = 0, water = 0;
                    int avg_air_x=0;
                    int avg_air_y=0;
                    int avg_air_z=0;
                    int x_p,y_p,z_p;
                    float l=100;
                    for (int x = 0; x < 16; x++ ) {
                        BlockInfo** AZ=AX[x+chunk_x*16];
                        for (int z = 0; z < 16; z++ ) {
                            BlockInfo* AY=AZ[z+chunk_z*16];
                            for (int y = 0; y < 16; y++ ) {
                                BlockInfo bi=AY[y+chunk_y*16];
                                if (bi.id==0) {
                                    float l_n = abs(x-8)+abs(y-8)+abs(z-8);
                                    if (l_n < l) {
                                        l = l_n;
                                        x_p = x;
                                        y_p = y;
                                        z_p = z;
                                    }
                                    air++;
                                    avg_air_x+=x;
                                    avg_air_y+=y;
                                    avg_air_z+=z;

                                }
                                else if (bi.id==9) water++;
                            }
                        }
                    }
                    if (air>0) {
                        avg_air_x=avg_air_x/air;
                        avg_air_y=avg_air_y/air;
                        avg_air_z=avg_air_z/air;
                    }
                    OneChunk.x=chunk_x;
                    OneChunk.y=chunk_y;
                    OneChunk.z=chunk_z;
                    OneChunk.avg_x=avg_air_x;
                    OneChunk.avg_y=avg_air_y;
                    OneChunk.avg_z=avg_air_z;
                    if (air > 0) {
                        OneChunk.air=1;
                        num_chunks_air++;
                    } else {
                        OneChunk.air=0;
                    }
                    num_chunks++;

                    if (air > 0) {
                        printf("Move to: x=%3d y=%3d z=%3d air=%d n=%d",
                                OneChunk.x*16+OneChunk.avg_x,
                                OneChunk.y*16+OneChunk.avg_y,
                                OneChunk.z*16+OneChunk.avg_z,
                                OneChunk.air,Chunk_vector.size());
                        Chunk_vector.push_back(OneChunk);
                        index++;
                    }

                    if (first) {
                        if (air > 0) {
                            first=false;
                            index_first=index;
                            printf(" first\n");
                        }
                    }

                    if (air > 0) {
                        printf("\r");
                        fflush(stdout);

                    }
                }
            }
        }
        printf("\n");
        int cvs=Chunk_vector.size();
        if (first == false) {
            printf("Move to: x=%3d y=%3d z=%3d air=%d n=%d\n",
                    Chunk_vector[index_first].x*16+Chunk_vector[index_first].avg_x,
                    Chunk_vector[index_first].y*16+Chunk_vector[index_first].avg_y,
                    Chunk_vector[index_first].z*16+Chunk_vector[index_first].avg_z,
                    Chunk_vector[index_first].air, Chunk_vector.size() );
            fflush(stdout);
            Chunk_vector_move.push_back(Chunk_vector[index_first]);
            x_chunk = Chunk_vector[index_first].x;
            y_chunk = Chunk_vector[index_first].y;
            z_chunk = Chunk_vector[index_first].z;
            x_chunk_sub = Chunk_vector[index_first].avg_x;
            y_chunk_sub = Chunk_vector[index_first].avg_y;
            z_chunk_sub = Chunk_vector[index_first].avg_z;

            OneChunk=Chunk_vector[index_first];

            int cnt=0;
            while (Chunk_vector.size() > 1) {
                Chunk_vector.erase(Chunk_vector.begin()+index_first);
                std::sort(Chunk_vector.begin(), Chunk_vector.end(), compareChunk);

                cnt++;
                float d_x=((float)Chunk_vector[0].x*16 + (float)Chunk_vector[0].avg_x - (float)x_chunk*16 - (float)x_chunk_sub);
                float d_y=((float)Chunk_vector[0].y*16 + (float)Chunk_vector[0].avg_y - (float)y_chunk*16 - (float)y_chunk_sub);
                float d_z=((float)Chunk_vector[0].z*16 + (float)Chunk_vector[0].avg_z - (float)z_chunk*16 - (float)z_chunk_sub);

                float dist=sqrt( d_x*d_x + d_y*d_y + d_z*d_z );

                index_first=0;
                if (dist>40 || Chunk_vector.size()==1) {
                    printf("Move to: x=%3d y=%3d z=%3d air=%d n=%d cnt=%2d dist=%.2f\n",
                            Chunk_vector[0].x*16+Chunk_vector[0].avg_x,
                            Chunk_vector[0].y*16+Chunk_vector[0].avg_y,
                            Chunk_vector[0].z*16+Chunk_vector[0].avg_z,
                            Chunk_vector[0].air,Chunk_vector.size(), cnt, dist);
                    fflush(stdout);

//                    Chunk_vector_move.push_back(Chunk_vector[0]);
                    Chunk_vector_move.push_back(OneChunk);

                    OneChunk=Chunk_vector[0];

                    x_chunk = Chunk_vector[0].x;
                    y_chunk = Chunk_vector[0].y;
                    z_chunk = Chunk_vector[0].z;
                    x_chunk_sub = Chunk_vector[0].avg_x;
                    y_chunk_sub = Chunk_vector[0].avg_y;
                    z_chunk_sub = Chunk_vector[0].avg_z;
                    cnt=0;
                } else {
                    printf("Move to: x=%3d y=%3d z=%3d air=%d n=%d cnt=%2d dist=%.2f\n",
                            Chunk_vector[0].x*16+Chunk_vector[0].avg_x,
                            Chunk_vector[0].y*16+Chunk_vector[0].avg_y,
                            Chunk_vector[0].z*16+Chunk_vector[0].avg_z,
                            Chunk_vector[0].air,Chunk_vector.size(), cnt, dist);
                    fflush(stdout);
                }
            }
            Chunk_vector_move.push_back(OneChunk);

            x_chunk = Chunk_vector_move[0].x;
            y_chunk = Chunk_vector_move[0].y;
            z_chunk = Chunk_vector_move[0].z;
            x_chunk_sub = Chunk_vector_move[0].avg_x;
            y_chunk_sub = Chunk_vector_move[0].avg_y;
            z_chunk_sub = Chunk_vector_move[0].avg_z;

            bool start=true;
            float fx,prev_x=0;
            float fy,prev_y=0;
            float fz,prev_z=0;
            int t=0;
            float prev_yaw=0;
            float prev_pitch=0;

            char line[1000];

            FILE* f=fopen("out.txt","a");

            printf("\n");

            for (index=1; index<Chunk_vector_move.size(); index++ ) {
                float d_x=((float)Chunk_vector_move[index].x + (float)Chunk_vector_move[index].avg_x/16.0 - (float)x_chunk - (float)x_chunk_sub/16.0);
                float d_y=((float)Chunk_vector_move[index].y + (float)Chunk_vector_move[index].avg_y/16.0 - (float)y_chunk - (float)y_chunk_sub/16.0);
                float d_z=((float)Chunk_vector_move[index].z + (float)Chunk_vector_move[index].avg_z/16.0 - (float)z_chunk - (float)z_chunk_sub/16.0);
                float dist=sqrt( d_x*d_x + d_y*d_y + d_z*d_z );

                int d=int(sqrt(dist));
                if (d<1) d=1;

                for (int n=0; n<=d; n++) {
                    fx=(float)x_chunk + (float)x_chunk_sub/16.0 + d_x*(float)n/(float)d;
                    fy=(float)y_chunk + (float)y_chunk_sub/16.0 + d_y*(float)n/(float)d;
                    fz=(float)z_chunk + (float)z_chunk_sub/16.0 + d_z*(float)n/(float)d;
                    if (start || n>0) {
                        if (start == false) {
                            float yaw=atan2( -(fx-prev_x), (fz-prev_z) );
                            float pitch=atan2( sqrt( (fx-prev_x)*(fx-prev_x) + (fz-prev_z)*(fz-prev_z) ), (fy-prev_y) );

                            OneFly.yaw=yaw*180.0/M_PI;
                            OneFly.pitch=pitch*180.0/M_PI-90.0;
                            Fly_vector.push_back(OneFly);

                            yaw=(prev_yaw*3+yaw)/4.0;
                            pitch=(prev_pitch*3+pitch)/4.0;

                            prev_yaw=yaw;
                            prev_pitch=pitch;

                            printf("yaw=%6.1f pitch=%6.1f", yaw*180.0/M_PI, pitch*180.0/M_PI-90.0);
//                            printf("%.2f/%.2f/0.0/70.0\n", pitch*180.0/M_PI-90.0, yaw*180.0/M_PI);
                            printf(" --  %s%.2f/%.2f/0.0/70.0\r", line, pitch*180.0/M_PI-90.0, yaw*180.0/M_PI);
                            fflush(stdout);

                            fprintf(f,"%s%.2f/%.2f/0.0/70.0\n", line, pitch*180.0/M_PI-90.0, yaw*180.0/M_PI);
                        }
                        start = false;
                        printf("Walk: x=%6.2f y=%6.2f z=%6.2f tnt=%d air=%d d=%2d dist=%6.2f n=%4d i=%4d ",
                                fx*16, fy*16, fz*16,
                                Chunk_vector_move[index].dynamite, Chunk_vector_move[index].air, d, dist, t, index);
                        t++;
//                        printf("%.2f/%.2f/%.2f/", region_x*512+fx*16, fy*16, region_z*512+fz*16);
//                        sprintf(line,"%.2f/%.2f/%.2f/", region_x*512+fx*16+8, fy*16+8, region_z*512+fz*16+8);
                        sprintf(line,"%.2f/%.2f/%.2f/", region_x*512+fx*16, fy*16, region_z*512+fz*16);
                        OneFly.FOV=70.0;
                        OneFly.tilt=0.0;
                        OneFly.x=region_x*512+fx*16;
                        OneFly.y=fy*16;
                        OneFly.z=region_z*512+fz*16;
                    }
                    if ( ! ( n==d && index==Chunk_vector_move.size()-1 ) ) {
                        prev_x=fx; prev_y=fy; prev_z=fz;
                    }
                }
                x_chunk=Chunk_vector_move[index].x;
                y_chunk=Chunk_vector_move[index].y;
                z_chunk=Chunk_vector_move[index].z;
                x_chunk_sub = Chunk_vector_move[index].avg_x;
                y_chunk_sub = Chunk_vector_move[index].avg_y;
                z_chunk_sub = Chunk_vector_move[index].avg_z;

//                printf("\n");
            }


            if (start == false) {

                float yaw=atan2( -(fx-prev_x), (fz-prev_z) );
                float pitch=atan2( sqrt( (fx-prev_x)*(fx-prev_x) + (fz-prev_z)*(fz-prev_z) ), (fy-prev_y) );
//                yaw=(prev_yaw*3+yaw)/4.0;
//                pitch=(prev_pitch*3+pitch)/4.0;
                OneFly.yaw=yaw*180.0/M_PI;
                OneFly.pitch=pitch*180.0/M_PI-90.0;
                Fly_vector.push_back(OneFly);
                yaw=(prev_yaw*3+yaw)/4.0;
                pitch=(prev_pitch*3+pitch)/4.0;

//                printf("yaw=%6.2f pitch=%6.2f\n", yaw*180.0/M_PI, pitch*180.0/M_PI-90.0);
//                printf("%.2f/%.2f/0.0/70.0\n", pitch*180.0/M_PI-90.0, yaw*180.0/M_PI);
                printf("yaw=%6.1f pitch=%6.1f", yaw*180.0/M_PI, pitch*180.0/M_PI-90.0);
                printf(" --  %s%.2f/%.2f/0.0/70.0\n", line, pitch*180.0/M_PI-90.0, yaw*180.0/M_PI);
                fprintf(f,"%s%.2f/%.2f/0.0/70.0\n", line, pitch*180.0/M_PI-90.0, yaw*180.0/M_PI);

            }
            fclose(f);

//            printf("\n");

            f=fopen("air.txt","a");
            index=0;
            int last=Fly_vector.size()-1;
            Fly_struct u;

            float x_prev,y_prev,z_prev;
            if (last>=0) {
                x_prev=Fly_vector[0].x;
                y_prev=Fly_vector[0].y;
                z_prev=Fly_vector[0].z;
            };
            float d_x=0;
            float d_y=0;
            float d_z=0;

            for (int index=1; index<=last; index++) {
//            for (auto u : Fly_vector) {
//                u=Fly_vector[index];

                float avg_yaw=0.0;
                float avg_pitch=0.0;
                float avg_tilt=0.0;
                float avg_x=0.0;
                float avg_y=0.0;
                float avg_z=0.0;
                int cnt=0;
                int cnt2=0;
                int loop=0;
//                while ( sqrt(d_x*d_x+d_y*d_y+d_z*d_z) < 100.0 && index<=last) {
                    loop++;
                    u=Fly_vector[index];
                    d_x+=fabs(u.x-x_prev);
                    d_y+=fabs(u.y-y_prev);
                    d_z+=fabs(u.z-z_prev);

                    x_prev=u.x;
                    y_prev=u.y;
                    z_prev=u.z;

//                    avg_pitch += Fly_vector[index  ].pitch*1.0;
//                    avg_yaw   += Fly_vector[index  ].yaw*1.0;
//                    cnt+=1;

                    if (loop==1) {
                        for (int inter=0; inter<=1; inter++) {
                            if (index+inter<=last)  {   u=Fly_vector[index+inter];
                                                        avg_pitch += u.pitch;
                                                        avg_yaw   += u.yaw  ;
                                                        avg_tilt  += u.yaw  ;
                                                        avg_x     += u.x    ;
                                                        avg_y     += u.y    ;
                                                        avg_z     += u.z    ;
                                                        cnt+=1; cnt2+=1; }
                        }
                    }
                    index++;
//                }

                d_x=0;
                d_y=0;
                d_z=0;
                avg_x/=(float)cnt;
                avg_y/=(float)cnt;
                avg_z/=(float)cnt;
                avg_yaw/=(float)cnt;
                avg_pitch/=(float)cnt;
//                if (cnt-5 >0) avg_tilt/=(float)cnt2;
                if (cnt2 >0) avg_tilt/=2.0*(float)cnt2;
                fprintf(f,"%.2f/%.2f/%.2f/%.2f/%.2f/%.2f/%.2f\n",
                        u.x, u.y, u.z, avg_pitch, avg_yaw, avg_tilt, u.FOV);
                printf("loops=%d %.2f/%.2f/%.2f/%.2f/%.2f/%.2f/%.2f\n",
                        loop, u.x, u.y, u.z, avg_pitch, avg_yaw, avg_tilt, u.FOV);

            }
            fclose(f);
        }
        printf("tot: %5d   air: %5d   none: %5d\n",
               num_chunks,  num_chunks_air,  num_chunks_none);

        if (to_save) {
            editor->mca_coder.current_filename_mca=region_filename;

            if (file_exists(editor->mca_coder.current_filename_mca.c_str())) {
                char cmd[200];
                sprintf(cmd,"rm %s",editor->mca_coder.current_filename_mca.c_str());
                system(cmd);
            }
            editor->setRegion(region);
            printf(" Region ready, returning\n");
        } else {
//memory leak
            editor->mca_coder.clearModification();
        }

        delete editor;
        return 0;
    }
}

