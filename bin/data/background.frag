// fragment shader

#version 150

uniform vec4 globalColor;
uniform float winHeight;
out vec4 outputColor;

void main()
{
    outputColor = globalColor;
    outputColor.a = (winHeight - gl_FragCoord.y) / (winHeight / 2);
}
