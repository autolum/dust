#version 150

uniform sampler2DRect posTex1;
uniform sampler2DRect posTex2;

uniform vec2 screen;

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
out vec2 vtexpos;

void main(){
    
    vec3 pixPos = texture(posTex1,position.xy).xyz;
    //vec3 pixPos2 = texture(posTex2,position.xy).xyz;
    
    //pixPos -= 0.5;
    //pixPos *= 512;
    
    //vec4 p = vec4(normalize(pixPos) * 128,1.0);
    vec4 p = vec4((pixPos) * 16,1.0);
    
    vtexpos = position.xy;
    
    gl_Position = modelViewProjectionMatrix * p;
}