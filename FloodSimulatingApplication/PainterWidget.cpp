#include "PainterWidget.h"
#include <QPainter>

PainterWidget::PainterWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	type = PainterType::Drain;

	QAction* actionReset = new QAction("Reset", this);
	actionReset->setCheckable(false);
	actionReset->setChecked(false);
	ui.mainToolBar->addAction(actionReset);

	QAction* actionSave = new QAction("Save", this);
	actionSave->setCheckable(false);
	actionSave->setChecked(false);
	ui.mainToolBar->addAction(actionSave);

	ui.labelImage->setStyleSheet("background-color: white;");
	ui.labelImage->setAlignment(Qt::AlignCenter);
	setCentralWidget(ui.labelImage);

	connect(actionReset, &QAction::triggered, this, &PainterWidget::ClearPosList);
	connect(actionReset, &QAction::triggered, this, &PainterWidget::ClearLineList);
	connect(actionSave, &QAction::triggered, this, &PainterWidget::ActionSaveTriggered);
}

void PainterWidget::mousePressEvent(QMouseEvent* event)
{
	if(GetPainterType() == PainterType::Drain)
	{
		QPoint p = event->pos();
		if (p.y() >= 0)
			posList.push_back(p);
	}
	if (GetPainterType() == PainterType::Dam)
	{
		QPoint p = event->pos();
		if (p.y() >= 0)
		{
			if (event->button() == Qt::LeftButton)
				posList.push_back(p);
			if (event->button() == Qt::RightButton)
			{
				lineList.push_back(posList);
				ClearPosList();
			}
		}
	}
	update();
}

void PainterWidget::paintEvent(QPaintEvent* event)
{
	QPixmap pixmap = QPixmap::fromImage(img).scaled(imgSize, Qt::KeepAspectRatio, Qt::FastTransformation);
	QPainter painter = QPainter(&pixmap);
	if (GetPainterType() == PainterType::Drain)
	{
		painter.setBrush(QColor(0, 0, 0));
		for (auto& p : posList)
		{
			painter.drawEllipse(p, 5, 5);
		}
	}
	if (GetPainterType() == PainterType::Dam)
	{
		painter.setBrush(QColor(25, 25, 25));
		painter.setPen(QPen(QColor(60, 60, 60), 3));

		painter.drawPolyline(posList);
		for (auto& p : posList)
			painter.drawEllipse(p, 5, 5);

		painter.setBrush(QColor(225, 225, 225));
		painter.setPen(QPen(QColor(190, 190, 190), 3));

		for (auto& line : lineList)
		{
			painter.drawPolyline(line);
			for(auto& p : line)
				painter.drawEllipse(p, 5, 5);
		}
	}
	painter.drawPixmap(0, 0, pixmap);
	ui.labelImage->setPixmap(pixmap);
}

void PainterWidget::SetPainterType(const PainterType type)
{
	this->type = type;
}

PainterWidget::PainterType PainterWidget::GetPainterType() const
{
	return this->type;
}

void PainterWidget::SetImage(const QImage img)
{
	this->img = img;
	this->imgSize = img.size();
}

QImage PainterWidget::GetImage() const
{
	return this->img;
}

void PainterWidget::SetLabelImage()
{
	QPixmap pixmap = QPixmap::fromImage(img).scaled(imgSize, Qt::KeepAspectRatio, Qt::FastTransformation);
	ui.labelImage->setPixmap(pixmap);
	setFixedSize(imgSize);
}

void PainterWidget::ClearPosList()
{
	posList.clear();
}

void PainterWidget::ClearLineList()
{
	lineList.clear();
}


void PainterWidget::ActionSaveTriggered()
{
	if (GetPainterType() == PainterType::Drain)
		emit SendDrainPosList(this->posList);
	if (GetPainterType() == PainterType::Dam)
		emit SendDamPosList(this->lineList);
}
