/*
Title: Compute Shaders
File Name: compute.glsl
Copyright © 2016
Original authors: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Compute shaders are part of openGL core since version 4.3
#version 430

// A basic definition of what our vertex data looks like.
struct VertexData
{
	vec4 position;
	vec4 color;
};


// A layout describing the buffer we're accessing.
// Compute shaders don't inherently have any concept of input or output.
// Instead, they read from and write to buffers that exist on the gpu.
layout(binding = 0) buffer block
{
	VertexData data[];
} outBuffer;



 layout(location = 0) uniform float in_dt;  


// This defines the dimensions of the compute shaders local group.
// This is the smallest group of times that this compute shader will be invoked on the data set.
// Multiplying all 3 values gives us the "volume" of one operation.
// When glDispatchCompute is called, it takes in 3 values that define how many local groups to run.
// In this case, we just want to operate on one thing at a time.
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

// Declare main program function which is executed when
// glDispatchCompute is called from the application.
void main()
{
	// Get the index of this object into the buffer
	uint index = gl_GlobalInvocationID.x;

	// Create a rotation matrix for angle based on delta time.
	mat2 rotation = mat2(
		cos(in_dt), sin(in_dt),
		-sin(in_dt), cos(in_dt)
	);

	// Rotate the vertex positions.
	outBuffer.data[index].position.xy = rotation * outBuffer.data[index].position.xy;

	// Add the vertex position to it's color value.
	// This is a completely arbitrary operation. It just looks cool.
	outBuffer.data[index].color += vec4(outBuffer.data[index].position.xy, 0, 1) * in_dt;
}