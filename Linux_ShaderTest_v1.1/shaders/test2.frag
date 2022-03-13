//change these constants to get different patterns!

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

#define bend1 2.
#define c1 vec3(1.,0.5,1.5)

vec2 triangle_wave(vec2 a,float scale){
    return abs(fract((a+c1.xy)*scale)-.5);
    //return abs(fract((a+c1.xy)*scale+u_time/500.)-.5); //morphing
}

void main()
{
    gl_FragColor = vec4(0.0);
    vec3 col = vec3(0.);
    float t1 = 3.;
    vec2 uv = (gl_FragCoord-u_resolution.xy)/u_resolution.y/t1/2.0;
    uv += vec2(u_time/2.0,u_time/3.0)/t1/8.0;
    float scale = c1.z;

    vec2 t2 = vec2(0.);
        vec2 t3 = vec2(0.);   
        for(int k = 0; k < 9; k++){

            float s1 = sin(uv.x*1.23+u_time)*t2;
            float s2 = sin(uv.y)*t3;

            //uv -= (t2.yx+.5)/scale;
            uv -= (t2.yx+s2/12.5)*(bend1+uv.x+uv.y+s1/12.5);
            //uv -= (t2.yx)/(1.-uv.y-uv.x);
            
            //uv -= float(k%3)*float(k%2); //this makes it even more colorful
            
            float bend = bend1*(t2.y*bend1+1.+s1)*(t2.x*bend1-1.);

            t2 = -triangle_wave(-uv.yx-1.5,scale+s2)/bend;

            t3 = -triangle_wave(-uv,scale)*bend;
            
            uv.yx = (t3-t2)/bend1*2.;

        col.x = abs(abs((uv.x+uv.y+col.x)-1.));
        col = col.yzx;
        
        uv /= scale*scale;
      }
    gl_FragColor = vec4((col),1.0);   
}
