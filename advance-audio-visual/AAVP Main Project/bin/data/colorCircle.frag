#version 150

// Uniforms passed to shader from openFrameworks
uniform float windowWidth;
uniform float windowHeight;
uniform vec2 mousePos;
uniform float circleRadius;

// Set outputColor as the name to use for this fragment's color
out vec4 outputColor;

// Colors to blend to at each corner of the display window
const vec3 col00 = vec3(1.0, 0.0, 0.0);
const vec3 col01 = vec3(0.0, 1.0, 0.0);
const vec3 col10 = vec3(0.0, 0.0, 1.0);
const vec3 col11 = vec3(0.0, 1.0, 1.0);

void main()
{
	// converting default mouse pos to fragment coordinates.
	vec2 mousePosInFragCoord = vec2(mousePos.x, windowHeight - mousePos.y);

	// Get the distance from the current fragment coordinate to the mouse position
	float dist = length(gl_FragCoord.xy - mousePosInFragCoord);

	// Test whether we're within circleRadius pixels of the mouse position
	if ( dist < circleRadius)
	{
		// Get multiplication factors in the range 0-1
		float factX = gl_FragCoord.x / windowWidth;
		float factY = gl_FragCoord.y / windowHeight;

		// Interpolate between corner colors to get the curent color
		vec3 mixColorA = mix(col00, col01, factX);
		vec3 mixColorB = mix(col10, col11, factX);
		vec3 curColor = mix(mixColorA, mixColorB, factY);

		// Set the RGB values of this fragment color to curColor
		outputColor.rgb = curColor;
	}
	else 
	{
		// Set the RGB values of this fragment color to black
		outputColor.rgb = vec3(0);
	}

	// Set the alpha value of this fragment color to 1
	outputColor.a = 1.0;
}
