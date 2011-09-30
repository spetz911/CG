uniform sampler2D tex;

void main(){
    vec3 texColor = vec3(texture2D(tex, gl_TexCoord[0].st));
    gl_FragColor = vec4 ( texColor, 1.0);
}
