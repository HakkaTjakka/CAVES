#define SFML_STATIC
#define PI 3.141592653589793
#include <curses.h>
#include <stdio.h>
//#include <windows.h>
#include <sys/stat.h>
#include <cstring>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include "shaders.hpp"

#include "MCEditor/MCEditor.h"
#include "MCEditor/BlockEntity.h"
#include "MCEditor/MCACoder.h"

//#include "functions.hpp"

int remove_block_entities=1;
int chunk_offsetx, chunk_offsetz;
int region_xxx,region_zzz;
int MCEDITOR_running=0;
int MCEDITOR_stop=0;

int repl_str(char *str, char *orig, char *rep)
{
    static char buffer[2000];
    char *p;
    if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
        return false;
    strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
    buffer[p-str] = '\0';
    sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));
    strcpy(str,buffer);
    return true;
}

bool file_exists(const char * filename)
{
    struct stat stat_buffer;
    int exist = stat(filename,&stat_buffer);
    if (exist==0)
    {
        return true;
    }
    return false;
}

extern sf::Sprite* main_sprite_pointer;

int toggle_2=0;
void toggle2() {
    toggle_2=(toggle_2+1); if (toggle_2>=5000) toggle_2=0;;
    if (toggle_2==0) { printf("/\b"); fflush(stdout); }
    else if (toggle_2==1250) {
        static int t=0;
        t++;
        if (t>100) { printf("o-\b"); t=0;  fflush(stdout); }
        else { printf("-\b");  fflush(stdout); }
        main_sprite_pointer->setRotation(main_sprite_pointer->getRotation()+0.5);
    }
    else if (toggle_2==2500) { printf("\\\b"); fflush(stdout); }
    else if (toggle_2==3750) { printf("|\b"); fflush(stdout); }

}

int toggle_3=0;
void toggle3() {
    static int toggle=0;
    if (toggle_3++>=10485760) toggle_3=0;
    if (toggle_3==0) { printf("/\b"); fflush(stdout); }
    else if (toggle_3==2621440) { printf("o-\b"); fflush(stdout); }
    else if (toggle_3==5242880) { printf("\\\b"); fflush(stdout); }
    else if (toggle_3==7864320) {
        printf("|\b");
        fflush(stdout);
        main_sprite_pointer->setRotation(main_sprite_pointer->getRotation()+0.5);
    }
}

void make_color_array(int* c_ar) {
    static bool first=true;
    if (first) {
        first=false;
        srand(12345);
        for (int i=0; i<4096; i++) {
            c_ar[i]=rand()%16;
            if (i!=0) while (c_ar[i]==c_ar[i-1]) c_ar[i]=rand()%16;

        }
    }
}

void make_distance_array(float d[35][35][35]) {
    static bool first=true;
    if (first) {
        for (int xxx=-17; xxx<18; xxx++) {
            for (int zzz=-17; zzz<18; zzz++) {
                for (int yyy=-17; yyy<18; yyy++) {
                    d[xxx+17][zzz+17][yyy+17]=sqrt(float(xxx*xxx)+float(yyy*yyy)+float(zzz*zzz));
                }
            }
        }
    }
}


float fast_sin[4096];

float get_fast_sin(float rot) {
    static float parm=4096.0/(2.0*PI);
    if (rot>=0) return fast_sin[(int)(rot*parm)&4095];
    else return -fast_sin[(int)(-rot*parm)&4095];
}

void fast_sin_init() {
    static bool first=true;
    if (first) for (int n=0; n<4096; n++) fast_sin[n]=sin(2.0*PI*((float)n/4096.0));
    first=false;
}

void make_caves(char* shader_name);

int main_mceditor() {
    fast_sin_init();
    printf("make_caves();\n");
    make_caves("shaders/caves.frag");
}

void MCEDITOR_THREAD() {
    main_mceditor();
    MCEDITOR_stop=0;
    MCEDITOR_running=0;
}

sf::Thread MCEDITOR(&MCEDITOR_THREAD);

void launch_MCEDITOR() {

    if (MCEDITOR_running==1) {
        printf("MCEditor() already running\n");
        return;
    }
    MCEDITOR_running=1;
    MCEDITOR.launch();
}

void terminate_MCEDITOR() {  MCEDITOR_running=0; MCEDITOR.terminate(); }

int read_array(double ARRAY[100][5]) {
    FILE* HOP;
    if ((HOP = fopen ("tunnels.txt", "r"))!=NULL) {
        char line[200];
        int N=0;
        int L=0;
        while (fgets (line,200, HOP)!=NULL) {
            L++;

            while (int ret=repl_str(line,",","."));
            int num;
            if ( (num=sscanf(line,"%lf %lf %lf %lf %lf\n",&ARRAY[N][0],&ARRAY[N][1],&ARRAY[N][2],&ARRAY[N][3],&ARRAY[N][4])) < 1) {
            } else {
                printf("%2d LOADED (%d) from LINE %2d:",N,num,L);
                for (int i=0; i<num; i++) printf(" %8.3f",ARRAY[N][i]);
                N++;
                printf("\n");
            }
        }
        fclose(HOP);

        if (N==0) {
            printf("Error reading tunnels.txt\n");
            return 0;
        }
    } else {
        printf("Error reading tunnels.txt\n");
        return 0;
    }
    return 1;
}

MCEditor* READ_REGION(int region_x, int region_z) {
    bool load_empty=false;

    char region_filename[1024];
    sprintf(region_filename, "saves/caves/region/r.%d.%d.mca", region_x, region_z);

    if ( !file_exists(region_filename) ) {
        printf("File %s doesn't exist, creating new\n",region_filename);
        load_empty=true;
    } else {
        printf("file %s exists, skipping...\n",region_filename);
        return NULL;
    }

    MCEditor *editor = new MCEditor(region_x,region_z);

    if (load_empty) {
        editor->mca_coder.remove_block_entities=1;
        if (!file_exists("saves/template/region/r.0.0.mca")) {
            if (!file_exists("template/region/r.0.0.mca")) {
                printf("Cannot find empty region template: %s or %s\n","saves/template/region/r.0.0.mca","template/region/r.0.0.mca");
                delete editor;
                return NULL;
            } else {
                editor->mca_coder.loadMCA("template/region/r.0.0.mca");
            }
        } else {
            editor->mca_coder.loadMCA("saves/template/region/r.0.0.mca");
        }
        editor->mca_coder.setPOSITIONS();

        printf("Creating region r.%d.%d.mca:\n",region_x,region_z);
        editor->mca_coder.reset_block();
    } else {
        editor->mca_coder.reset_block();
        remove_block_entities=0;
        printf(" File %s exists... ",region_filename);
        editor->mca_coder.loadMCA(region_filename);
    }

    return editor;
}

