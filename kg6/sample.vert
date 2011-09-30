uniform float t;
void main(){
    gl_TexCoord[0] = gl_MultiTexCoord0;
    vec4 pos;
    pos = gl_Vertex;
    pos.x = pos.x*cos(t);

    gl_Position = gl_ModelViewProjectionMatrix * pos;
}
