#version 150

uniform sampler2DRect prevPos;
uniform sampler2DRect noiseTex;

in vec2 vtexcoord;

out vec4 outColor;


uniform float a;
uniform float b;
uniform float c;
uniform float d;

uniform float noisemix;

void main()
{
    
    vec3 pos   = texture(prevPos,vtexcoord).xyz;
    vec3 noise = texture(noiseTex,vtexcoord).xyz;
    
    
    float nx = sin(a * pos.y) - pos.z * cos(b * pos.x);
    float ny = pos.z * sin(c * pos.x) - cos(d * pos.y);
    float nz = sin(pos.x);
    
    /*
    float nx = pos.x + 5 * a * d * (pos.y - pos.x);
    float ny = pos.y + d * (14 * b * pos.x - pos.y - pos.x * pos.z);
    float nz = pos.z + d * (pos.x * pos.y + c * pos.z);
    */
    
    float dst = distance(pos,vec3(nx,ny,nz));
    
    pos = vec3(nx,ny,nz);
    
    pos = mix(pos,noise,noisemix);
    
    //pos += noise*noisemix;
    
    outColor.rgba = vec4(pos,dst);

}