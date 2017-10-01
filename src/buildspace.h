#ifndef BUILDSPACE_H
#define BUILDSPACE_H

#include <QtOpenGL/QGLFunctions>
#include <QtOpenGL/QGLShaderProgram>
#include <QtOpenGL/QGLBuffer>


class BuildSpace : protected QGLFunctions
{
public:
    BuildSpace();
    void draw();
private:
    QGLShaderProgram shader;
    QGLBuffer buildSpaceVertices;
};

#endif // BUILDSPACE_H
