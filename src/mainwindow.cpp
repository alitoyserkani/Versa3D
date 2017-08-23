#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include "loader.h"

#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <sstream>

//TODO: dont show changing text box when file is not loaded.

const QString MainWindow::RECENT_FILE_KEY = "recentFiles";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    open_action(new QAction("Open", this)),
    about_action(new QAction("About", this)),
    quit_action(new QAction("Quit", this)),
    perspective_action(new QAction("Perspective", this)),
    orthogonal_action(new QAction("Orthographic", this)),
    reload_action(new QAction("Reload", this)),
    autoreload_action(new QAction("Autoreload", this)),
    recent_files(new QMenu("Open recent", this)),
    recent_files_group(new QActionGroup(this)),
    recent_files_clear_action(new QAction("Clear recent files", this)),
    watcher(new QFileSystemWatcher(this))
{
    ui->setupUi(this);

    setWindowTitle("3DPrint");
    setAcceptDrops(true);

    setStyleSheet("background-color: gray"); //change background to something suitable later

//    QGLFormat format;
//    format.setVersion(2, 1);
//    format.setSampleBuffers(true);

    //canvas = new Canvas(format, this);
    //setCentralWidget(canvas);

    //initialize lineEfit widget

    ui->lineEdit->setText(QString::number(ui->verticalSlider->value()));
    ui->verticalSlider->setInvertedAppearance(true);
    ui->verticalSlider->setTickInterval(5);



    QObject::connect(watcher, &QFileSystemWatcher::fileChanged,
                     this, &MainWindow::on_watched_change);

    open_action->setShortcut(QKeySequence::Open);
    QObject::connect(open_action, &QAction::triggered,
                     this, &MainWindow::on_open);

    quit_action->setShortcut(QKeySequence::Quit);
    QObject::connect(quit_action, &QAction::triggered,
                     this, &MainWindow::close);

    autoreload_action->setCheckable(true);
    autoreload_action->setChecked(true);
    autoreload_action->setEnabled(false);
    QObject::connect(autoreload_action, &QAction::triggered,
            this, &MainWindow::on_autoreload_triggered);

    reload_action->setShortcut(QKeySequence::Refresh);
    reload_action->setEnabled(false);
    QObject::connect(reload_action, &QAction::triggered,
                     this, &MainWindow::on_reload);

    QObject::connect(about_action, &QAction::triggered,
                     this, &MainWindow::on_about);

    QObject::connect(recent_files_clear_action, &QAction::triggered,
                     this, &MainWindow::on_clear_recent);
    QObject::connect(recent_files_group, &QActionGroup::triggered,
                     this, &MainWindow::on_load_recent);

    rebuild_recent_files();

    auto file_menu = menuBar()->addMenu("File");
    file_menu->addAction(open_action);
    file_menu->addMenu(recent_files);
    file_menu->addSeparator();
    file_menu->addAction(reload_action);
    file_menu->addAction(autoreload_action);
    file_menu->addAction(quit_action);

    auto view_menu = menuBar()->addMenu("View");
    auto projection_menu = view_menu->addMenu("Projection");
    projection_menu->addAction(perspective_action);
    projection_menu->addAction(orthogonal_action);
    auto projections = new QActionGroup(projection_menu);
    for (auto p : {perspective_action, orthogonal_action})
    {
        projections->addAction(p);
        p->setCheckable(true);
    }
    perspective_action->setChecked(true);
    projections->setExclusive(true);
    QObject::connect(projections, &QActionGroup::triggered,
                     this, &MainWindow::on_projection);

    auto help_menu = menuBar()->addMenu("Help");
    help_menu->addAction(about_action);

    resize(600,400);

    //change svg viewer background

}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::on_open()
{
    qDebug() << "Hey my habibi bro";
    QString filename = QFileDialog::getOpenFileName(
                this, "Load .stl file", QString(), "*.stl");
    qDebug() << "Hey my habibi";
    qDebug() << filename;
    if (!filename.isNull())
    {
        load_stl(filename);
    }
}

void MainWindow::on_about()
{
    QMessageBox::about(this, "",
        "<p align=\"center\"><b>ThreeDimension</b></p>"
        "<p>A interface for 3D printing across many machines<br>"
        "<a href=\"https://github.com/alitoyserkani"
        "   style=\"color: #93a1a1;\">https://github.com/alitoyserkani</a></p>"
        "<p>© 2017 Ali Toyserkani<br>"
        );
}

void MainWindow::on_bad_stl()
{
    QMessageBox::critical(this, "Error",
                          "<b>Error:</b><br>"
                          "This <code>.stl</code> file is invalid or corrupted.<br>"
                          "Please export it from the original source, verify, and retry.");
}

void MainWindow::on_empty_mesh()
{
    QMessageBox::critical(this, "Error",
                          "<b>Error:</b><br>"
                          "This file is syntactically correct<br>but contains no triangles.");
}

void MainWindow::on_confusing_stl()
{
    QMessageBox::warning(this, "Warning",
                         "<b>Warning:</b><br>"
                         "This <code>.stl</code> file begins with <code>solid </code>but appears to be a binary file.<br>"
                         "<code>ThreeDimension</code> loaded it, but other programs may be confused by this file.");
}

void MainWindow::on_missing_file()
{
    QMessageBox::critical(this, "Error",
                          "<b>Error:</b><br>"
                          "The target file is missing.<br>");
}

void MainWindow::enable_open()
{
    open_action->setEnabled(true);
}

void MainWindow::disable_open()
{
    open_action->setEnabled(false);
}

void MainWindow::set_watched(const QString& filename)
{
    const auto files = watcher->files();
    if (files.size())
    {
        watcher->removePaths(watcher->files());
    }
    watcher->addPath(filename);

    QSettings settings;
    auto recent = settings.value(RECENT_FILE_KEY).toStringList();
    const auto f = QFileInfo(filename).absoluteFilePath();
    recent.removeAll(f);
    recent.prepend(f);
    while (recent.size() > MAX_RECENT_FILES)
    {
        recent.pop_back();
    }
    settings.setValue(RECENT_FILE_KEY, recent);
    rebuild_recent_files();
}

void MainWindow::on_projection(QAction* proj)
{
    if (proj == perspective_action)
    {
        ui->stl_viewer->view_perspective();
    }
    else
    {
        ui->stl_viewer->view_orthographic();
    }
}

void MainWindow::on_watched_change(const QString& filename)
{
    if (autoreload_action->isChecked())
    {
        load_stl(filename, true);
    }
}

void MainWindow::on_autoreload_triggered(bool b)
{
    if (b)
    {
        on_reload();
    }
}

void MainWindow::on_clear_recent()
{
    QSettings settings;
    settings.setValue(RECENT_FILE_KEY, QStringList());
    rebuild_recent_files();
}

void MainWindow::on_load_recent(QAction* a)
{
    load_stl(a->data().toString());
}

void MainWindow::rebuild_recent_files()
{
    QSettings settings;
    QStringList files = settings.value(RECENT_FILE_KEY).toStringList();

    const auto actions = recent_files_group->actions();
    for (auto a : actions)
    {
        recent_files_group->removeAction(a);
    }
    recent_files->clear();

    for (auto f : files)
    {
        const auto a = new QAction(f, recent_files);
        a->setData(f);
        recent_files_group->addAction(a);
        recent_files->addAction(a);
    }
    if (files.size() == 0)
    {
        auto a = new QAction("No recent files", recent_files);
        recent_files->addAction(a);
        a->setEnabled(false);
    }
    recent_files->addSeparator();
    recent_files->addAction(recent_files_clear_action);
}

void MainWindow::on_reload()
{
    auto fs = watcher->files();
    if (fs.size() == 1)
    {
        load_stl(fs[0], true);
    }
}

bool MainWindow::load_stl(const QString& filename, bool is_reload)
{
    qInfo() << "Hi everyone";
    if (!open_action->isEnabled())  return false;
    ui->stl_viewer->set_status("Loading " + filename); //change to application status bar

    Loader* loader = new Loader(this, filename, is_reload);
    connect(loader, &Loader::started,
              this, &MainWindow::disable_open);
    connect(loader, &Loader::got_mesh,
            ui->stl_viewer, &Canvas::load_mesh);
    connect(loader, &Loader::error_bad_stl,
              this, &MainWindow::on_bad_stl);
    connect(loader, &Loader::error_empty_mesh,
              this, &MainWindow::on_empty_mesh);
    connect(loader, &Loader::warning_confusing_stl,
              this, &MainWindow::on_confusing_stl);
    connect(loader, &Loader::error_missing_file,
              this, &MainWindow::on_missing_file);

    connect(loader, &Loader::finished,
            loader, &Loader::deleteLater);
    connect(loader, &Loader::finished,
              this, &MainWindow::enable_open);
    connect(loader, &Loader::finished,
            ui->stl_viewer, &Canvas::clear_status);

    if (filename[0] != ':')
    {
        connect(loader, &Loader::loaded_file,
                  this, &MainWindow::setWindowTitle);
        connect(loader, &Loader::loaded_file,
                  this, &MainWindow::set_watched);
        autoreload_action->setEnabled(true);
        reload_action->setEnabled(true);
    }

    loader->start(); //begin thread for rendering stl

    //system("pwd");
    //Command line prompt for slicing the .stl file

    // TODO: See if system() can be replaced with QProcess, QProcess may be needed to track the completion of Slic3r
    //Clearing svg files after
    std::stringstream ss;
    ss << "../../../../tools/Slic3r.app/Contents/MacOS/slic3r --export-svg " << filename.toUtf8().constData() << " --output ../../../../files/SVG_Files";
    system(ss.str().c_str()); //may automatically wait for completion
    //NOTE : This need to be changed for the deployable version and stored in proper directories
    qDebug() << filename.endsWith(".stl");
    //system("../../../../tools/Slic3r.app/Contents/MacOS/slic3r --export-svg ../../../../test/CAD_tests/testSphere.stl --output ../../../../files/SVG_Files");
    ui->svg_viewer->loadData("../../../../files/SVG_Files/testEggShape.svg");
    ui->svg_viewer->currLayer = ui->lineEdit->text().toInt();
    ui->svg_viewer->update();
    ui->verticalSlider->setMaximum(ui->svg_viewer->numLayers);
    //draw layers onto svg widget



    return true;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        auto urls = event->mimeData()->urls();
        if (urls.size() == 1 && urls.front().path().endsWith(".stl"))
            event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    load_stl(event->mimeData()->urls().front().toLocalFile());
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    //TODO: Only change when stl is present -> will make interface more smooth
    //Note: be careful of starting a 0 for index
    ui->lineEdit->setText(QString::number(value));
    ui->svg_viewer->currLayer = value;
    ui->svg_viewer->update();
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    if (arg1.toInt() > 0 && arg1.toInt() <= ui->svg_viewer->numLayers) {
       ui->verticalSlider->setValue(arg1.toInt());
    } else {
        //bug: should not update that mush in real time
       ui->lineEdit->setText(QString::number(ui->verticalSlider->value()));
    }
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << ui->svg_viewer->getNumLayers();

    //TODO: don't redo algorithm if machine code has already been generated, prompt user to make sure they want to proceed


}
