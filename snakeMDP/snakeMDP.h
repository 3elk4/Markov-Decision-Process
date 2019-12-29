#ifndef SNAKEMDP_H
#define SNAKEMDP_H

#include <QtWidgets/QMainWindow>
#include <QkeyEvent>
#include <QTimer>
#include "ui_snakeMDP.h"
#include <iostream>
#include <vector>
#include <utility>
#include "Pair.h"
#include "snakeMDP.h"
#include "Constants.h"
#include "PolicyIteration.h"

using namespace std;

namespace Ui {
	class snakeMDP;
}

class snakeMDP : public QMainWindow
{
	Q_OBJECT

public:
	snakeMDP(QWidget *parent = Q_NULLPTR);
	~snakeMDP();

	void paintEvent(QPaintEvent *event);

	void initFrame();
	void initEnvironment();
	Point getRandomFoodPos();
	Point getRandomHeadPos();


private:
	Ui::snakeMDPClass *ui;
	QTimer *timer = nullptr;

	MDPmodel mdp;
	map<pair<Point, Point>, action> policy;
	pair<Point, Point> snakeAndFood;
	vector<Point> frame;
	list<Point> environment;
	Point frameSize;
	Point squareSize;

private slots:
	void loop();
};

#endif //SNAKEMDP_H