precision mediump float;
uniform sampler2D sampler;
varying vec4 v_color;
varying vec2 v_texcoord;
uniform float t;
uniform vec2 u_resolution;
#define HALF_PI 1.5707963267948966
#define PI 3.14159265359
#define TWO_PI 6.28318530718
#define DW 0.09

vec3 colorRed = vec3(1.0, 0.0, 0.0);
vec3 colorOrange = vec3(1.0, 128.0/255.0, 0);
vec3 colorYellow = vec3 (1.0, 1.0, 0.0);
vec3 colorGreen	= vec3(0.0, 1.0, 0.0);
vec3 colorBlue = vec3(0.0, 191.0/255.0, 1.0);
vec3 colorDarkBlue = vec3(0, 77.0/255.0, 1.0);
vec3 colorViolet = vec3(90.0/255.0, 0, 157.0/255.0);
vec3 colorBlack = vec3(0.0, 0.0, 0.0);
vec3 colorWhite = vec3(1.0, 1.0, 1.0);

float plot(vec2 st, float y) {    
    return smoothstep(st.y - 0.02, st.y, y) - smoothstep(st.y, st.y + 0.02, y);
}

mat2 rotate2d(float _angle){
    return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}

mat2 scale2d(vec2 _scale){
    return mat2(_scale.x,0.0,
                0.0,_scale.y);
}

vec3 filledRect(in vec2 st, in vec2 bottomLeft, in vec2 topRight) {   
    return vec3(step(bottomLeft.x, st.x) * step(bottomLeft.y, st.y) * (1.0 - step(topRight.x, st.x)) * (1.0 - step(topRight.y, st.y)));
}

vec3 segment3(in float x, in float y, in float r, in vec2 st) {
   vec2 p = st - vec2(x, y);
   if (p.x < 0.0 && p.y < 0.0 && length(p) < r) {
      float a = atan(p.y, p.x);
      float v = smoothstep(-PI, -PI/1.8, a);  
      //float v = (1.0 + a / PI) / 0.1;
      return vec3(1.0-v);
   } else {
        return colorBlack;
   }
}

vec3 circleOutline(in float x, in float y, in float r, in vec2 st, vec3 color) { 
   float len =  length(st - vec2(x, y));
   return color * vec3(1.0 - step(r, len)) * vec3(step(r - 0.003 , len));
}
 
vec3 circleOutlineDivided(in float x, in float y, in float r, in vec2 st, vec3 color, in float t) { 
   vec2 p = st - vec2(x, y);
   float a = atan(p.y, p.x);
   float len = length (p);
   vec3 c;
   float d = 0.5 + 0.3 * sin(t);
   if (length(p) < r) {
      if (abs(a) > PI - d) {
         c =  colorBlack;
      } else {
         c =  vec3(1.0 - step(r, len)) * vec3(step(r - 0.003 , len));
      }
   } else {
      c =  colorBlack;
   }
   vec3 c1;
   if (length(p) < r) {
      if (abs(a) < d) {
         c1 =  colorBlack;
      } else {
         c1 =  vec3(1.0 - step(r, len)) * vec3(step(r - 0.003 , len));
      }
   } else {
      c1 =  colorBlack;
   }
   return color * c * c1;
}

vec3 circleWithBordSmooth(in float x, in float y, in float r0, in vec2 st, vec3 color, in float t) { 
   float r = r0/4.0 + r0 * fract(t);
   float w = r - r/1.4;
   vec2 p = st - vec2(x, y);   
   float len = length(p);
   if ( len > r) {
      return colorBlack;
   } else { 
        float v = smoothstep(r - w, r, len);  
        return color * vec3(v);
       // return vec3(v);

   }
}
 
vec3 targetPulsing(in float x, in float y, in float r0, in vec2 st, vec3 color, in float t) {
    vec3 smoothBord = circleWithBordSmooth(x, y, r0, st, color, t);
    vec3 bord =  circleOutline(x, y, r0 / 4.0, st, color);
    vec3 core;
    if (sin(15.0 * t) > 0.0) {
        core = color * vec3(1.0 - step(r0 - r0/1.3, length (st - vec2(x, y)) * 2.0));
    } else {
        core = colorBlack;
    }
    return core + smoothBord + bord;
}


vec3 radar(in vec2 st, in float t) {
   vec2 center = vec2(0.5, 0.5);
   st -= center;
   st = rotate2d(-t)  * st;
   st += center;
   vec3 segment = colorBlue * segment3(0.5, 0.5, 0.45, st);
   st -= center;
   st = rotate2d(t)  * st;
   st += center;
   vec3 circles = circleOutline(0.5, 0.5, 0.6, st, colorBlue) + circleOutline(0.5, 0.5, 0.45, st, colorWhite)
                + circleOutline(0.5, 0.5, 0.3, st, colorBlue) + circleOutline(0.5, 0.5, 0.15, st, colorBlue)
                + circleOutline(0.5, 0.5, 0.02, st, colorBlue);
   vec3 circleDivided = circleOutlineDivided(0.5, 0.5, 0.5, st, colorYellow, t);
   return circles + segment + circleDivided;
}

void main() {
   vec2 st = gl_FragCoord.xy/vec2(768, 768) - vec2(0.17, 0);
   vec3 rad = radar(st, t);
   vec3 targets = targetPulsing(0.4, 0.4, 0.05, st, colorOrange, t);
   vec3 color =  targets + rad;
// vec3 color = mix(rad, colorOrange, targets);
   gl_FragColor = vec4(color, 1.0);
}
