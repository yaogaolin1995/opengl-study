#version 330 core

out vec4 FragColor;

in vec2 ftexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
//	vec3 finalColor = mix(vec3(texture(texture0,ftexCoord)),vec3(texture(texture1,ftexCoord)),0.5);
	FragColor = texture(texture0,ftexCoord);
};