// Author: @patriciogv - 2015
// Title: Metaballs

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

vec2 random2( vec2 p ) {
    return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    vec3 color = vec3(.0);
	#define NUMBER 8
    // Scale
    st *= 2.;

    
    // Tile the space

    float m_dist = 1.;  // minimum distance
    float t_dist = 1.;  // minimum distance
    for (int me=0; me<NUMBER; me++) {

        float f_me=float(me);
        st *= 1.35;

        vec2 i_st = floor(st+f_me*1.45);
        vec2 f_st = fract(st+f_me*1.45);
        for (int j= -1; j <= 1; j++ ) {
            for (int i= -1; i <= 1; i++ ) {
                // Neighbor place in the grid
                vec2 neighbor = vec2(float(i),float(j));

                // Random position from current + neighbor place in the grid
                vec2 offset = random2(i_st + neighbor+f_me);

                // Animate the offset
                vec2 offset1 = 0.5 + 0.5*sin(u_time+f_me*3.23452 + 6.2831*offset);
                vec2 offset2 = 0.5 + 0.5*sin(u_time*.15+f_me*8.23452 + 6.2831*offset);

                offset = vec2(offset1.x,offset2.y);

                // Position of the cell
                vec2 pos = neighbor + offset - f_st;

                // Cell distance
                float dist = length(pos);
                dist=max(0.1,dist);

                // Metaball it!
                m_dist = min(m_dist, m_dist*dist);
            }
        }
//        t_dist += m_dist;
        t_dist = min(t_dist, m_dist);
        // Draw cells
        
    }
    color += step(0.000530/float(NUMBER), t_dist*float(NUMBER));

    gl_FragColor = vec4(color,1.0);
}
