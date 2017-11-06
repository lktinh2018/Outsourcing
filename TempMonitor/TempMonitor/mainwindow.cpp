#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include <QPrinter>
#include <QPrintDialog>

#include <QDebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->customPlot->replot();

    realtimeDataSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setUpPlot(QCustomPlot *customPlot) {

    // add new graphs and set their look:
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue

    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-2, 2);

    //Set up timer that repeatly calls MainWindow::realtimeDataSlot()
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));

    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::realtimeDataSlot() {
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;
    static double lastPointKey = 0;
    if(key - lastPointKey > 0.002) {
        ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
        lastPointKey = key;
    }
    ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->customPlot->replot();
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog settingsDialog;
    settingsDialog.setModal(true);
    settingsDialog.exec();
}

void MainWindow::on_actionConnect_toggled(bool arg1)
{
    if(arg1) {
        ui->actionDisconnect->setChecked(false);
        ui->actionConnect->setCheckable(false);
        ui->actionDisconnect->setCheckable(true);
        ui->customPlot->replot();
        setUpPlot(ui->customPlot);
        setUpPlot(ui->customPlot);
    }

}

void MainWindow::on_actionDisconnect_toggled(bool arg1)
{
    if(arg1) {
        dataTimer.stop();
        ui->actionConnect->setChecked(false);
        ui->actionDisconnect->setCheckable(false);
        ui->actionConnect->setCheckable(true);

        ui->customPlot->clearPlottables();
        ui->customPlot->replot();
    }
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setPrinterName("Printer");
    QPrintDialog printDialog(&printer, this);
    if(printDialog.exec() == QDialog::Rejected)
        return;
    else {
        QPainter painter;
        painter.begin(&printer);
        double xscale = printer.pageRect().width()/double(ui->customPlot->width());
        double yscale = printer.pageRect().height()/double(ui->customPlot->height());
        double scale = qMin(xscale, yscale);
        painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
                           printer.paperRect().y() + printer.pageRect().height()/2);
        painter.scale(scale, scale);
        painter.translate(-width()/2, -height()/2);

        ui->customPlot->render(&painter);
        ui->customPlot->render(&painter);
    }
}
