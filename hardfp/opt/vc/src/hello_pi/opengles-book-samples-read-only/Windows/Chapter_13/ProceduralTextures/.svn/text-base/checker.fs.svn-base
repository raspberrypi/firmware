#ifdef GL_ES
precision highp float;
#endif

uniform int     frequency;
uniform vec4    color0;
uniform vec4    color1;

varying vec2    v_st;

void
main()
{
    float   s, t, delta;
    
    s = mod(floor(v_st.x * float(frequency * 2)), 2.0);
    t = mod(floor(v_st.y * float(frequency * 2)), 2.0);    
    delta = abs(s - t);
    
    gl_FragColor = mix(color1, color0, delta);
}
