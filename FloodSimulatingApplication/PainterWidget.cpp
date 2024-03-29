#include "PainterWidget.h"
#include <QPainter>

PainterWidget::PainterWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	type = PainterType::Dam;

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
	connect(actionSave, &QAction::triggered, this, &PainterWidget::ActionSaveTriggered);
}

void PainterWidget::mousePressEvent(QMouseEvent* event)
{
	QPoint p = event->pos();
	if(p.y() >= 0)
		posList.push_back(p);
	update();
}

void PainterWidget::paintEvent(QPaintEvent* event)
{
	QPixmap pixmap = QPixmap::fromImage(img).scaled(imgSize, Qt::KeepAspectRatio, Qt::FastTransformation);
	QPainter painter = QPainter(&pixmap);
	painter.setBrush(QColor(0, 0, 0));
	for (auto& p : posList)
	{
		painter.drawEllipse(p, 5, 5);
	}
	painter.drawPixmap(0, 0, pixmap);
	ui.labelImage->setPixmap(pixmap);
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

void PainterWidget::ActionSaveTriggered()
{
	emit SendDamPosList(posList);
}
