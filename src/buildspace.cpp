#include "buildspace.h"

BuildSpace::BuildSpace()
{
    initializeGLFunctions();

    shader.addShaderFromSourceFile(QGLShader::Vertex, ":/gl/gl/buildspace.vert");
    shader.addShaderFromSourceFile(QGLShader::Fragment, ":/gl/gl/buildspace.frag");
    shader.link();


}

void BuildSpace::draw()
{

}
