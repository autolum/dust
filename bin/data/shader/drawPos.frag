#version 150

uniform sampler2DRect posTex1;
uniform sampler2DRect posTex2;

uniform float alpha;
uniform float lumi;

in vec2 vtexpos;

out vec4 outColor;

void main()
{
    //float d = texture(posTex1,vtexpos).a*0.3;
    outColor = vec4(1.0,1.0,1.0,alpha);
    
}