#ifndef EXPORTIMAGEDIALOG_H
#define EXPORTIMAGEDIALOG_H

#include <QDialog>
#include "OutputNode.h"

namespace Ui {
class ExportImageDialog;
}

class ExportImageDialog : public QDialog{
	Q_OBJECT

public:
	explicit ExportImageDialog(QWidget *parent = 0);
	~ExportImageDialog();
	static void exportBMP(OutputNode *node);

private:
	Ui::ExportImageDialog *ui;
};

#endif // EXPORTIMAGEDIALOG_H
