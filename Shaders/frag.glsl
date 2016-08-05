#version 400

const int MAX_ITS = 3000;
const float PX = -0.653295281061;
const float PY = +0.350520783400;
const int paletteSize = 40;

uniform vec3 palette[paletteSize] = vec3[paletteSize](
	vec3(255,180,4),
	vec3(240,156,4),
	vec3(220,124,4),
	vec3(156,71,4),
	vec3(72,20,4),
	vec3(251,180,4),
	vec3(180,74,4),
	vec3(180,70,4),
	vec3(164,91,4),
	vec3(100,28,4),
	vec3(191,82,4),
	vec3(47,5,4),
	vec3(138,39,4),
	vec3(81,27,4),
	vec3(192,89,4),
	vec3(61,27,4),
	vec3(216,148,4),
	vec3(71,14,4),
	vec3(142,48,4),
	vec3(196,102,4),
	vec3(58,9,4),
	vec3(132,45,4),
	vec3(95,15,4),
	vec3(92,21,4),
	vec3(166,59,4),
	vec3(244,178,4),
	vec3(194,121,4),
	vec3(120,41,4),
	vec3(53,14,4),
	vec3(80,15,4),
	vec3(23,3,4),
	vec3(249,204,4),
	vec3(97,25,4),
	vec3(124,30,4),
	vec3(151,57,4),
	vec3(104,36,4),
	vec3(239,171,4),
	vec3(131,57,4),
	vec3(111,23,4),
	vec3(4,2,4)
);

uniform float m;
uniform int xRes;
uniform int yRes;
	
out vec4 colour;

int member(float cx, float cy){

	float x = 0.0;
	float y = 0.0;
	int iterations = 0;
	while ((x*x + y*y < (2*2)) && (iterations < MAX_ITS)) {
		float xtemp = x*x - y*y + cx;
		y = 2*x*y + cy;
		x = xtemp;
		iterations++;
	}

	return iterations;

}

void main () {

	float x = floor(gl_FragCoord.x);
	float y = floor(gl_FragCoord.y);

	float cx = (((float(x)/float(xRes)) -0.5 + (PX/(4.0/m)))*(4.0f/m));
	float cy = (((float(y)/float(yRes)) -0.5 + (PY/(4.0/m)))*(4.0f/m));

	int iterations = member(cx, cy);

	if (iterations < MAX_ITS) {
		int i = int(mod(iterations, 40)) - 1;
		colour = vec4(palette[i].x / 256, palette[i].y / 256, palette[i].z / 256, 0);
	} else {
		colour = vec4(0, 0, 0, 0);
	}

}