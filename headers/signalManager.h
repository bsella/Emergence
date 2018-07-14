#ifndef SIGNALMANAGER_H
#define SIGNALMANAGER_H

#include <QObject>

class SignalManager: public QObject{
	Q_OBJECT
public:
	SignalManager(){}
	~SignalManager(){}
signals:
	void updateRatio();
	void updateOutputs();
};

#endif // SIGNALMANAGER_H
