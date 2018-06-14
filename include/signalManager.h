#ifndef SIGNALMANAGER_H
#define SIGNALMANAGER_H

#include <QObject>

class SignalManager: public QObject{
	Q_OBJECT
public:
	SignalManager(QObject* parent=0);
	~SignalManager();
signals:
	void updateXY();
	void updateRatio();
};

#endif // SIGNALMANAGER_H
