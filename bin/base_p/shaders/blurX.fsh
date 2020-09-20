precision mediump float;
uniform sampler2D sampler;
varying vec4 v_color;
varying vec2 v_texcoord;

void main(void)
{
	vec3 sum = vec3(0.0);
	vec2 dx = vec2(1.0 / 1024.0, 0.0);
	vec2 tx = v_texcoord.xy - 3.0 * dx;

	for(int i = 0; i < 7; i++) {
		sum += texture2D(sampler, tx).rgb;
		tx += dx;
	}
	gl_FragColor = vec4(sum / 7.0, 1.0);
	//gl_FragColor = v_color * texture2D(sampler, v_texcoord);
}
