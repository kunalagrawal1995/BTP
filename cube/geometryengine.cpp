/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>
#include <vector>
#include <iostream>
using namespace std;

//! [0]
GeometryEngine::GeometryEngine(QString fileName,QString type)
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry(fileName,type);
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]


void GeometryEngine::initCubeGeometry(QString fileName,QString type)
{


    vector<VertexData> vertices;
    vector<int> indices;
    load_my_obj(indices, vertices, fileName,type);
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(&vertices[0], vertices.size() * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(&indices[0], indices.size() * sizeof(int));
    indicesSize = indices.size();
    verticesSize = vertices.size();
//! [1]
}

void GeometryEngine::load_my_obj(std::vector< int > & indices, std::vector< VertexData > & vertexData, QString fileName,QString type)
{
    std::vector< QVector4D > vertices;
    std::vector< QVector4D > colors;
    QByteArray ba = fileName.toLatin1();
    cout<<ba.data()<<endl;
    QByteArray typ = type.toLatin1();
    cout<<typ.data()<<endl;
    FILE * file = fopen(ba.data(), "r");
    FILE * file_part = fopen("/home/dibyendu/Qt/Examples/Qt-5.7/opengl/cube/skeleton/partsTree.out", "r");
    int V,P=1;
    fscanf(file_part, "%d %d\n", &V,&P);
    if( file == NULL )
    {
      printf("Impossible to open the file !\n");
      return ;
    }
    int i=0;
    while(1)
    {
        if(type.toStdString()=="obj")
        {
            char lineHeader[128];
            // read the first word of the line
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF)
                break; //
            if ( strcmp( lineHeader, "v" ) == 0 )
            {
                float v1,v2,v3;
                int C=0;
                fscanf(file, "%f %f %f\n",  &v1,&v2, &v3 );
                if(fileName.toStdString()=="/home/dibyendu/Qt/Examples/Qt-5.7/opengl/build-cube-Desktop_Qt_5_7_0_GCC_64bit-Debug/scans/obj/mesh.obj")
                    fscanf(file_part, "%d \n", &C);
                QVector4D vertex(v1,v2,v3,1.0f);
                float r,g,b;
                if(C==0)
                {
                    r = 0.5;
                    g = 0;
                    b = 0;
                }
                else if(C==1)
                {
                    r = 0;
                    g = 0.5;
                    b = 0;
                }
                else if(C==2)
                {
                    r = 0;
                    g = 0;
                    b = 0.5;
                }
                else if(C==3)
                {
                    r = 1;
                    g = 0;
                    b = 0;
                }
                else if(C==4)
                {
                    r = 0;
                    g = 1;
                    b = 0;
                }
                else if(C==5)
                {
                    r = 0;
                    g = 0;
                    b = 1;
                }
                else if(C==6)
                {
                    r = 1;
                    g = 0.5;
                    b = 0;
                }
                else if(C==7)
                {
                    r = 1;
                    g = 0;
                    b = 0.5;
                }
                else if(C==8)
                {
                    r = 0;
                    g = 1;
                    b = 0.5;
                }
                else if(C==9)
                {
                    r = 0;
                    g = 0.5;
                    b = 1;
                }
                else if(C==10)
                {
                    r = 0.5;
                    g = 1;
                    b = 0;
                }
                else if(C==11)
                {
                    r = 0.5;
                    g = 0;
                    b = 1;
                }
                else if(C==12)
                {
                    r = 1;
                    g = 1;
                    b = 0;
                }
                else if(C==13)
                {
                    r = 1;
                    g = 0;
                    b = 1;
                }
                else if(C==14)
                {
                    r = 0;
                    g = 1;
                    b = 1;
                }
                else if(C==15)
                {
                    r = 1;
                    g = 1;
                    b = 1;
                }
                else if(C==16)
                {
                    r = 0.5;
                    g = 0.5;
                    b = 0.5;
                }
                else if(C==17)
                {
                    r = 0.5;
                    g = 0;
                    b = 0.5;
                }
                if(fileName.toStdString()=="/home/dibyendu/Qt/Examples/Qt-5.7/opengl/build-cube-Desktop_Qt_5_7_0_GCC_64bit-Debug/scans/obj/mesh.obj")
                {
                    QVector4D vertex_color(r,g,b,1.0f);
                    colors.push_back(vertex_color);
                }
                else
                {
                    QVector4D vertex_color(1,0,0,1);
                    colors.push_back(vertex_color);
                }
                vertices.push_back(vertex);

            }
            else if ( strcmp( lineHeader, "f" ) == 0 )
            {
                int vertexIndex[3];
                fscanf(file, "%d %d %d\n", &vertexIndex[0],  &vertexIndex[1], &vertexIndex[2] );
                indices.push_back(i++);
                indices.push_back(i++);
                indices.push_back(i++);
                vertexData.push_back({vertices[vertexIndex[0]-1],colors[vertexIndex[0]-1]});
                vertexData.push_back({vertices[vertexIndex[1]-1],colors[vertexIndex[1]-1]});
                vertexData.push_back({vertices[vertexIndex[2]-1],colors[vertexIndex[2]-1]});
            }
        }
        else if(type.toStdString()=="xyz")
        {
            float v1,v2,v3;
            int res = fscanf(file, "%f %f %f\n",  &v1,&v2, &v3 );
            if (res == EOF)
                break;
            QVector4D vertex(v1,v2,v3,1.0f);
            QVector4D vertex_color(1,0,0,1);
            vertices.push_back(vertex);
            colors.push_back(vertex_color);
            indices.push_back(i++);
            vertexData.push_back({vertex,vertex_color});

        }
    }
    fclose(file);
    fclose(file_part);
}
//! [2]
void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program,QString type)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 4, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector4D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("a_color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 4, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    if(type.toStdString()=="obj")
        glDrawArrays(GL_TRIANGLES, 0, indicesSize);
    else if(type.toStdString()=="xyz")
        glDrawArrays(GL_POINTS, 0, indicesSize);
}
//! [2]
