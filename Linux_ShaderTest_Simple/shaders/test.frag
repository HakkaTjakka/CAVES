uniform sampler2D texture;
//uniform float y;
uniform float blur_radius;
uniform float height;

float y=height;

void main()
{
    vec2 offx = vec2(blur_radius*2.0+0.5/512, +0.5/512.0);
    vec2 offy = vec2(+0.5/512.0, blur_radius*2.0+0.5/512.0);

    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy)               * 4.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx)        * 2.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx)        * 2.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offy)        * 2.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offy)        * 2.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx - offy) * 1.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx + offy) * 1.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx - offy) * 1.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx + offy) * 1.0;
    gl_FragColor =  (pixel / 15.9);


//    vec4 pixel=texture2D(texture, gl_TexCoord[0].xy);
//    vec4 pixel=texture2D(texture, gl_TexCoord[0].xy+vec2(0.5/512.0,0.5/512.0));

//    vec4 pixel=texelFetch(texture,ivec2(gl_FragCoord.xy),0);
//    float r=pixel.r;
//    pixel.r=pixel.g;
//    pixel.g=pixel.b;
//    pixel.b=r;
//    gl_FragColor = pixel;

//    pixel.a=(pixel.r+pixel.g+pixel.b)/3.0;
//    gl_FragColor =  pixel;
}

