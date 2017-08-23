#include "backdrop.h"

Backdrop::Backdrop()
{
    initializeGLFunctions();

    shader.addShaderFromSourceFile(QGLShader::Vertex, ":/gl/gl/quad.vert");
    shader.addShaderFromSourceFile(QGLShader::Fragment, ":/gl/gl/quad.frag");
    shader.link();

//    float vbuf[] = {
//        0, 0, 0.00, 0, 0,
//        0,  1, 0, 0.21, 0.26,
//         0, 0, 10, 0.12, 0.18,
//         0,  0, 0.06, 0.26, 0.30}; //Courtesy of fstl

    float vbuf[] = { //Saved for reverting back to later: --> x,y,r,g,b
        -1, -1, 0.4, 0.4, 0.4,
        -1,  1, 0.4, 0.4, 0.4,
         1, -1, 0.5, 0.5, 0.5,
         1,  1, 0.6, 0.6, 0.6};

    vertices.create();
    vertices.bind();
    vertices.allocate(vbuf, sizeof(vbuf));
    vertices.release();
}

void Backdrop::draw()
{
    shader.bind();
    vertices.bind();

    const GLuint vp = shader.attributeLocation("vertex_position");
    const GLuint vc = shader.attributeLocation("vertex_color");

    glEnableVertexAttribArray(vp);
    glEnableVertexAttribArray(vc);


    glVertexAttribPointer(vp, 2, GL_FLOAT, false,
                          5 * sizeof(GLfloat), 0);
    glVertexAttribPointer(vc, 3, GL_FLOAT, false,
                          5 * sizeof(GLfloat),
                          (GLvoid*)(2 * sizeof(GLfloat)));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);

    vertices.release();
    shader.release();
}
