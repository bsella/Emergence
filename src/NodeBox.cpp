#include "include/NodeBox.h"

NodeTool::NodeTool(int id,const QString& text, const QString& iconPath)
	:nodeID(id),icon(iconPath){
	setMinimumHeight(30);
	setMaximumHeight(30);
	QLabel *lbl= new QLabel("<img src=\""+iconPath+"\">  "+text,this);
	lbl->setAttribute(Qt::WA_TransparentForMouseEvents);
	setFrameShape(StyledPanel);
	setFrameShadow(Raised);
//	setAutoFillBackground(true);
//	setBackgroundRole(QPalette::Base);
}

void NodeTool::mouseMoveEvent(QMouseEvent *event){
	QDrag* drag= new QDrag(this);
	QMimeData* mime = new QMimeData;
	drag->setMimeData(mime);
	mime->setText("nodeTool");
	mime->setData("type",QByteArray::number(nodeID));
	drag->setPixmap(QPixmap::fromImage(QImage(icon)));
	drag->exec();
	QWidget::mouseMoveEvent(event);
}

NodeBox::NodeBox(QWidget *parent):QToolBox(parent){
	x=new NodeTool(X_G,"X",":/icons/x.png");
	y=new NodeTool(Y_G,"Y",":/icons/y.png");
	ratio=new NodeTool(RATIO_G,"Width/Height");
	output=new NodeTool(RENDER_G,"Output",":/icons/output.png");

	QWidget * page_Math= new QWidget;
	QWidget * page_Comp= new QWidget;
	QWidget * page_Logic= new QWidget;
	QWidget * page_Misc= new QWidget;
	QVBoxLayout *l_math= new QVBoxLayout(page_Math);
	QVBoxLayout *l_comp= new QVBoxLayout(page_Comp);
	QVBoxLayout *l_logic= new QVBoxLayout(page_Logic);
	QVBoxLayout *l_misc= new QVBoxLayout(page_Misc);

	l_math->setSpacing(1);
	l_math->setMargin(0);
	l_math->addWidget(new NodeTool(ADD_G,"Add",":/icons/add.png"));
	l_math->addWidget(new NodeTool(SUB_G,"Subtract",":/icons/subtract.png"));
	l_math->addWidget(new NodeTool(MUL_G,"Multiply",":/icons/multiply.png"));
	l_math->addWidget(new NodeTool(DIV_G,"Divide",":/icons/divide.png"));
	l_math->addWidget(new NodeTool(DOUBLE_G,"Real",":/icons/real.png"));
	l_math->addWidget(new NodeTool(CPLX_G,"Complex",":/icons/complex.png"));
	l_math->addWidget(new NodeTool(SQRT_G,"Square Root",":/icons/sqrt.png"));
	l_math->addWidget(new NodeTool(ABS_G,"Absolute Value"));
	l_math->addWidget(new NodeTool(NEG_G,"Negative",":/icons/neg.png"));
	l_math->addWidget(new NodeTool(MIN_G,"Min"));
	l_math->addWidget(new NodeTool(MAX_G,"Max"));
	l_math->addWidget(new NodeTool(SIN_G,"Sin",":/icons/sin.png"));
	l_math->addWidget(new NodeTool(COS_G,"Cos",":/icons/cos.png"));
	l_math->addWidget(new NodeTool(LERP_G,"Linear Interpolation"));
	l_math->addWidget(new NodeTool(CLAMP_G,"Clamp"));
	l_math->addItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));

	l_comp->setSpacing(1);
	l_comp->setMargin(0);
	l_comp->addWidget(new NodeTool(GT_G,"Greater",":/icons/greater_than.png"));
	l_comp->addWidget(new NodeTool(LT_G,"Less",":/icons/less_than.png"));
	l_comp->addWidget(new NodeTool(EQ_G,"Equals",":/icons/equal.png"));
	l_comp->addWidget(new NodeTool(NE_G,"Not Equal",":/icons/not_equal.png"));
	l_comp->addItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));

	l_logic->setSpacing(1);
	l_logic->setMargin(0);
	l_logic->addWidget(new NodeTool(AND_G,"AND",":/icons/and.png"));
	l_logic->addWidget(new NodeTool(OR_G,"OR",":/icons/or.png"));
	l_logic->addWidget(new NodeTool(XOR_G,"XOR",":/icons/xor.png"));
	l_logic->addWidget(new NodeTool(NOT_G,"NOT",":icons/not.png"));
	l_logic->addItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));

	l_misc->setSpacing(1);
	l_misc->setMargin(0);
	l_misc->addWidget(x);
	l_misc->addWidget(y);
	l_misc->addWidget(ratio);
	l_misc->addWidget(output);
	l_misc->addWidget(new NodeTool(IF_G,"Condition",":/icons/if.png"));
	l_misc->addWidget(new NodeTool(RGB_G,"RGB"));
	l_misc->addWidget(new NodeTool(HSV_G,"HSV"));
	l_misc->addWidget(new NodeTool(COLOR_G,"Color",":/icons/color.png"));
	l_misc->addWidget(new NodeTool(PALETTE_G,"LUT"));
	l_misc->addWidget(new NodeTool(BITMAP_G,"Image",":/icons/image.png"));
	l_misc->addItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));

	addItem(page_Math,"Math");
	addItem(page_Comp,"Comparison");
	addItem(page_Logic,"Logic");
	addItem(page_Misc,"Miscellaneous");
}
