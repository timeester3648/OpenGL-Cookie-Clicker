#version 400 core

in vec2 position;
in vec2 textureCoords;

out vec2 pass_textureCoords;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform int numberRows;
uniform int numberColumns;
uniform vec2 offset;

void main(void) {

	gl_Position = projectionMatrix * transformationMatrix * vec4(position, -1.0, 1.0);
	pass_textureCoords = vec2(textureCoords.x / numberColumns, textureCoords.y / numberRows) + offset;

}