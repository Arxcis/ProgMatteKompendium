uniform mat4 transform;
uniform vec2 resolution;
uniform float res;

attribute vec4 position;

void main() {
  gl_Position = transform * position;
}
