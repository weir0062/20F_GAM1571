
attribute vec2 a_Position;
attribute vec2 a_UVCoord; // Input from VBO in C++.

uniform vec2 u_ObjectPos;
uniform vec2 u_UVScale;
uniform vec2 u_UVOffset;

varying vec2 v_UVCoord; // Output to frag shader.

void main()
{
    vec2 pos = a_Position;
    
    pos *= 1; // Object Scale.

    pos += u_ObjectPos;

    // Transformation from 0->10 Game world space to -1->1 clip space.
    pos /= 5.0;
    pos -= 1.0;

    v_UVCoord = a_UVCoord * u_UVScale + u_UVOffset;

    gl_Position = vec4( pos, 0, 1 );
}
