#define SFML_STATIC
#define PI 3.141592653589793

//#include <conio.h>
#include <curses.h>
#include "MCEditor/MCEditor.h"
#include "MCEditor/BlockEntity.h"
#include "MCEditor/MCACoder.h"
#include <math.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <SFML/System/Thread.hpp>

extern int repl_str(char *str, char *orig, char *rep);
extern int toggle2();
extern int first_MCEDIT;
extern bool file_exists(const char * filename);
extern void reset_block();
extern std::string MCAFileNameXZ(int x, int z);

extern int region_x_old,region_z_old;
extern std::string file_name_MCA;

int main_mceditor();

int main_CAVES(int region_x, int region_z, unsigned char* mc);
void launch_MCEDITOR();
void make_caves();

int remove_block_entities=1;
int chunk_offsetx, chunk_offsetz;
int region_xxx,region_zzz;
int MCEDITOR_running=0;
int MCEDITOR_stop=0;
float fast_sin[4096];
MCEditor editor;
unsigned char region_block[512*256*512*4];

int main(int argc, char ** argv) {
    launch_MCEDITOR();
    while (MCEDITOR_running==0) sleep(100);
    while (MCEDITOR_running==1) sleep(1000);
}

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

#define sin get_fast_sin

int main_mceditor() {
    fast_sin_init();
    printf("make_caves();\n");
    make_caves();
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

void terminate_MCEDITOR() { MCEDITOR.terminate(); }

void make_caves() {
    mkdir("saves", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("saves/caves", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("saves/caves/region", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    int region_x=0,region_z=0;
    int size_regions=0;
    char tmp[512];

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
                printf("Creating caves: region.%d.%d.mca\n",region_x,region_z);
                main_CAVES(region_x, region_z, region_block);
            }
        }
    }
}

int main_CAVES(int region_x, int region_z, unsigned char* mc) {
    int xx,zz;
    int load_leeg;

    int size_regions=0;
	int first_loop=1;
    bool zisout=false;
    bool xisout=false;

    region_xxx=region_x;
    region_zzz=region_z;

    chunk_offsetx=region_x*32;;
    chunk_offsetz=region_z*32;

    load_leeg=0;

    bool do_model=false;

    std::string fname=MCAFileNameXZ(region_x, region_z);
    char tmp[1024];
    sprintf(tmp, "saves/caves/region/r.%d.%d.mca", region_x, region_z);
    fname=tmp;

    if ( !file_exists(fname.c_str() ) ) {
        printf("File %s doesn't exist, creating new\n",fname.c_str());
        load_leeg=1;
    } else {
        printf("file %s exists, skipping...\n",fname.c_str());
        return 0;
    }

    static int c_ar[4096];
    {
        static bool first=true;
        if (first) {
            first=false;
            srand(12345);
            for (int i=0; i<4096; i++) c_ar[i]=rand()%16;
        }
    }

//	srand(time(0));

    if (load_leeg) {
        static bool first=true;

        remove_block_entities=1;
        first_MCEDIT=1;
        if (!file_exists("saves/template/region/r.0.0.mca")) {
            if (!file_exists("template/region/r.0.0.mca")) {
                printf("Cannot find empty region template: %s or %s\n","saves/template/region/r.0.0.mca","template/region/r.0.0.mca");
//                region.eraseRegion();
                return -1;
            } else {
                editor.mca_coder.loadMCA("template/region/r.0.0.mca");
            }
        } else {
            editor.mca_coder.loadMCA("saves/template/region/r.0.0.mca");
        }
        editor.mca_coder.setPOSITIONS();
        first_MCEDIT=0;
        region_x_old=0,region_z_old=0;

        printf("Creating region r.%d.%d.mca:\n",region_x,region_z);
        reset_block();
    } else {
        reset_block();
        remove_block_entities=0;
        printf(" File %s exists... ",fname.c_str());
        first_MCEDIT=1;
        editor.mca_coder.loadMCA(fname.c_str());
        first_MCEDIT=0;
        region_x_old=0,region_z_old=0;

    }

    MCRegion region(0, 0, 0, 512, 512, 256);
    BlockInfo*** AX=region.A;


    int real_max_x=-std::numeric_limits<int>::max();
    int real_min_x=std::numeric_limits<int>::max();

    int real_max_z=-std::numeric_limits<int>::max();
    int real_min_z=std::numeric_limits<int>::max();

    int real_max_y=-std::numeric_limits<int>::max();
    int real_min_y=std::numeric_limits<int>::max();

    if (!load_leeg) {
        printf("Ok. Testing: ");
        if (1) {
            editor.mca_coder.getBlock_FAST(region);
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
            static int prev_region_x=-99999999;
            static int prev_region_z=-99999999;
            static bool first=true;

            for (int x = 0; x < 512; x++) {
                BlockInfo** AZ=AX[x];
                for (int z = 0; z < 512; z++) {
                    BlockInfo* AY=AZ[z];
                    for (int y = 0; y < 256; y++) {
                        BlockInfo bi=editor.mca_coder.getBlock(x,z,y);
                        if (bi.id!=0) {
                            AY[y]=BlockInfo(bi.id,bi.add,bi.data,bi.block_light,bi.sky_light);
                        } else {
                            AY[y]=BlockInfo();
                        }
                    }
                }
            }
            printf(" Ok.\n");
        }
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

    size_t max_off=512*512*256*4;

    double ARRAY[100][5];

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
//            return-1;
        }
    } else {
        printf("Error reading tunnels.txt\n");
//        return-1;
    }

    int counter1=0;
    int counter2=0;

    printf("tunnels:\n");
    static bool first=true;
    static float d[35][35][35];
    if (first) {
        first=false;
        for (int xxx=-17; xxx<18; xxx++) {
            for (int zzz=-17; zzz<18; zzz++) {
                for (int yyy=-17; yyy<18; yyy++) {
                    d[xxx+17][zzz+17][yyy+17]=sqrt(float(xxx*xxx)+float(yyy*yyy)+float(zzz*zzz));
                }
            }
        }
    }

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
        BlockInfo** AZ=AX[x];
        xx=x+chunk_offsetx*16;
        printf("\rx=%3d => %d/%d\r",x,counter1,counter2);
        fflush(stdout);
        for (int z = 0; z < 512; z++) {
            zz=z+chunk_offsetz*16;
            BlockInfo* AY=AZ[z];
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


                        r3_a= 1+int(115.0 + 144.0*sin( (
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
                                                            if (dd<19.0 || dd2<19 ) {
                                                                int h=(int)dd-13;
                                                                if (h<0) h=0;
                                                                h=2000 - h*200;
                                                                if ( ! ( rand()%h ) ) {
                                                                    *hoppa=BlockInfo(89, 0, 0, 0);
                                                                } else {
                                                                    float ch= 20*(1.0+sin( ((f_x*var1+f_y*var2+f_z*var3)/8 + float((xxx+xx-yyy-y+zzz+zz)))/1200 ) ) ;
                                                                    int c=int( (abs(xxx+xx)+abs(yyy+y)+abs(zzz+zz)+rand()%20 + (f_x+f_y+f_z)/4 + ch ) / (60.0+8.0*var1+8.0*var2+8.0*var3) + 5500 )%4096;
                                                                    *hoppa=BlockInfo(95,0,c_ar[c],0);
                                                                }
                                                            } else if (!(hoppa->id==95)) {
                                                                if (dd<20.0 || dd2<20.0) {
                                                                    if (rand()%5000 < int(  30.0  +20.0*sin( (f_x+f_y+f_z)/100.07       ) + 10.0*sin( (f_x/2+f_y/2+f_z/2)/55.07       ) ) ) *hoppa=BlockInfo(89,0,0,0);
                                                                }
                                                                if (dd<21.0 || dd2<21.0) {
                                                                    if (rand()%4000 < int(  30.0  +20.0*sin( (f_x+f_y+f_z)/100.07 + 0.1 ) + 10.0*sin( (f_x/2+f_y/2+f_z/2)/55.07 + 0.1 ) ) ) *hoppa=BlockInfo(89,0,0,0);
                                                                }
                                                                if (dd<25.0 || dd2<25.0) {
                                                                    if (rand()%3000 < int(  30.0  +20.0*sin( (f_x+f_y+f_z)/100.07 + 0.2 ) + 10.0*sin( (f_x/2+f_y/2+f_z/2)/55.07 + 0.2 ) ) ) *hoppa=BlockInfo(89,0,0,0);
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

//                        }
            }
        }
    }


    for (int x = 0; x < 512; x++) {
        xx=x+chunk_offsetx*16;
        BlockInfo** AZ=AX[x];
        for (int z = 0; z < 512; z++) {
            zz=z+chunk_offsetz*16;
            BlockInfo* AY=AZ[z];
            toggle2();
            for (int y = 0; y < 256; y++) {
                if (y<3) {
                    AY[y] = BlockInfo(7, 0, 0, 0);
//                    continue;
                } else if (AY[y].id==254) {
                    AY[y]=BlockInfo(5,0,0,0);
                }
            }
        }
    }
    printf("\n");
    printf("REGION=[%d][%d]  XX=[%3d-%3d] Y=[%3d-%3d] ZZ=[%3d-%3d] ",region_x,region_z,0,511,0,255,0,255);

    printf(" ");
    first_MCEDIT=0;
    region_x_old=0;
    region_z_old=0;
    sprintf(tmp, "saves/caves/region/r.%d.%d.mca", region_x, region_z);

    if (file_exists(tmp)) {
        char cmd[200];
        sprintf(cmd,"del %s",tmp);
        while (repl_str(cmd,"/","\\"));
        system(cmd);
    }
    file_name_MCA = tmp;
    editor.setRegion(region);
    printf("Region ready, returning\n");

    return 0;
}


