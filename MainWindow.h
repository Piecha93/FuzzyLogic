#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "fl/headers.h"

using namespace fl;

namespace Ui {
class MainWindow;
}

static const QString rules[] {
    "if Age is YOUNG and Weight is SUPERLIGHT and Amount is LITTLE then DrunkLevel is DRUNK",
    "if Age is YOUNG and Weight is SUPERLIGHT and Amount is MEAN then DrunkLevel is WASTED",
    "if Age is YOUNG and Weight is SUPERLIGHT and Amount is ALOT then DrunkLevel is WASTED",

    "if Age is YOUNG and Weight is LIGHT and Amount is LITTLE then DrunkLevel is TIPSY",
    "if Age is YOUNG and Weight is LIGHT and Amount is MEAN then DrunkLevel is DRUNK",
    "if Age is YOUNG and Weight is LIGHT and Amount is ALOT then DrunkLevel is WASTED",

    "if Age is YOUNG and Weight is AVERAGE and Amount is LITTLE then DrunkLevel is TIPSY",
    "if Age is YOUNG and Weight is AVERAGE and Amount is MEAN then DrunkLevel is DRUNK",
    "if Age is YOUNG and Weight is AVERAGE and Amount is ALOT then DrunkLevel is WASTED",

    "if Age is YOUNG and Weight is FAT and Amount is LITTLE then DrunkLevel is SOBER",
    "if Age is YOUNG and Weight is FAT and Amount is MEAN then DrunkLevel is TIPSY",
    "if Age is YOUNG and Weight is FAT and Amount is ALOT then DrunkLevel is WASTED",

    "if Age is AVERAGE and Weight is SUPERLIGHT and Amount is LITTLE then DrunkLevel is DRUNK",
    "if Age is AVERAGE and Weight is SUPERLIGHT and Amount is MEAN then DrunkLevel is DRUNK",
    "if Age is AVERAGE and Weight is SUPERLIGHT and Amount is ALOT then DrunkLevel is WASTED",

    "if Age is AVERAGE and Weight is LIGHT and Amount is LITTLE then DrunkLevel is TIPSY",
    "if Age is AVERAGE and Weight is LIGHT and Amount is MEAN then DrunkLevel is DRUNK",
    "if Age is AVERAGE and Weight is LIGHT and Amount is ALOT then DrunkLevel is WASTED",

    "if Age is AVERAGE and Weight is AVERAGE and Amount is LITTLE then DrunkLevel is TIPSY",
    "if Age is AVERAGE and Weight is AVERAGE and Amount is MEAN then DrunkLevel is DRUNK",
    "if Age is AVERAGE and Weight is AVERAGE and Amount is ALOT then DrunkLevel is DRUNK",

    "if Age is AVERAGE and Weight is FAT and Amount is LITTLE then DrunkLevel is SOBER",
    "if Age is AVERAGE and Weight is FAT and Amount is MEAN then DrunkLevel is SOBER",
    "if Age is AVERAGE and Weight is FAT and Amount is ALOT then DrunkLevel is TIPSY",

    "if Age is OLD and Weight is SUPERLIGHT and Amount is LITTLE then DrunkLevel is DRUNK",
    "if Age is OLD and Weight is SUPERLIGHT and Amount is MEAN then DrunkLevel is DRUNK",
    "if Age is OLD and Weight is SUPERLIGHT and Amount is ALOT then DrunkLevel is WASTED",

    "if Age is OLD and Weight is LIGHT and Amount is LITTLE then DrunkLevel is TIPSY",
    "if Age is OLD and Weight is LIGHT and Amount is MEAN then DrunkLevel is DRUNK",
    "if Age is OLD and Weight is LIGHT and Amount is ALOT then DrunkLevel is WASTED",

    "if Age is OLD and Weight is AVERAGE and Amount is LITTLE then DrunkLevel is SOBER",
    "if Age is OLD and Weight is AVERAGE and Amount is MEAN then DrunkLevel is DRUNK",
    "if Age is OLD and Weight is AVERAGE and Amount is ALOT then DrunkLevel is WASTED",

    "if Age is OLD and Weight is FAT and Amount is LITTLE then DrunkLevel is TIPSY",
    "if Age is OLD and Weight is FAT and Amount is MEAN then DrunkLevel is TIPSY",
    "if Age is OLD and Weight is FAT and Amount is ALOT then DrunkLevel is DRUNK",
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    Engine* engine = Q_NULLPTR;
    InputVariable* ageInput = Q_NULLPTR;
    InputVariable* weightInput = Q_NULLPTR;
    InputVariable* gender = Q_NULLPTR;
    InputVariable* amountInput = Q_NULLPTR;

    RuleBlock* ruleBlock = Q_NULLPTR;
    OutputVariable* drunkLevel = Q_NULLPTR;

    ~MainWindow();

public slots:
    bool eventFilter(QObject* watched, QEvent* event);

private slots:
    void on_pushButton_clicked();
    void setResultImage(double restult);


private:
    Ui::MainWindow *ui;

    QImage image;

    void setUpModel();
};

#endif // MAINWINDOW_H
