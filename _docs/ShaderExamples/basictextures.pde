PShader start;
PGraphics pg;

float t = 0;

void setup() {
  size(512,512,P2D);
  start = loadShader("shaderexample.glsl","texturevertshader.glsl");
  pg = createGraphics(512,512,P2D);
  start.set("res",512.0);
}


void draw() {
  shader(start);
  t += 0.006;
  start.set("t",t);
  background(0);
  rect(0,0,512,512);
}