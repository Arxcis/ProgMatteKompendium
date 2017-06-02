[TOC]

# 5. Interpolation

## 5.1 HP-bar and other examples of Linear interpolation

## 5.2 Curves

**Polynomial functions**
**Rational functions** 
**Trigonometric functions** 
**Normal distribution aka *Bell Curve*** 
**Clamp** 
**Smoothstep**
**Parametric curves** 
**Circle curve** 

## 5.3 Physics in games

Games tend to take certain freedoms in the way they implement physics. This is of course to make something that is better than the real world. See Lens[^which lens tho]

**Double jump** - [^1]

**Varying gravity** - Often, in games, you'll find (though you might not think much of it) that the player character's acceleration increases once he's reached the apex (highest point) of a jump. In game programming, this is known as *fast falling*[^1], and it's implemented because it often feels more natural.

## 5.4 LERP - Linear Interpolation

LERP is commonly used as the name of the funciton, which implements *Linear interpolation*

```javascript
function LERP (float t, Vector a, Vector b) 
{
   return (1-t)*a + t*b;
}
```

**Easing LERP** - Easing LERP is an interpolation-method that is biased by value 0 when $t<0.5f$  and biased by value 1 when $t >0.5f$.

The most common way of implementing such behaviour into a LERP-function is to modify $t$ within the function before the interpolation happens:

```javascript
function EasingLERP (float t, Vector a, Vector b)
{
   t = t * t * (3.0F - 2.0F * t); //A typical smoothStep-curve by biasing time
   return LERP(t, a, b);
}
```

Further reading on the SmoothStep formula[^2].

**What can be interpolated?**

Theoretically speaking, interpolation is possible to do with any datatypes[^citation needed]. But the cases where interpolation is most commonly used are these:

- Position
- Color
- Rotation
- Size
- Shape
- Matrices

## 5.5 Quadratic Bezier curves

Definition: Interpolation between two linear interpolations

**Control points** - 

**Cubic Bezier curves** -

## 5.6 SLERP - Spherical interpolation

Interpolation with rotation.

[^1]: Building a Better Jump - https://www.youtube.com/watch?v=hG9SzQxaCm8
[^2]: Smothstep formula - https://en.wikipedia.org/wiki/Smoothstep