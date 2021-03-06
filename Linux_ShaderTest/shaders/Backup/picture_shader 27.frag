//shader 27 FIRE RING

uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform vec2 pos_pacman;

float random (in vec2 _st) {
    return fract(sin(dot(_st.xy, vec2(12.9898,78.233))) * 43758.54531237);
}

float noise (in vec2 _st) {
    vec2 i = floor(_st);
    vec2 f = fract(_st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3. - 2.0 * f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1. - u.x) +
            (d - b) * u.x * u.y;
}

float light(in vec2 pos,in float size,in float radius,in float inner_fade,in float outer_fade){
	float len = length(pos/size);
	return pow(clamp((1.0 - pow( clamp(len-radius,0.0,1.0) , 1.0/inner_fade)),0.0,1.0),1.0/outer_fade);
}

float flare(in float angle,in float alpha,in float time){
	float t = time;
    float n = noise(vec2(t+0.5+abs(angle)+pow(alpha,0.4),t-abs(angle)+pow(alpha+0.1,0.4))*7.0);
   //	n = 1.0;
    float split = (15.0+sin(t*2.0+n*4.0+angle*10.0+alpha*1.0*n)*(.3+.5+alpha*.6*n));

    float rotate = sin(angle*20.0 + sin(angle*15.0+alpha*4.0+t*30.0+n*5.0+alpha*4.0))*(.5 + alpha*1.5);

    float g = pow((2.0+sin(split+n*1.5*alpha+rotate)*1.4)*n*4.0,n*(1.5-0.8*alpha));

    g *= alpha * alpha * alpha * .4;
	g += alpha*.7 + g * g * g;
	return g;
}

#define SIZE 2.3
#define RADIUS 0.099
#define INNER_FADE .8
#define OUTER_FADE 0.02
#define OUTER_FADE_2 0.01
#define SPEED .1
#define BORDER 0.21999

void main() {
//    vec2 uv = ((gl_FragCoord.xy - pos_pacman.xy) - iResolution.xy * 0.5)/iResolution.y;
    vec2 uv = ((gl_FragCoord.xy - pos_correction.xy) - iResolution.xy * 0.5)/iResolution.y;
	float f = .0;
    float f2 = .0;
    float t = iTime * SPEED;
	float alpha = light(uv,SIZE,RADIUS,INNER_FADE,OUTER_FADE);
	float angle = atan(uv.x,uv.y);
   // float n = noise(vec2(uv.x*100.+iTime,uv.y*100.+iTime));

	float l = length(uv);
	if(l < BORDER){
        t *= .8;
        alpha = (1. - pow(((BORDER - l)/BORDER),0.22)*0.7);
        alpha = clamp(alpha-light(uv,0.2,0.0,1.3,.7)*.55,.0,1.);
        f = flare(angle*1.0,alpha,t*.5+alpha);
        f2 = flare(angle*1.0,alpha,((t+alpha*.5+5.38134)));

	}else if(alpha < 0.001){
		f = alpha;
	}else{
		f = flare(angle,alpha,t)*1.3;
	}
	gl_FragColor = vec4(vec3(f*(1.0+sin(angle-t*4.)*.3)+f2*f2*f2,f*alpha+f2*f2*2.0,f*alpha*0.5+f2*(1.0+sin(angle+t*4.)*.3)),1.0);
}
