precision mediump float;
uniform sampler2D sampler;
varying vec4 v_color;
varying vec2 v_texcoord;

void main(void)
{
	vec3 sum = vec3(0.0);
	vec2 dy = vec2(0.0, 1.0 / 1024.0);
	vec2 ty = v_texcoord.xy - 3.0 * dy ;

	for(int i = 0; i < 7; i++) { 
		// due to target size.y = 1024
		if (ty.y > 0.75) {
			ty.y = 0.75;
		}
		sum += texture2D(sampler, ty).rgb;		
		ty += dy;
	}
	gl_FragColor = vec4(sum / 7.0, 1);
	//gl_FragColor = v_color * texture2D(sampler, v_texcoord);
}
