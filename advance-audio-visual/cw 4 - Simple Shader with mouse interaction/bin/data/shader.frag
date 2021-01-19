#version 150
//adapted from https://www.youtube.com/watch?v=vi2Ae2K1GQY
out vec4 outputColor;
uniform float mouseX;
uniform float mouseY;
uniform vec2 u_resolution;
uniform sampler2D imageTexture;

void main()
{
    float r = gl_FragCoord.x / mouseX*.6;
    float g = gl_FragCoord.y / mouseY*.2;
    float b = gl_FragCoord.x / mouseY*.5;
    float a = 1.0;
    vec2 coord = gl_FragCoord.xy/u_resolution;
    coord.y = 1.0 - coord.y;
    vec4 image = texture2D(imageTexture, coord);
    image.r += r;
    image.g += g;
    image.b += b;
    image.a += a;
    outputColor = vec4(image);

}


