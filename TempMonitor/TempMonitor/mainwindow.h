#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUpPlot(QCustomPlot *customPlot);

private slots:
    void on_actionSettings_triggered();

    void on_actionConnect_toggled(bool arg1);

    void on_actionDisconnect_toggled(bool arg1);

    void realtimeDataSlot();

    void on_actionPrint_triggered();

private:
    Ui::MainWindow *ui;
    QTimer dataTimer;
};

#endif // MAINWINDOW_H
