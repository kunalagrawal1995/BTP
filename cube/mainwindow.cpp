/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
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

#include <QtWidgets>
#include <QMatrix4x4>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "mainwindow.h"
#include "mainwidget.h"

//! [0]
MainWindow::MainWindow()
{
//    mainWidget = new MainWidget(0);
//    setCentralWidget( mainWidget );

    CentralWidget = new MainWidget(0);
    CentralWidget->resize(512,512);
    CentralWidget->fileName = "/home/dibyendu/Qt/Examples/Qt-5.7/opengl/cube/scans/obj/test_scan_000.obj";
    CentralWidget->type = "obj";

    CamWidget1 = new MainWidget(1);
    CamWidget1->resize(128,128);
    CamWidget1->fileName = "/home/dibyendu/Qt/Examples/Qt-5.7/opengl/cube/scans/obj/test_scan_000.obj";
    CamWidget1->type = "obj";

    CamWidget2 = new MainWidget(2);
    CamWidget2->resize(128,128);
    CamWidget2->fileName = "/home/dibyendu/Qt/Examples/Qt-5.7/opengl/cube/scans/obj/test_scan_000.obj";
    CamWidget2->type = "obj";

    CamWidget3 = new MainWidget(3);
    CamWidget3->resize(128,128);
    CamWidget3->fileName = "/home/dibyendu/Qt/Examples/Qt-5.7/opengl/cube/scans/obj/test_scan_000.obj";
    CamWidget3->type = "obj";

    CamWidget4 = new MainWidget(4);
    CamWidget4->resize(128,128);
    CamWidget4->fileName = "/home/dibyendu/Qt/Examples/Qt-5.7/opengl/cube/scans/obj/test_scan_000.obj";
    CamWidget4->type = "obj";

    QWidget *widget = new QWidget;
    setCentralWidget(widget);
//! [0]

//! [1]

    QGridLayout *layout = new QGridLayout();
    layout->setMargin(5);
    layout->addWidget(CentralWidget,0,0,-1,2);
    layout->addWidget(CamWidget1,0,3,1,1);
    layout->addWidget(CamWidget2,1,3,1,1);
    layout->addWidget(CamWidget3,2,3,1,1);
    layout->addWidget(CamWidget4,3,3,1,1);
    widget->setLayout(layout);
//! [1]

//! [2]
    createActions();
    createMenus();

    setWindowTitle(tr("Render Mesh"));
    resize(1024, 1024);
}
//! [2]

void MainWindow::save_file(int i)
{
    std::ofstream scene_saver;
    std::string s;
    s = "test_scan_000_now" + std::to_string(i);
    s = s+".xyz";
    scene_saver.open(s, std::ios::out);
    int WINSIZE = 512;
    float depth;
    float x,y,z;
    for (int i = 0; i < WINSIZE; ++i)
    {
        for (int j = 0; j < WINSIZE; ++j)
        {
            glReadPixels(i,j,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&depth);
            x = (i-256)/256.0;
            y = (j-256)/256.0;
            z = 2.0*(depth-0.5);
            if(depth == 1)
            {
                continue;
            }
            else
            {
                QVector4D p;
                p = (CamWidget->view).inverted() * (CamWidget->projection).inverted() * QVector4D(x,y,z,1.0);
                scene_saver<<p[0]/p[3] <<" "<<p[1]/p[3]<<" "<<p[2]/p[3]<<std::endl;
            }
        }
    }
    std::cout<<"done. depth values calculated for camera "<<i<<std::endl;

    scene_saver.close();

}

void MainWindow::save_all()
{
    for (int i = 1; i < 5; ++i)
    {
        CamWidget = new MainWidget(i);
        CamWidget->resize(512,512);
        CamWidget->fileName = CamWidget1->fileName;
        CamWidget->type = "obj";

        // Render here
        CamWidget->show();
        save_file(i);
        delete CamWidget;
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_K)
    {
        save_all();
    }
}

void MainWindow::loadFile(const QString &fileName)
//! [42] //! [43]
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

//    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
//    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    if(CentralWidget->type.toStdString() == "obj")
        delete CamWidget4;
    delete CentralWidget;
    delete CamWidget1;
    delete CamWidget2;
    delete CamWidget3;

    CentralWidget = new MainWidget(0);
    CentralWidget->resize(512,512);
    CentralWidget->fileName = fileName;
    CentralWidget->type = "obj";

    CamWidget1 = new MainWidget(1);
    CamWidget1->resize(128,128);
    CamWidget1->fileName = fileName;
    CamWidget1->type = "obj";

    CamWidget2 = new MainWidget(2);
    CamWidget2->resize(128,128);
    CamWidget2->fileName = fileName;
    CamWidget2->type = "obj";

    CamWidget3 = new MainWidget(3);
    CamWidget3->resize(128,128);
    CamWidget3->fileName = fileName;
    CamWidget3->type = "obj";

    CamWidget4 = new MainWidget(4);
    CamWidget4->resize(128,128);
    CamWidget4->fileName = fileName;
    CamWidget4->type = "obj";

    QWidget *widget = new QWidget;
    setCentralWidget(widget);
//! [0]

//! [1]

    QGridLayout *layout = new QGridLayout();
    layout->setMargin(5);
    layout->addWidget(CentralWidget,0,0,-1,2);
    layout->addWidget(CamWidget1,0,3,1,1);
    layout->addWidget(CamWidget2,1,3,1,1);
    layout->addWidget(CamWidget3,2,3,1,1);
    layout->addWidget(CamWidget4,3,3,1,1);
    widget->setLayout(layout);
//! [1]

    setWindowTitle(tr("Render Mesh"));
    resize(1024, 1024);
}
//! [43]


void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::load()
{
    delete CentralWidget;
    delete CamWidget1;
    delete CamWidget2;
    delete CamWidget3;
    delete CamWidget4;

    CentralWidget = new MainWidget(1);
    CentralWidget->resize(512,512);
    CentralWidget->fileName = "/home/dibyendu/Qt/Examples/Qt-5.7/opengl/build-cube-Desktop_Qt_5_7_0_GCC_64bit-Debug/test_scan_000_now1.xyz";
    CentralWidget->type = "xyz";

    CamWidget1 = new MainWidget(2);
    CamWidget1->resize(512,512);
    CamWidget1->fileName = "/home/dibyendu/Qt/Examples/Qt-5.7/opengl/build-cube-Desktop_Qt_5_7_0_GCC_64bit-Debug/test_scan_000_now2.xyz";
    CamWidget1->type = "xyz";

    CamWidget2 = new MainWidget(3);
    CamWidget2->resize(512,512);
    CamWidget2->fileName = "/home/dibyendu/Qt/Examples/Qt-5.7/opengl/build-cube-Desktop_Qt_5_7_0_GCC_64bit-Debug/test_scan_000_now3.xyz";
    CamWidget2->type = "xyz";

    CamWidget3 = new MainWidget(4);
    CamWidget3->resize(512,512);
    CamWidget3->fileName = "/home/dibyendu/Qt/Examples/Qt-5.7/opengl/build-cube-Desktop_Qt_5_7_0_GCC_64bit-Debug/test_scan_000_now4.xyz";
    CamWidget3->type = "xyz";

    CamWidget4 = new MainWidget(0);
//    CamWidget4->resize(128,128);
//    CamWidget4->fileName = fileName;

    QWidget *widget = new QWidget;
    setCentralWidget(widget);
//! [0]

//! [1]

    QGridLayout *layout = new QGridLayout();
    layout->setMargin(5);
    layout->addWidget(CentralWidget,0,0,1,1);
    layout->addWidget(CamWidget1,0,1,1,1);
    layout->addWidget(CamWidget2,1,0,1,1);
    layout->addWidget(CamWidget3,1,1,1,1);
//    layout->addWidget(CamWidget4,3,3,1,1);
    widget->setLayout(layout);
//! [1]

    setWindowTitle(tr("Render Mesh"));
    resize(1024, 1024);
}

void MainWindow::save()
{
    save_all();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Menu"),
            tr("This application is developed by <b>Dibyendu Mondal</b> and <b>Kunal Agrawal</b> as a part of their <b>Computer Graphics B. Tech Project</b>."));
}

void MainWindow::aboutQt()
{
}

//! [4]
void MainWindow::createActions()
{
//! [4]

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
//! [5]

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    loadAct = new QAction(tr("&Load..."), this);
    loadAct->setShortcuts(QKeySequence::New);
    loadAct->setStatusTip(tr("Load Partial Point Clouds"));
    connect(loadAct, &QAction::triggered, this, &MainWindow::load);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);
}
//! [7]

//! [8]
void MainWindow::createMenus()
{
//! [9] //! [10]
    fileMenu = menuBar()->addMenu(tr("&File"));
//! [9]
    fileMenu->addAction(openAct);
//! [10]
    fileMenu->addAction(saveAct);
//! [11]
    fileMenu->addSeparator();
//! [11]
    fileMenu->addAction(exitAct);

    registerMenu = menuBar()->addMenu(tr("&Register"));
    registerMenu->addAction(loadAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
//! [8]

//! [12]
}
//! [12]
