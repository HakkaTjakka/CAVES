//#version 330

//#ifdef GL_ES
precision mediump float;
//#endif
//#extension GL_EXT_gpu_shader4 : enable

precision mediump float;
uniform sampler2D texture;
uniform int height;
uniform int yyy;
uniform int ff;
uniform int offsetx;
uniform int offsetz;
uniform int deltax;
uniform int deltaz;
uniform int deltay;
uniform int phase;

//out vec4 Fukkie;

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
//ivec2 texturesize=textureSize(texture, 0);


float hh=float(deltay*deltay);
float hh2=float((deltay-3)*(deltay-3));

const float sqrt_35=3.5*3.5;
const float sqrt_50=5.0*5.0;
const float sqrt_200=20.0*20.0;
const float tnt=254.0/255.0;

vec2 random2( vec2 p ) {
    return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}

vec2 get_color(float x_a, float z_a, float y_a) {
    float var1=1.0+0.24*sin(float(999.0+ x_a+y_a+z_a)/70.53 );
    float var2=1.0+0.24*sin(float(899.0+ x_a+y_a-z_a)/117.32 );
    float var3=1.0+0.24*sin(float(799.0+-x_a-y_a+z_a)/ 93.21 );

    var1=var1+ 0.07*sin(float( x_a+y_a+1.5*z_a)/64.53 + var3);
    var2=var2+ 0.06*sin(float( 1.5*x_a+y_a-z_a)/75.32 + var1);
    var3=var3+ 0.08*sin(float(-x_a-1.5*y_a+z_a)/53.21 + var2);

    float f_x=276.0*sin(float(x_a + z_a/2.0 + y_a +200.0)/42.79);
    float f_y=200.0*sin(float(y_a + x_a     - z_a       )/130.54);
    float f_z=236.0*sin(float(z_a + y_a     + x_a/2.0   )/65.59);

    float ch= (var1*var2*var3*75.0)*(1.0+sin( ((f_x*var1+f_y*var2+f_z*var3+f_x*var2/2.0+f_y*var3/2.0+f_z*var1/2.0)/3.0 + float(((x_a)*var2-(y_a)*var3+(z_a)*var1)))/100.0 ) );

    float r=random2(vec2(f_x,f_y+f_z)).y*20.0;
    int c=int( (abs(x_a)+abs(y_a)+abs(z_a)+ r + (f_x+f_y+f_z)/2.0 + ch ) / (40.0+8.0*var1-8.0*var2+8.0*var3) + 5500.0 );

    return random2(vec2(float(c),float(c+1)));
}

vec4 main_1() {
    ivec2 pos = ivec2(512*gl_TexCoord[0].xy);
//    ivec2 pos = ivec2(gl_FragCoord.xy);

    vec4 pixel=texelFetch(texture,pos.xy,0);

    if (pixel.a!=0) {
        if (pixel.r>=tnt) return pixel;
//        if (pixel.g==1.0) return pixel;
    }

//    vec4 color=vec4(0.0);

    int x=pos.x-deltax;
//    int z=511-pos.y-deltaz;
    int z=511-pos.y-deltaz;

    float dd2=10000.0;
    if (deltay+17-3 > 0) {
        float xxzz=float(x*x) + float(z*z);

        dd2= xxzz + hh2;
        if (dd2<=1.0) return vec4(tnt,0.0,0.0,1.0);
        else if (dd2<sqrt_35) return vec4(0.0,1.0,0.0,1.0);
        else {
            if (pixel.a==0.0) {
                float dd= xxzz + hh ;
                if (dd<sqrt_200 || dd2<sqrt_200) {
                    vec2 c=get_color(float(offsetx+deltax+x),float(offsetz+deltaz+z),float(height+deltay));
                    return vec4(c.x-1.0/255.0, c.x-1.0/255.0, c.x+1.0/255.0, 1.0);
                    return vec4(0.0,0.0,1.0,1.0);
                }
            }
        }
    }
    return pixel;
}

vec4 main_0() {
    int y=height;
//    vec2 pos = vec2(512.0*gl_TexCoord[0].xy);
    vec2 pos = vec2(gl_FragCoord.xy);

    int x=int(pos.x);
    int z=511-int(pos.y);

    int xx=x+offsetx;
    int zz=z+offsetz;

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

    vec4 color=vec4(0.0);
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
    if (hit) {
        color.r=1.0;
        color.g=0.0;
        color.a=1.0;
    }

    return color;
}

vec4 main_2() {
    int y=height;
//    vec2 pos = vec2(512.0*gl_TexCoord[0].xy);
    vec2 pos = vec2(gl_FragCoord.xy);

    int x=int(pos.x);
    int z=int(pos.y);

    int xx=x+offsetx;
    int zz=z+offsetz;

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
                   0.2*sin(float(x_a   + y_a + z_a/2) / (631.34+ 60.43*sin(float(x_a-z_a)/86.0) ))
                   ) +
                    0.1*sin(float(x_a + z_a/2 + y_a  ) / (466.79+120.48*sin(float(x_a-y_a)/145.5) ));

        f_y=250.0*(
                       sin(float(x_a +y_a/2+z_a   ) / 88.32 ) +
                   0.2*sin(float(x_a +z_a)          / (610.13+25*sin(float(x_a-y_a)/84.0) ))
                   );

        f_z=250.0*(
                       sin(float(x_a  +y_a  +z_a/2)/143.21 ) +
                   0.2*sin(float(y_a+z_a)/(730.72+37*sin(float(y_a-x_a)/95.0) ))
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
    vec4 color=vec4(0.0);
    color=vec4(0.0,0.0,0.0,0.0);
    if ( !((r3_p_a>y && r3_q_a>y && r3_r_a>y && r3_s_a>y) || (r3_p_a<y && r3_q_a<y && r3_r_a<y && r3_s_a<y)) ) {
        if ( !((r1_p_a>x && r1_q_a>x && r1_r_a>x && r1_s_a>x) || (r1_p_a<x && r1_q_a<x && r1_r_a<x && r1_s_a<x)) ) color+=vec4(.5, .0,  128.0/255.0, 1.0 );
        if ( !((r2_p_a>z && r2_q_a>z && r2_r_a>z && r2_s_a>z) || (r2_p_a<z && r2_q_a<z && r2_r_a<z && r2_s_a<z)) ) color+=vec4(.0, .9,   64.0/255.0, 1.0 );
    }
    if ( !((r3_p_b>y && r3_q_b>y && r3_r_b>y && r3_s_b>y) || (r3_p_b<y && r3_q_b<y && r3_r_b<y && r3_s_b<y)) ) {
        if ( !((r1_p_b>x && r1_q_b>x && r1_r_b>x && r1_s_b>x) || (r1_p_b<x && r1_q_b<x && r1_r_b<x && r1_s_b<x)) ) color+=vec4(.9, .5,  32.0/255.0, 1.0 );
        if ( !((r2_p_b>z && r2_q_b>z && r2_r_b>z && r2_s_b>z) || (r2_p_b<z && r2_q_b<z && r2_r_b<z && r2_s_b<z)) ) color+=vec4(.9, .0,  16.0/255.0, 1.0 );
    }


//        if ( ((r3_p_a>y && r3_q_a>y && r3_r_a>y && r3_s_a>y) || (r3_p_a<y && r3_q_a<y && r3_r_a<y && r3_s_a<y)) ) color+=vec4(0.5, 0.0,  1.0/255.0, 1.0 );
//        if ( ((r1_p_a>x && r1_q_a>x && r1_r_a>x && r1_s_a>x) || (r1_p_a<x && r1_q_a<x && r1_r_a<x && r1_s_a<x)) ) color+=vec4(0.0, 0.5,  2.0/255.0, 1.0 );
//        if ( ((r2_p_a>z && r2_q_a>z && r2_r_a>z && r2_s_a>z) || (r2_p_a<z && r2_q_a<z && r2_r_a<z && r2_s_a<z)) ) color+=vec4(0.5, 0.5,  4.0/255.0, 1.0 );
//        if ( ((r3_p_b>y && r3_q_b>y && r3_r_b>y && r3_s_b>y) || (r3_p_b<y && r3_q_b<y && r3_r_b<y && r3_s_b<y)) ) color+=vec4(1.0, 0.0,  8.0/255.0, 1.0 );
//        if ( ((r1_p_b>x && r1_q_b>x && r1_r_b>x && r1_s_b>x) || (r1_p_b<x && r1_q_b<x && r1_r_b<x && r1_s_b<x)) ) color+=vec4(0.0, 1.0, 16.0/255.0, 1.0 );
//        if ( ((r2_p_b>z && r2_q_b>z && r2_r_b>z && r2_s_b>z) || (r2_p_b<z && r2_q_b<z && r2_r_b<z && r2_s_b<z)) ) color+=vec4(1.0, 1.0, 32.0/255.0, 1.0 );

    color=min(color,1.0);

    return color;
}


vec4 main_3_a(int x, int y, int z) {
    int xx=x+offsetx;
    int zz=z+offsetz;
    vec4 color=vec4(0.0);

    for (int n=0; n<4; n++) {
        if (n==0)       { x_a=float(xx);   y_a=float(y);   z_a=float(zz);   }
        else if (n==1)  { x_a=float(xx+1); y_a=float(y);   z_a=float(zz);   }
        else if (n==2)  { x_a=float(xx);   y_a=float(y+1); z_a=float(zz);   }
        else            { x_a=float(xx);   y_a=float(y);   z_a=float(zz+1); }
        var1=1.0+0.24*sin(float(999.0+ x_a+y_a+z_a)/120.53 );
        var2=1.0+0.24*sin(float(899.0+ x_a+y_a-z_a)/117.32 );
        var3=1.0+0.24*sin(float(799.0+-x_a-y_a+z_a)/ 93.21 );

        var1=var1+ 0.02*sin(float( x_a+y_a+1.5*z_a)/64.53 );
        var2=var2+ 0.02*sin(float( 1.5*x_a+y_a-z_a)/75.32 );
        var3=var3+ 0.02*sin(float(-x_a-1.5*y_a+z_a)/53.21 );

        f_x=376.0*sin(float(x_a + z_a/2.0 + y_a   +200.0)/142.79);
        f_y=200.0*sin(float(y_a + x_a     + z_a         )/130.54);
        f_z=336.0*sin(float(z_a + y_a     + x_a/2.0     )/165.59);

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
                       sin(float(x_a/2.0 + y_a + z_a    ) / 120.53 ) +
                   0.2*sin(float(x_a     + y_a + z_a/2.0) / (631.34+ 60.43*sin(float(x_a-z_a)/86.0) ))
                   ) +
                    0.1*sin(float(x_a + z_a/2.0 + y_a  ) / (466.79+120.48*sin(float(x_a-y_a)/145.5) ));

        f_y=250.0*(
                       sin(float(x_a +y_a/2.0+z_a   ) / 88.32 ) +
                   0.2*sin(float(x_a +z_a)            / (610.13+25.0*sin(float(x_a-y_a)/84.0) ))
                   );

        f_z=250.0*(
                       sin(float(x_a  +y_a  +z_a/2.0)/143.21 ) +
                   0.2*sin(float(y_a+z_a)/(730.72+37.0*sin(float(y_a-x_a)/95.0) ))
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

//    color=vec4(0.0,0.0,0.0,0.0);
    if ( !((r3_p_a>y && r3_q_a>y && r3_r_a>y && r3_s_a>y) || (r3_p_a<y && r3_q_a<y && r3_r_a<y && r3_s_a<y)) ) {
        if ( !((r1_p_a>x && r1_q_a>x && r1_r_a>x && r1_s_a>x) || (r1_p_a<x && r1_q_a<x && r1_r_a<x && r1_s_a<x)) ) color+=vec4(.5, .0,  128.0/255.0, 1.0 );
        if ( !((r2_p_a>z && r2_q_a>z && r2_r_a>z && r2_s_a>z) || (r2_p_a<z && r2_q_a<z && r2_r_a<z && r2_s_a<z)) ) color+=vec4(.0, .9,   64.0/255.0, 1.0 );
    }
    if ( !((r3_p_b>y && r3_q_b>y && r3_r_b>y && r3_s_b>y) || (r3_p_b<y && r3_q_b<y && r3_r_b<y && r3_s_b<y)) ) {
        if ( !((r1_p_b>x && r1_q_b>x && r1_r_b>x && r1_s_b>x) || (r1_p_b<x && r1_q_b<x && r1_r_b<x && r1_s_b<x)) ) color+=vec4(.9, .5,  32.0/255.0, 1.0 );
        if ( !((r2_p_b>z && r2_q_b>z && r2_r_b>z && r2_s_b>z) || (r2_p_b<z && r2_q_b<z && r2_r_b<z && r2_s_b<z)) ) color+=vec4(.9, .0,  16.0/255.0, 1.0 );
    }


//        if ( ((r3_p_a>y && r3_q_a>y && r3_r_a>y && r3_s_a>y) || (r3_p_a<y && r3_q_a<y && r3_r_a<y && r3_s_a<y)) ) color+=vec4(0.5, 0.0,  1.0/255.0, 1.0 );
//        if ( ((r1_p_a>x && r1_q_a>x && r1_r_a>x && r1_s_a>x) || (r1_p_a<x && r1_q_a<x && r1_r_a<x && r1_s_a<x)) ) color+=vec4(0.0, 0.5,  2.0/255.0, 1.0 );
//        if ( ((r2_p_a>z && r2_q_a>z && r2_r_a>z && r2_s_a>z) || (r2_p_a<z && r2_q_a<z && r2_r_a<z && r2_s_a<z)) ) color+=vec4(0.5, 0.5,  4.0/255.0, 1.0 );
//        if ( ((r3_p_b>y && r3_q_b>y && r3_r_b>y && r3_s_b>y) || (r3_p_b<y && r3_q_b<y && r3_r_b<y && r3_s_b<y)) ) color+=vec4(1.0, 0.0,  8.0/255.0, 1.0 );
//        if ( ((r1_p_b>x && r1_q_b>x && r1_r_b>x && r1_s_b>x) || (r1_p_b<x && r1_q_b<x && r1_r_b<x && r1_s_b<x)) ) color+=vec4(0.0, 1.0, 16.0/255.0, 1.0 );
//        if ( ((r2_p_b>z && r2_q_b>z && r2_r_b>z && r2_s_b>z) || (r2_p_b<z && r2_q_b<z && r2_r_b<z && r2_s_b<z)) ) color+=vec4(1.0, 1.0, 32.0/255.0, 1.0 );

    color=min(color,1.0);

    return color;
}


vec4 main_3() {
    int y=height;
//    ivec2 pos = ivec2(512.0*gl_TexCoord[0].xy);
    ivec2 pos = ivec2(gl_FragCoord.xy);

    int x=pos.x;
    int z=511-pos.y;

    vec4 color=main_3_a(x,y,z);
    if (color.a>0.0) return color;

    for (int yyy=-18; yyy<17; yyy++) {
        int yy=yyy+y;
        if (yy>=0 && yy<256) {
            int d_y=yyy*yyy;
            for (int xxx=-18; xxx<17; xxx++) {
                int xx=xxx+x;
                if (xx>=0 && xx<512) {
                    int d_x=d_y+xxx*xxx;
                    if (d_x < 400) {
                        for (int zzz=-18; zzz<17; zzz++) {
                            int zz=zzz+z;
                            if (zz>=0 && zz<512) {
                                if ( (d_x+zzz*zzz) < 400) {
                                    color=main_3_a(xx,yy,zz);
                                    if (color.a!=0.0) {
                                        color.b+=8.0/255.0;
                                        return color;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return vec4(0.0);
//    return pixel;
}

void main() {
    if (phase==1) {
        gl_FragColor=main_1();
    } else if (phase==0)  {
        gl_FragColor=main_0();
    } else if (phase==2) {
        gl_FragColor=main_2();
    } else if (phase==3) {
        gl_FragColor=main_3();
    }
}
