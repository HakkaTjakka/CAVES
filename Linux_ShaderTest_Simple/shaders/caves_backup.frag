//#version 130
//precision highp float;
//precision mediump float;

uniform sampler2D texture;
//uniform float height;
uniform int height;
uniform int chunk_offsetx;
uniform int chunk_offsetz;
uniform int phase;
//uniform int centre;

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
ivec2 texturesize=textureSize(texture, 0);

/*
float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
	return 1.-smoothstep(_radius-(_radius*0.1),
                         _radius+(_radius*0.1),
                         dot(dist,dist)*4.0);
}
*/

/*
float r1=0.2*sin(test123+sin(test123*1.33+sin(test123*1.55+sin(test123*1.66))));
float r2=0.2*sin(test123*1.1+sin(test123*1.53+sin(test123*1.75+sin(test123*1.86))));
vec2 r=vec2(r1,r2);

void main2(){
//	vec2 st = gl_FragCoord.xy/u_resolution.xy;
	vec2 st = vec2(gl_TexCoord[0].xy);


//	vec3 color = vec3(circle(st,0.02));
	vec3 color = vec3(circle(st+r+vec2(0.05,0.05),0.02),circle(st+r+vec2(0.05,-0.05),0.02),circle(st+r,0.02));

	gl_FragColor = vec4( color, 1.0 );
    gl_FragColor.a=(gl_FragColor.r+gl_FragColor.g+gl_FragColor.b)/3.0;

}

*/

float hh=float(height*height);
float hh2=float((height-3)*(height-3));

vec4 main_1() {
    vec4 color=vec4(0.0);

//    vec2 pos = vec2(35.0*gl_TexCoord[0].xy-vec2(0.5,0.5));
//    vec2 pos = vec2(35.0*gl_TexCoord[0].xy-vec2(0.5,0.5));
//    vec2 pos = vec2(35.0*gl_TexCoord[0].xy);

//    vec2 pos = vec2(512*gl_TexCoord[0].xy);
    ivec2 pos = ivec2(512*gl_TexCoord[0].xy);

//    ivec2 pos = ivec2(512*gl_TexCoord[0].xy);
//    vec2 pos = (gl_FragCoord.xy)-vec2(0.5,0.5);

//    vec4 pixel=texelFetch(texture,ivec2(gl_TexCoord[0].xy*512),0);
    vec4 pixel=texelFetch(texture,pos.xy,0);

//    vec4 pixel=texelFetch(texture,ivec2(gl_TexCoord[0].xy*35),0);
//    vec2 pos = (gl_FragCoord.xy)-vec2(0.5,0.5);
//    vec2 pos = (gl_FragCoord.xy)-vec2(0.5,0.5);

//    int x=int(pos.x)-17;
//    int z=int(pos.y)-17;

    int x=pos.x-chunk_offsetx;
    int z=511-pos.y-chunk_offsetz;

//    int z=int(pos.y)-chunk_offsetz;
//    int z=int(pos.y)-chunk_offsetz;

//    if (x==chunk_offsetx && z==chunk_offsetz && height==0) return vec4(0.0,1.0,0.0,1.0);
//    if (x==0 && z==0 && height==0) return vec4(0.0,1.0,0.0,1.0);
//    else return vec4(0.0,0.0,0.0,0.0);
//    int x=int(pos.x)-chunk_offsetx-17;
//    int z=17-(int(pos.y)-chunk_offsetz);

//    int z=int(pos.y)-chunk_offsetz-17;

    if (pixel.a>0) {
//        return vec4(1.0,1.0,1.0,1.0);
        if (pixel.r==1.0 || pixel.g==1.0) {
//            pixel.g=1.0;
//            pixel.g=1.0;
            return pixel;
        }
    }


//    return color;



/*
    if (x==-17) {
        return vec4(0.8,0.0,0.0,0.5);
    } else if (x==17) {
        return vec4(0.0,0.8,0.0,0.5);
    } else if (z==-17) {
        return vec4(0.0,0.0,0.8,0.5);
    } else if (z==17) {
        return vec4(0.0,0.8,0.8,0.5);
    } else {
//        return vec4(float(x)/511.0,float(z)/511.0,float(y)/255,0.5);
//        return vec4(0.01,0.0,0.0,0.01);
        return vec4(0.0,0.0,0.0,0.0);
    }
*/

//    float s=sqrt(float(x*x)+float(z*z)+float(height*height));


    float dd2=10000.0;
//    if (height+17-3 > 0) {
//    if (height+17-3 > 0) {
    if (height+17-3 > 0) {
        float xxzz=float(x*x) + float(z*z);

        dd2=sqrt( xxzz + hh2 );
//        float dd=sqrt( float(x*x) + float(z*z) + float((height)*(height)) );
//        dd2=sqrt( float(x*x) + float(z*z) + float((height-3)*(height-3)) );
//        dd2=sqrt( float(x*x) + float(z*z) + float((height)*(height)) );
        if ( dd2<=1.0) {
            color.g=1.0;
            color.a=1.0;
            return color;
        } else if (dd2<3.5) {
            color.g=0.5;
            color.b=0.0;
            color.a=1.00;
            return color;
        } else {
            if (pixel.g==0.0 && pixel.b==0.0) {
                float dd=sqrt( xxzz + hh );
                if (dd<20.0 || dd2<20 ) {
                    color.b=0.5;
                    color.a=1.0;
                    return color;
                }
            }
        }
    }


//    color.g=1.0;
//    color.a=0.1;
    return pixel;
}

vec4 main_0() {
    int y=height;

//    vec4 pixel=texelFetch(texture,ivec2(gl_TexCoord[0].xy*texturesize),0);

//    vec2 pos = (gl_FragCoord.xy)-vec2(0.5,0.5);

//    vec2 pos = vec2(512.0*gl_TexCoord[0].xy-vec2(0.5,0.5));
    vec2 pos = vec2(512.0*gl_TexCoord[0].xy);

    int x=int(pos.x);
    int z=int(pos.y);
//    int z=511-int(pos.y);

/*
//    if (pos.x==0.0) {
    if (x==0) {
//    if (x==0 || x==511 || z==0 || z==511) {
        return vec4(0.8,0.0,0.0,0.5);
//    } else if (pos.x==511.0) {
    } else if (x==511) {
        return vec4(0.0,0.8,0.0,0.5);
//    } else if (pos.y==0.0) {
    } else if (z==0) {
        return vec4(0.0,0.0,0.8,0.5);
//    } else if (pos.y==511.0) {
    } else if (z==511) {
        return vec4(0.0,0.8,0.8,0.5);
    } else {
//        return vec4(float(x)/511.0,float(z)/511.0,float(y)/255,0.5);
//        return vec4(0.01,0.0,0.0,0.01);
        return vec4(0.0,0.0,0.0,0.0);
    }
*/

    int xx=x+chunk_offsetx*16;
    int zz=z+chunk_offsetz*16;

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

    vec4 color;

    if (hit) {
        color.r=1.0;
        color.a=1.0;
//        color.g=(0.25+float(y)/192.0);
    } else {
        color=vec4(0.0);
    }

    return color;

/*
	vec2 st = vec2(gl_TexCoord[0].x,var1-0.5);
	vec4 color1 = vec4(circle(st,0.005)-circle(st,0.001)); color1.x=0; color1.y=0;

	st = vec2(gl_TexCoord[0].x,var2-0.5);
	vec4 color2 = vec4(circle(st,0.005)-circle(st,0.001)); color2.x=0; color2.z=0;

	st = vec2(gl_TexCoord[0].x,var3-0.5);
	vec4 color3 = vec4(circle(st,0.005)-circle(st,0.001)); color3.y=0; color3.z=0;

	gl_FragColor=color1+color2+color3;
	gl_FragColor.a=gl_FragColor.a/2.0;
*/

//    gl_FragColor.r=gl_TexCoord[0].x;
//    gl_FragColor.g=gl_TexCoord[0].y;
//    gl_FragColor.a=1.0;
//    gl_FragColor.a=(gl_FragColor.r+gl_FragColor.g+gl_FragColor.b)/3.0;
}


void main() {
    if (phase==0) {
        gl_FragColor=main_0();
    } else {
        gl_FragColor=main_1();
    }
}




void main1() {

    vec4 pixel=texture2D(texture, gl_TexCoord[0].xy+vec2(0.5/512.0,0.5/512.0));
//    vec4 pixel=texture2D(texture, gl_TexCoord[0].xy);

    pixel.a=(pixel.r+pixel.g+pixel.b)/3.0;
    gl_FragColor =  pixel;
}

