uniform sampler2D sampler;
varying vec4 v_color;
varying vec2 v_texcoord;
void main()
{
gl_FragColor = v_color * texture2D(sampler, v_texcoord);
}