#version 330

in vec4 vColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D texSampler;

void main() {
  color = texture(texSampler, TexCoord);
}
