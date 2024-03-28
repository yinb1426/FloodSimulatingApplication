#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Project.h"

#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp>  

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void IsStarted(bool flag);

public slots:
    void ActionLoadTriggered();
    void ActionStartTriggered();
    void ActionPauseTriggered();
    void StartTimer(bool flag);
    void RunSimulation();

private:
    Ui::MainWindowClass ui;
    int currentStep = 0;
    QLabel* labelStatus = nullptr;
    QTimer* timer = nullptr;
    Project project;

    QAction* actionLoad = nullptr;
    QAction* actionStart = nullptr;
    QAction* actionPause = nullptr;

    cv::Mat terrainImg = cv::Mat::zeros(1, 1, CV_8UC3);
    cv::Mat waterImg = cv::Mat::zeros(1, 1, CV_8UC3);
    cv::Mat blendedImg = cv::Mat::zeros(1, 1, CV_8UC3);
};
