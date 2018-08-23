#include "ExportImageDialog.h"
#include "ui_exportimagedialog.h"

ExportImageDialog::ExportImageDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ExportImageDialog){
	ui->setupUi(this);
}

ExportImageDialog::~ExportImageDialog(){
	delete ui;
}

void ExportImageDialog::exportBMP(OutputNode *node){
	QString f= QFileDialog::getSaveFileName(0,"Export Image",".","Images (*.bmp)");
	if(f.isNull()) return;
	if(!f.endsWith(".bmp"))
		f.append(".bmp");
	ExportImageDialog dial;
	if(!dial.exec()) return;
	int w = dial.ui->widthBox->value();
	int h = dial.ui->heightBox->value();
	QPixmap::fromImage(node->output->renderImage(w,h)).save(f);
}
