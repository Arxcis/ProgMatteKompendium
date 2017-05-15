uniform vec2 resolution;
uniform float res;

//
// clamping, damping
//
/*
float min(float x, float y)
{
    if(x < y) return x;
    else return y;
}

float max(float x, float y)
{
   if(x > y) return x;
   else return y;
}

*/


//
// Interpolation
//
float lerp(float a, float b, float t)
{
    return a*(1-t)+b*t;
}

float lerp(vec2 a, vec2 b, float t)
{
    return a*(1-t)+b*t;
}

float tlerp(float a, float b, float t)
{
    float nt = t / (3.1415 / 2);
    return cos(t)*cos(t)*a+sin(t)*sin(t)*b;
}

float tlerp(vec2 a, vec2 b, float t)
{
    float nt = t / (3.1415 / 2);
    return cos(t)*cos(t)*a+sin(t)*sin(t)*b;
}

// quadratic and cubic interpolation




//
// norms and distances
//
float a1(vec2 v)
{
	return sqrt(v.x*v.x+v.y*v.y);
}

float a2(vec2 v, float n)
{
	return pow(pow(abs(v.x),n)+pow(abs(v.y),n),1/n);
}

float a3(vec2 v)
{
	return abs(v.x) + abs(v.y);
}

float d1(vec2 v, vec2 w)
{
	return a1(v-w);
}

float d2(vec2 v, vec2 w, float n)
{
	return a2(v-w,n);
}

float d3(vec2 v, vec2 w)
{
	return a3(v-w);
}


//
// hash functions
//

// On generating random numbers, with help of y= [(a+x)sin(bx)] mod 1", W.J.J. Rey,
// 22nd European Meeting of Statisticians and the
// 7th Vilnius Conference on Probability Theory and Mathematical Statistics, August 1998
// no abs!!
float h1(vec2 co)
{
    return abs(fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453));
}





/*

//
// Set theory
//
float U( float d1, float d2 )
{
    return max(d1,d2);
}

float D( float d1, float d2 )
{
    return min(d1,1-d2);
}

float I( float d1, float d2 )
{
    return min(d1,d2);
}

*/

//
// Balls
//
float ball0(vec2 p, vec2 o, float r)
{
   if(d1(p,o) < r) return 1.0;
   else return 0.0;
}


float ball1(vec2 p, vec2 o, float r)
{
    return sqrt(r*r-((p.x-o.x)*(p.x-o.x)+(p.y-o.y)*(p.y-o.y)));
}

float ball2(vec2 p, vec2 o)
{
    return cos(3.1415/2*((p.x-o.x)*(p.x-o.x)+(p.y-o.y)*(p.y-o.y)));
}

float ball3(vec2 p, vec2 o, float r)
{
    return exp(-((p.x-o.x)*(p.x-o.x)+(p.y-o.y)*(p.y-o.y))/r);
}



//
// Linear Planar deformation
//
// Scaling, rotation, reflection ...


//
// to polar and back
//
vec2 ctop(vec2 c)
{
    return vec2(atan(c.y,c.x),a1(c));
}

vec2 ptoc(vec2 p)
{
    return vec2(p.y*cos(p.x),p.y*sin(p.x));
}

//
//  Checkerboard
//
float checker(vec2 p, float  n)
{
    float v = floor(0.5*n*p.x) + floor(0.5*n*p.y);
    bool even = mod(v,2.0) == 0;
    if(even) return 1;
    else return 0;
}


//
// Colour schemes
//
vec4 greyScale(float v)
{
     return vec4(v,v,v,1.0);
}

vec4 bw(float v, float w)
{
    if(v>w) return vec4(1.0,1.0,1.0,1.0);
    else return vec4(0.0,0.0,0.0,1.0);
}


//
// heightmaps
//
float height1(vec2 pos)
{
    float alpha = 1/512.0;
    float beta = 0.5;
    float n = 0;
    for(; alpha < 1.0; alpha *= 2.0) {
        n = n + beta*h1(vec2(floor(pos.x/alpha)*alpha, floor(pos.y/alpha)*alpha));
        beta = beta / 2.0;
    }
    return n;
}


// Shadertoy
float hash( float n )
{
    return fract(sin(n)*43758.5453);
}

float height2(vec3 x)
{
    // The noise function returns a value in the range -1.0f -> 1.0f

    vec3 p = floor(x);
    vec3 f = fract(x);

    f       = f*f*(3.0-2.0*f);
    float n = p.x + p.y*57.0 + 113.0*p.z;

    return lerp(lerp(lerp( hash(n+0.0), hash(n+1.0),f.x),
                   lerp( hash(n+57.0), hash(n+58.0),f.x),f.y),
               lerp(lerp( hash(n+113.0), hash(n+114.0),f.x),
                   lerp( hash(n+170.0), hash(n+171.0),f.x),f.y),f.z);
}



//
// Description : Array and textureless GLSL 2D simplex noise function.
//      Author : Ian McEwan, Ashima Arts.
//  Maintainer : stegu
//     Lastmod : 20110822 (ijm)
//     License : Copyright (C) 2011 Ashima Arts. All rights reserved.
//               Distributed under the MIT License. See LICENSE file.
//               https://github.com/ashima/webgl-noise
//               https://github.com/stegu/webgl-noise
//

vec3 mod289(vec3 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec2 mod289(vec2 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec3 permute(vec3 x) {
  return mod289(((x*34.0)+1.0)*x);
}

float snoise(vec2 v)
  {
  const vec4 C = vec4(0.211324865405187,  // (3.0-sqrt(3.0))/6.0
                      0.366025403784439,  // 0.5*(sqrt(3.0)-1.0)
                     -0.577350269189626,  // -1.0 + 2.0 * C.x
                      0.024390243902439); // 1.0 / 41.0
// First corner
  vec2 i  = floor(v + dot(v, C.yy) );
  vec2 x0 = v -   i + dot(i, C.xx);

// Other corners
  vec2 i1;
  //i1.x = step( x0.y, x0.x ); // x0.x > x0.y ? 1.0 : 0.0
  //i1.y = 1.0 - i1.x;
  i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
  // x0 = x0 - 0.0 + 0.0 * C.xx ;
  // x1 = x0 - i1 + 1.0 * C.xx ;
  // x2 = x0 - 1.0 + 2.0 * C.xx ;
  vec4 x12 = x0.xyxy + C.xxzz;
  x12.xy -= i1;

// Permutations
  i = mod289(i); // Avoid truncation effects in permutation
  vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 ))
		+ i.x + vec3(0.0, i1.x, 1.0 ));

  vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
  m = m*m ;
  m = m*m ;

// Gradients: 41 points uniformly over a line, mapped onto a diamond.
// The ring size 17*17 = 289 is close to a multiple of 41 (41*7 = 287)

  vec3 x = 2.0 * fract(p * C.www) - 1.0;
  vec3 h = abs(x) - 0.5;
  vec3 ox = floor(x + 0.5);
  vec3 a0 = x - ox;

// Normalise gradients implicitly by scaling m
// Approximation of: m *= inversesqrt( a0*a0 + h*h );
  m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );

// Compute final noise value at P
  vec3 g;
  g.x  = a0.x  * x0.x  + h.x  * x0.y;
  g.yz = a0.yz * x12.xz + h.yz * x12.yw;
  return 130.0 * dot(m, g);
}


void main()
{
    // Normalise -1,..,1

    vec2 pos = 2*(gl_FragCoord.xy - vec2(256,256))/res;
    vec2 origin = vec2(0,0);

    // Torus
    // gl_FragColor = greyScale(D(ball0(pos,origin,1),ball0(pos,origin,0.5)));


    // Checkered ball
    //pos = ctop(pos);
    //pos.x += 3.1415/4;
    //pos = ptoc(pos);
    //gl_FragColor = greyScale(D(ball0(pos,origin,1.0),checker(pos,6)));


    // sinuoidal turbulence
    float f = 5;
    gl_FragColor = greyScale(sin(f*(pos.x+0.4*snoise(pos))));


}
