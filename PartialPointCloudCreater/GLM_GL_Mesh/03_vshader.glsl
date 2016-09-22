#version 330

in vec4 vPosition;
in vec4 vColor;
uniform int state;
out vec4 color;
uniform mat4 uModelViewMatrix;

void main (void) 
{
	//if(state == 3 || state ==4){
	//	gl_Position = uModelViewMatrix * (vPosition)*(1/vPosition.a);

	//}
	// else {
		gl_Position = uModelViewMatrix * vPosition;
	// }

		color = vColor;
}
