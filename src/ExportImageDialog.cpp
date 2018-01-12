#include "include/ExportImageDialog.h"
#include "ui_exportimagedialog.h"

ExportImageDialog::ExportImageDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ExportImageDialog){
	ui->setupUi(this);
}

ExportImageDialog::~ExportImageDialog(){
	delete ui;
}

void ExportImageDialog::exportBMP(RenderArea *renderer){
	QString f= QFileDialog::getSaveFileName(0,"Export Image",".","Images (*.bmp)");
	if(f.isNull()) return;
	if(!f.endsWith(".bmp"))
		f.append(".bmp");
	ExportImageDialog * dial= new ExportImageDialog;
	dial->ui->widthBox->setValue(renderer->width());
	dial->ui->heightBox->setValue(renderer->height());
	if(!dial->exec()) return;
	int w = dial->ui->widthBox->value();
	int h = dial->ui->heightBox->value();
	QPixmap::fromImage(renderer->renderImage(w,h)).save(f);
	delete dial;
}
