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

Games tend to take certain freedoms in the way they implement physics. This is of course to make something that is better than the real world. See Lens

**Double jump** -

**Varying gravity** - 

## 5.4 LERP - Linear Interpolation

LERP is commonly used as the name of the funciton, which implements *Linear interpolation*

```javascript
function LERP (float t, Vector a, Vector b) 
{
   return (1-t)*a + t*b;
}
```


**Easing LERP** - 

**What can be interpolated?**

- Position
- Color
- rotation
- size
- shape

## 5.5 Quadratic Bezier curves

Deifinition: Interpolation between two linear interpolations

**Control points** -

**Cubic Bezier curves** -

## 5.6 SLERP - Spherical interpolation

Interpolation with rotation.