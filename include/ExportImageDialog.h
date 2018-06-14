#ifndef EXPORTIMAGEDIALOG_H
#define EXPORTIMAGEDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include "include/nodes/RenderNode.h"

namespace Ui {
class ExportImageDialog;
}

class ExportImageDialog : public QDialog{
	Q_OBJECT

public:
	explicit ExportImageDialog(QWidget *parent = 0);
	~ExportImageDialog();
	static void exportBMP(RenderNode::RenderArea *renderer);

private:
	Ui::ExportImageDialog *ui;
};

#endif // EXPORTIMAGEDIALOG_H
