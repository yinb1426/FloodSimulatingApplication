#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Project.h"
#include "PainterWidget.h"

#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp>  

#include <QMouseEvent>
#include <QResizeEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void IsStarted(bool flag);
    void PainterTypeSelected(PainterWidget::PainterType);

public slots:
    void ActionLoadTriggered();
    void ActionStartTriggered();
    void ActionPauseTriggered();
    void ActionDrawingDamTriggered();
    void ActionDrawingDrainTriggered();
    void ActivatePainterWidget(PainterWidget::PainterType type);

    void resizeEvent(QResizeEvent* event);

    void StartTimer(bool flag);
    void RunSimulation();
    void SaveDrainList(QList<QPoint> posList);

private:
    Ui::MainWindowClass ui;
    PainterWidget painterWidget;

    int currentStep = 0;
    int pixmapWidth = 0;
    int pixmapHeight = 0;

    QLabel* labelStatus = nullptr;
    QLabel* labelFPS = nullptr;
    QImage img;

    QTimer* timer = nullptr;
    QAction* actionLoad = nullptr;
    QAction* actionStart = nullptr;
    QAction* actionPause = nullptr;
    QAction* actionDrawingDrain = nullptr; 
    QAction* actionDrawingDam = nullptr;

    Project project;
    cv::Mat terrainImg = cv::Mat::zeros(1, 1, CV_8UC3);
    cv::Mat waterImg = cv::Mat::zeros(1, 1, CV_8UC3);
    cv::Mat blendedImg = cv::Mat::zeros(1, 1, CV_8UC3);
};
