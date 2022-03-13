// Author: @patriciogv - 2015
// Title: Metaballs

#ifdef GL_ES
precision mediump float;
#endif
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2D texture;
uniform int height;
uniform int offsetx;
uniform int offsetz;

//uniform vec2 u_resolution;
//uniform vec2 u_mouse;
//uniform float u_time;

ivec2 texturesize=textureSize(texture, 0);

vec2 random2( vec2 p ) {
    return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}

vec2 offset=vec2( float(offsetx),float(offsetz) )/512.0;



float get_color(float x_a, float z_a, float y_a) {
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

    return random2(vec2(float(c),float(c+1.0)));
}

/*
bool glow_stone(float x_a, float z_a, float y_a) {
    float var1=1.0+0.24*sin(float(999.0+ x_a+y_a+z_a)/1450.53 );
    float var2=1.0+0.24*sin(float(899.0+ x_a+y_a-z_a)/1557.32 );
    float var3=1.0+0.24*sin(float(799.0+-x_a-y_a+z_a)/1466.21 );

    var1=var1+ 0.07*sin(float( x_a+y_a+1.5*z_a)/1264.53 + var3);
    var2=var2+ 0.06*sin(float( 1.5*x_a+y_a-z_a)/1375.32 + var1);
    var3=var3+ 0.08*sin(float(-x_a-1.5*y_a+z_a)/1253.21 + var2);

    float f_x=176.0*sin(float(x_a*var1 + var2*z_a/2.0 + y_a +200.0)/1442.79);
    float f_y=100.0*sin(float(y_a*var2 + var3*x_a     + z_a       )/1530.54);
    float f_z=136.0*sin(float(z_a*var3 + var1*y_a     + x_a/2.0   )/1765.59);

    float r=random2(vec2(f_x+f_y,f_z)).y*5000.0;

    if (r <  350.0 +  get_color(z_a,x_a,y_a)*100 + f_x/5.0 - f_y/6.0 + 100.0*sin( (f_x*var1+f_y*var3+f_z*var2)/787.07 + 0.2 ) + 40.0*sin( (var3*f_x/2.0+var2*f_y/2.0+f_z/2.0)/655.07 + 0.2 ) )  return true;
    return false;
}
*/

float main_0(float u_time, vec2 st) {

//    float u_time=float(height)/100.0;
//    vec2 st = ( offset + gl_TexCoord[0].xy );

//    int c=get_color(int(st.x*512.0),int(st.y*512.0),int(u_time));

    st *= 15.;

    // Tile the space

    float m_dist = 1.;  // minimum distance
    float m_color;
    float color = .0;

    for (int me=0; me<3; me++) {
        float m=sin(sin(float(me)*u_time+st.x+st.y/4.0));
        float m1=sin(sin(float(me)*u_time/3.3)+st.x/5.0+st.y/4.0);
        float m2=sin(float(me)*u_time/4.4);
        vec2 t=vec2(sin(u_time+m)/2.3+0.4*sin(u_time*1.4+m2/3.0),
                    sin(u_time*.4+m)+0.4*sin(u_time*1.5-m/5.0));
        vec2 i_st = floor(st+t+m+m2-m1);
        vec2 f_st = fract(st+t+m+m2-m1);
	    color = .0;
	    m_dist = 1.;  // minimum distance

        // Scale
        for (int j= -1; j <= 1; j++ ) {
            for (int i= -1; i <= 1; i++ ) {
                // Neighbor place in the grid
                vec2 neighbor = vec2(float(i),float(j));

                // Random position from current + neighbor place in the grid
                vec2 offset = random2(i_st + neighbor);

                // Animate the offset
                offset = vec2(0.5 + 0.5*sin(u_time + 6.2831*offset.x+m/2.0),
                             0.5 + 0.5*sin(u_time*0.84 + 6.1831*offset.y+m2/2.0));

                // Position of the cell
                vec2 pos = neighbor + offset - f_st;

                // Cell distance
                float dist = length(pos);

                // Metaball it!
                m_dist = min(m_dist, m_dist*dist);
            }
        }
	    color += step(0.35+0.10*sin(m1+m2+m), m_dist);
    }

    // Draw cells

    m_color=max(m_color,color);

    return m_color;
//    gl_FragColor = vec4(vec3(m_color),1.0);
}

void main() {
    float u_time=float(height)/300.0;
    vec2 st = ( offset + gl_TexCoord[0].xy )/2.0;

    float s1=1.0+0.25*sin(st.x/712+st.y/603+u_time/6.0)+0.25*sin(st.x/500+st.y/600+u_time/3.5);
    float s2=1.0+0.25*sin(st.x/750+st.y/633+u_time/6.0)+0.25*sin(st.x/550+st.y/733+u_time/3.7);
    float s3=1.0+0.25*sin(st.x/650+st.y/750+u_time/7.0)+0.25*sin(st.x/565+st.y/777+u_time/3.2);
    st=st*vec2(s1,s2);
    u_time=u_time*s3;

    if (main_0(u_time, st)==0.0) {
        gl_FragColor = vec4(vec3(0.0),1.0);
        return;
    }

    float r=random2(st*5.3).x*2.5;
    float m=sin(sin(u_time+st.x+st.y/3.330));
    float m1=sin(sin(u_time*1.143)+st.x/4.1423+st.y);
    float m2=sin(m1*u_time*1.232);
    vec2 t=vec2(sin(u_time+m)+0.3*sin(u_time*2.4+m2),
                sin(u_time*.4+m)+0.5*sin(u_time*2.5-m));

    if ( (get_color( st.y*1000.0 + t.y*100.0,
                   st.x*1000.0 + t.x*85.0,
                   2.0*float(height) )*25.0  < r) ||
         (get_color( (st.x+4.2)*1500.0+ t.x*t.y*85.0,
                   (st.y+4.3)*1500.0 ,
                   2.0*float(height) + t.y*45.0 )*45.0  < r)
           ) {
//    if (glow_stone(st.x*512.0,st.y*512.0,height)) {
        if (main_0(u_time+0.01, st                       )==0.0 ||
            main_0(u_time-0.01, st                       )==0.0 ||
            main_0(u_time     , st+vec2( 1.0/512.0,0.0)   )==0.0 ||
            main_0(u_time     , st+vec2(-1.0/512.0,0.0)   )==0.0 ||
            main_0(u_time     , st+vec2( 0.0, 1.0/512.0)  )==0.0 ||
            main_0(u_time     , st+vec2( 0.0,-1.0/512.0)  )==0.0 ) {
            gl_FragColor = vec4(1.0,0.0,0.0,1.0);
            return;
        }
    }
    float c=get_color(st.x*512.0,st.y*512.0,height);

    gl_FragColor = vec4(vec3(c+1.0/255.0),1.0);
}
