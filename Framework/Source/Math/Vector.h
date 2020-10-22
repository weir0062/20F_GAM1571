#pragma once

namespace fw {

class vec2
{
public:
    vec2() { x = 0; y = 0; }
    vec2(float nx, float ny) { x = nx; y = ny; }

    vec2 operator*(float o) const { return vec2( x*o, y*o ); }
    vec2 operator/(float o) const { return vec2(x / o, y / o); }
    vec2 operator+(float o) const { return vec2(x + o, y + o); }
    vec2 operator-(float o) const { return vec2(x - o, y - o); }

    vec2 operator+=(const vec2& o) { x += o.x; y += o.y; return vec2(x,y); }

    vec2 operator-=(const vec2& o) { x -= o.x; y -= o.y; return vec2(x, y); }

    vec2 operator*=(const vec2& o) { x *= o.x; y *= o.y; return vec2(x, y); }

    vec2 operator/=(const vec2& o) { x /= o.x; y /= o.y; return vec2(x, y); }
    bool operator==(const vec2& o) {if (x == o.x && y == o.y){return true;}return false;}
    bool operator!=(const vec2& o) {if (x != o.x || y != o.y){return true;}return false;}
    vec2 magnitude(vec2 vec)
    {
        x *= x;
        y *= y;
        vec = vec2(x, y);
        return vec;

    }
    vec2 Normalize(vec2 vec)
    {
        vec2 timevec = vec;
        vec2 normalize = 1.0f/ vec.magnitude;
        vec = timevec * normalize;
        return (vec);
    }

public:
    float x;
    float y;
};

class vec4
{
public:
    vec4() { x = 0; y = 0; z = 0; w = 0; }
    vec4(float nx, float ny, float nz, float nw) { x = nx; y = ny; z = nz; w = nw; }

    static const vec4 Red()      { return vec4( 1.0f, 0.0f, 0.0f, 1.0f ); }
    static const vec4 Green()    { return vec4( 0.0f, 1.0f, 0.0f, 1.0f ); }
    static const vec4 Blue()     { return vec4( 0.0f, 0.0f, 1.0f, 1.0f ); }
    static const vec4 DarkBlue() { return vec4( 0.0f, 0.0f, 0.3f, 1.0f ); }
    static const vec4 White()    { return vec4( 1.0f, 1.0f, 1.0f, 1.0f ); }
    static const vec4 Black()    { return vec4( 0.0f, 0.0f, 0.0f, 1.0f ); }

public:
    union
    {
        float x;
        float r;
    };
    union
    {
        float y;
        float g;
    };
    union
    {
        float z;
        float b;
    };
    union
    {
        float w;
        float a;
    };
};

} // namespace fw
