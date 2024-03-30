#pragma once

#include <QMainWindow>
#include "ui_PainterWidget.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QList>

class PainterWidget : public QMainWindow
{
	Q_OBJECT

public:
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

	void SetPainterType(const PainterType type);
	PainterType GetPainterType() const;

	void SetImage(const QImage img);
	QImage GetImage() const;

	void SetLabelImage();
	void ClearPosList();

public slots:
	void ActionSaveTriggered();

signals:
	void SendDrainPosList(QList<QPoint>);

private:
	Ui::PainterWidgetClass ui;	
	QImage img;
	QSize imgSize;

	PainterType type;
	QList<QPoint> posList;

};
