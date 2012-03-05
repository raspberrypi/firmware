
uniform mat4    mvp_matrix;

attribute vec4  a_position;
attribute vec2  a_st;

varying vec2    v_st;

void
main()
{
    v_st = a_st;
    gl_Position = mvp_matrix * a_position;
}
