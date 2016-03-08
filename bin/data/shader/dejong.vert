#version 150

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec2 texcoord;
out vec2 vtexcoord;

uniform float size;
uniform float mx;
uniform float my;

void main(){
    
    vtexcoord = texcoord;
    gl_Position = modelViewProjectionMatrix * position;
}