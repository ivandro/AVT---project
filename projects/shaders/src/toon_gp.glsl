#extension GL_EXT_geometry_shader4 : enable
/**/
uniform float triangleScale;

varying in vec3 vNormal[3];
varying out vec3 fNormal;
vec3 V[3];
vec3 CG;

void produceVertex( int v ) {
	fNormal = vNormal[v];
	gl_Position = gl_ModelViewProjectionMatrix * vec4( ((V[v] - CG) * triangleScale) + CG, 1.0 );
	EmitVertex();
}

void main() {

	V[0] = gl_PositionIn[0].xyz;
	V[1] = gl_PositionIn[1].xyz;
	V[2] = gl_PositionIn[2].xyz;
	
	CG = ( V[0] + V[1] + V[2] ) / 3.0;
	
	produceVertex( 0 );
	produceVertex( 1 );
	produceVertex( 2 );
}
/**/

/** /
// Passthrough geometry shader

varying in vec3 vNormal[3];
varying out vec3 fNormal;

void main(void)
{
	for(int i=0; i < gl_VerticesIn; i++){
		gl_Position = gl_ModelViewProjectionMatrix * gl_PositionIn[i];
		fNormal = vNormal[i];
		EmitVertex();
	}
	EndPrimitive();
}
/**/