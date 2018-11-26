#version 400 core

in vec2 pass_textureCoords;
out vec4 out_Color;

uniform sampler2D textureSampler;
uniform float doMixColor;
uniform float mixColorIntensity;
uniform vec4 colorMix;
uniform float iconLocked;

void main(void) {

	out_Color = texture(textureSampler, pass_textureCoords);

	if (doMixColor > 0.5) {

		out_Color = mix(out_Color, colorMix, mixColorIntensity);

	}

	if (iconLocked > 0.5) {

		out_Color = vec4(0, 0, 0, out_Color.a);

	}

}