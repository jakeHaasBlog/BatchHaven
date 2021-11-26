#pragma once

// format is: "fff ffff f f f ff ff"
struct RenderListVertexAttribs {

	float x, y, z; // attrib name: position
	float r, g, b, a; // attrib name: color

	float thickness; // attrib name: thickness
	float type; // attrib name: type

	float textureID; // attrib name: texID
	float texX, texY; // attrib name: uvCoord;

	float centerCoordX, centerCoordY; // attrib name: centerCoord
};