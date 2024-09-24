#version 330 core

layout ( location = 0 ) in vec3 aPos;
//layout ( location = 1 ) in vec3 aColor;
layout ( location = 1 ) in vec2 atexCoord;
//layout ( location = 3 ) in vec2 testtexCoord;

out vec3 fColor;
out vec2 ftexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	ftexCoord = atexCoord;
//	fColor = aColor;
	gl_Position = projection * view * model * vec4(aPos.x,aPos.y,aPos.z,1.0);
};