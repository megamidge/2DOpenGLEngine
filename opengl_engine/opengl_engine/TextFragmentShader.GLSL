#version 330 core
in vec2 TexCoord;

layout(location = 0) out vec4 FragColour;
uniform vec4 colour;
uniform sampler2D text;

void main() {
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoord).r);

	vec4 final = colour*sampled;
	FragColour = final;
}