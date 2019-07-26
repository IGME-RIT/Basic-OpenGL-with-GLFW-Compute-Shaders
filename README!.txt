Documentation Author: Niko Procopi 2019

This tutorial was designed for Visual Studio 2017 / 2019
If the solution does not compile, retarget the solution
to a different version of the Windows SDK. If you do not
have any version of the Windows SDK, it can be installed
from the Visual Studio Installer Tool

Welcome to the Compute Shader Tutorial!
Prerequesite: Intro Graphics

Normally, the Graphics Pipeline works like this:
Vertex Shader -> Rasterizer -> Pixel Shader -> Screen

Now, we have the Compute Pipeline, that works like this:
Compute Shader (that's it).

What are Compute Shaders?
A Compute Shader is a raw utilization of a graphics card.
A Compute Shader is given a buffer of memory to use as input,
and an empty buffer of memory where it can write output,
and then the shader writes to the output, based on the input.

Compute shaders can be used for graphics, but they can be used
for many more things for just graphics. In this tutorial, for
a simple example, we will be using a compute shader to manipulate geomtry.
We will be using the Vertex Buffer as input, then we will alter the data,
and pass the altered data to the rasterizer. We attach the Vertex Buffer:
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, square->m_vertexBuffer);
We activate the compute shader:
	glUseProgram(computeProgram);
We give additional data to the shader if we want, (in this case, Delta Time)
	glUniform1f(0, dt);
We then run the shader multiple times, we run the shader once per each Vertex,
so we give it vertices.size() to run that many times
	glDispatchCompute(vertices.size(), 1, 1);
When we are in the compute shader, out of all the times the shader is running,
we know which time is currently being calculated (first time running, second, third...):
	gl_GlobalInvocationID.x;
Is the variable that tells us which time the shader is being run.
When I say "which time", I am not saying "what time", I am not talking about hours or minutes,
I am talking about first time, second time, third time... that the shader is running.
(Just to Clarify).

That's everything for now!

How to Improve:
Experiment! You've just learned how to use a GPU for something
that is not limited to drawing graphics, which can compute
thousands of calculations in parallel. You can run physics 
equations in parallel to simulate an ocean of particles,
(fire, explosions, dust, gas, water, ash, smoke, sparks, etc)
you can generate mipmaps for textures, you can learn intro 
Ray Tracing, you can utilize your GPU for cryptocurrency,
the possibilities are endless

