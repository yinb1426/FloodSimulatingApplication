#include "MainWindow.h"
#include <QActionGroup>
#include <QTimer>
#include <QMessageBox>
#include <QImage>

#include "VirtualPipelineModel.cuh"

cv::Mat GetImage(vector<double> heightMap, size_t sizeX, size_t sizeY, int type, int mapType)
{
    double maxHeight = *max_element(heightMap.begin(), heightMap.end());
    double minHeight = *min_element(heightMap.begin(), heightMap.end());
    double rangeHeight = (maxHeight - minHeight);
    vector<double> heightMapNormalized(heightMap);
    if (mapType == 0)
        for (auto& height : heightMapNormalized)
            height = (height - minHeight) / rangeHeight * 255.0;
    if (mapType == 1)
        for (auto& height : heightMapNormalized)
            height = min(height * 0.6 * 255.0, 255.0);
    cv::Mat vecForShow = cv::Mat(heightMapNormalized);
    cv::Mat matForShow = vecForShow.reshape(1, sizeY).clone();
    matForShow.convertTo(matForShow, CV_8UC3);
    cv::Mat colorImgForShow = cv::Mat::zeros(sizeY, sizeX, CV_8UC3);
    cv::applyColorMap(matForShow, colorImgForShow, type);
    return colorImgForShow;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    actionLoad = new QAction("Load", ui.mainToolBar);
    actionLoad->setCheckable(false);
    actionLoad->setChecked(false);
    ui.mainToolBar->addAction(actionLoad);

    QActionGroup* group = new QActionGroup(this);

    actionStart = new QAction("Start", ui.mainToolBar);
    actionStart->setEnabled(false);
    actionStart->setCheckable(true);
    actionStart->setChecked(false);
    group->addAction(actionStart);
    ui.mainToolBar->addAction(actionStart);

    actionPause = new QAction("Pause", ui.mainToolBar);
    actionPause->setEnabled(false);
    actionPause->setCheckable(true);
    actionPause->setChecked(false);
    group->addAction(actionPause);
    ui.mainToolBar->addAction(actionPause);    

    actionDrawingDrain = new QAction("Drawing Drain", ui.mainToolBar);
    actionDrawingDrain->setEnabled(false);
    actionDrawingDrain->setCheckable(true);
    actionDrawingDrain->setChecked(false);
    group->addAction(actionDrawingDrain);
    ui.mainToolBar->addAction(actionDrawingDrain);

    actionDrawingDam = new QAction("Drawing Dam", ui.mainToolBar);
    actionDrawingDam->setEnabled(false);
    actionDrawingDam->setCheckable(true);
    actionDrawingDam->setChecked(false);
    group->addAction(actionDrawingDam);
    ui.mainToolBar->addAction(actionDrawingDam);

    ui.labelImage->setStyleSheet("background-color: white;");
    ui.labelImage->setAlignment(Qt::AlignCenter);
    setCentralWidget(ui.labelImage);

    timer = new QTimer(this);

    labelStatus = new QLabel("", this);
    ui.statusBar->addWidget(labelStatus);
    labelFPS = new QLabel("", this);
    ui.statusBar->addPermanentWidget(labelFPS);

    connect(actionLoad, &QAction::triggered, this, &MainWindow::ActionLoadTriggered);
    connect(actionStart, &QAction::triggered, this, &MainWindow::ActionStartTriggered);
    connect(actionPause, &QAction::triggered, this, &MainWindow::ActionPauseTriggered);
    connect(actionDrawingDrain, &QAction::triggered, this, &MainWindow::ActionDrawingDrainTriggered);
    connect(actionDrawingDam, &QAction::triggered, this, &MainWindow::ActionDrawingDamTriggered);

    connect(this, SIGNAL(IsStarted(bool)), this, SLOT(StartTimer(bool)));
    connect(timer, SIGNAL(timeout()), this, SLOT(RunSimulation()));
    connect(this, SIGNAL(PainterTypeSelected(PainterWidget::PainterType)), this, SLOT(ActivatePainterWidget(PainterWidget::PainterType)));
    connect(&painterWidget, SIGNAL(SendDrainPosList(QList<QPoint>)), this, SLOT(SaveDrainList(QList<QPoint>)));
    connect(&painterWidget, SIGNAL(SendDamPosList(QList<QList<QPoint>>)), this, SLOT(SaveDamList(QList<QList<QPoint>>)));

}

void MainWindow::ActionLoadTriggered()
{
    actionLoad->setEnabled(false);
    actionStart->setEnabled(true);
    actionPause->setEnabled(true);
    actionDrawingDrain->setEnabled(true);
    actionDrawingDam->setEnabled(true);

    size_t sizeX = 1405;
    size_t sizeY = 790;
    size_t deltaX = 15;

    cv::Mat terrainHeightTif = cv::imread("resource/heightmap/FangshanTestArea.tif", cv::IMREAD_UNCHANGED);
    cv::Mat rainfallRateTif = cv::imread("resource/heightmap/RainData_0.tif", cv::IMREAD_UNCHANGED);
    cv::Mat riverDepthTif = cv::imread("resource/heightmap/RiverDepth60m.tif", cv::IMREAD_UNCHANGED);

    vector<double> terrainHeight = terrainHeightTif.reshape(1, 1);
    vector<double> rainfallRate = rainfallRateTif.reshape(1, 1);
    vector<double> riverDepth = riverDepthTif.reshape(1, 1);

    vector<double> zeros(sizeX * sizeY);
    vector<Vec3> zerosVec3(sizeX * sizeY);

    VPM fs = VPM(sizeX, sizeY, deltaX, terrainHeight, zeros, zeros, riverDepth, rainfallRate, zeros, zerosVec3);
    project = Project(std::make_shared<VPM>(fs));

    terrainImg = GetImage(fs.GetTerrainHeight(), fs.GetSizeX(), fs.GetSizeY(), cv::COLORMAP_JET, 0);
    cv::cvtColor(terrainImg, terrainImg, cv::COLOR_BGR2RGB);
    waterImg = cv::Mat::zeros(fs.GetSizeY(), fs.GetSizeX(), CV_8UC3);
    blendedImg = cv::Mat::zeros(fs.GetSizeY(), fs.GetSizeX(), CV_8UC3);

    project.Preparation();

    QMessageBox message(QMessageBox::Icon::Information, "Load Success", "Load Success!");
    message.exec();

}

void MainWindow::ActionStartTriggered()
{
    emit IsStarted(true);
}

void MainWindow::ActionPauseTriggered()
{
    emit IsStarted(false);
}

void MainWindow::ActionDrawingDamTriggered()
{
    emit PainterTypeSelected(PainterWidget::Dam);
}

void MainWindow::ActionDrawingDrainTriggered()
{
    emit PainterTypeSelected(PainterWidget::Drain);
}

void MainWindow::ActivatePainterWidget(PainterWidget::PainterType type)
{
    timer->stop();
    painterWidget.SetPainterType(type);
    painterWidget.SetImage(QImage((uchar*)terrainImg.data, terrainImg.cols, terrainImg.rows, terrainImg.cols * 3, QImage::Format_RGB888));
    painterWidget.SetLabelImage();
    painterWidget.show();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QPixmap pixmap = QPixmap::fromImage(img).scaled(ui.labelImage->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    ui.labelImage->setPixmap(pixmap);
    ui.labelImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

void MainWindow::StartTimer(bool flag)
{
    if (flag)
        timer->start(1.0 / 60.0 * 1000.0);
    else
        timer->stop();
}

void MainWindow::RunSimulation()
{    
    if (currentStep % 100 == 0)
        labelStatus->setText("Step: " + QString::number(currentStep));

    clock_t start = clock();

    project.RunSimulationOneStep(currentStep++);
    project.GetResult();

    terrainImg = GetImage(project.GetModel()->GetSurfaceHeight(), project.GetModel()->GetSizeX(), project.GetModel()->GetSizeY(), cv::COLORMAP_JET, 0);
    cv::cvtColor(terrainImg, terrainImg, cv::COLOR_BGR2RGB);
    waterImg = GetImage(project.GetWaterHeight(), project.GetModel()->GetSizeX(), project.GetModel()->GetSizeY(), cv::COLORMAP_BONE, 1);
    cv::addWeighted(terrainImg, 0.45, waterImg, 0.55, 2.8, blendedImg);
    img = QImage((uchar*)blendedImg.data, blendedImg.cols, blendedImg.rows, blendedImg.cols * 3, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(img).scaled(ui.labelImage->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    ui.labelImage->setPixmap(pixmap);
    ui.labelImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    clock_t end = clock();

    pixmapWidth = pixmap.size().width();
    pixmapHeight = pixmap.size().height();

    labelFPS->setText("FPS: " + QString::number(CLOCKS_PER_SEC / (double)(end - start), 'f', 2));
}

void MainWindow::SaveDrainList(QList<QPoint> posList)
{
    painterWidget.ClearPosList();
    painterWidget.hide();

    for (auto& p : posList)
    {
        Drain d = Drain(p.x(), p.y(), 5.0, 5.0 * project.GetModel()->GetDeltaX());
        project.AddDrain(d);
    }
    project.UpdateDrainRate();  

    QMessageBox message(QMessageBox::Icon::Information, "Drain Update Success", "Drain Update Success!");
    message.exec();
}

void MainWindow::SaveDamList(QList<QList<QPoint>> lineList)
{
    painterWidget.ClearPosList();
    painterWidget.ClearLineList();
    painterWidget.hide();
    for (auto& line : lineList)
    {
        vector<Point<double>> pList;
        for (auto& p : line)
            pList.push_back(Point<double>(p.x(), p.y()));
        Dam d = Dam(pList, 200);
        project.AddDam(d);
    }
    project.UpdateDamHeight();

    QMessageBox message(QMessageBox::Icon::Information, "Dam Update Success", "Dam Update Success!");
    message.exec();
}

MainWindow::~MainWindow()
{
    if(project.GetModel() != nullptr)
        project.Ending();
    delete timer;
    delete labelStatus;
    delete actionLoad;
    delete actionStart;
    delete actionPause;
    delete actionDrawingDrain;
}