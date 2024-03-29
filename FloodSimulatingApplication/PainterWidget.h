#pragma once

#include <QMainWindow>
#include "ui_PainterWidget.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <vector>

class PainterWidget : public QMainWindow
{
	Q_OBJECT

	enum PainterType
	{
		Dam,
		Drain
	};

public:
	PainterWidget(QWidget* parent = nullptr);
	~PainterWidget() {};

public:
	void mousePressEvent(QMouseEvent* event);
	void paintEvent(QPaintEvent* event);

	void SetImage(const QImage img);
	QImage GetImage() const;
	void SetLabelImage();
	void ClearPosList();

public slots:
	void ActionSaveTriggered();

signals:
	void SendDamPosList(std::vector<QPoint>);

private:
	Ui::PainterWidgetClass ui;	
	QImage img;
	QSize imgSize;

	PainterType type;
	std::vector<QPoint> posList;

};
