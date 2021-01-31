#include "myplotquickpainteditem.h"

QSize MyPlotQuickPaintedItem::s_size(300, 300);

MyPlotQuickPaintedItem::MyPlotQuickPaintedItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    m_plot = makePlot();
    setImplicitSize(s_size.width(), s_size.height());
}

MyPlotQuickPaintedItem::~MyPlotQuickPaintedItem()
{
    delete m_plot;
}

bool MyPlotQuickPaintedItem::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_plot)
    {
        if (event->type() == QEvent::Paint || event->type() == QEvent::UpdateRequest)
        {
            update();
        }
    }
    return QQuickPaintedItem::eventFilter(watched, event);
}

void MyPlotQuickPaintedItem::paint(QPainter *painter)
{
    m_plot->render(painter);
}

bool MyPlotQuickPaintedItem::event(QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress
        || event->type() == QEvent::MouseButtonRelease
        || event->type() == QEvent::MouseButtonDblClick
        || event->type() == QEvent::KeyPress
        || event->type() == QEvent::KeyRelease)
    {
        QApplication::sendEvent(m_plot, event);
        return true;
    }
    else if (event->type() == QEvent::FocusIn)
    {
        forceActiveFocus();
    }
    return QQuickPaintedItem::event(event);
}

QCustomPlot *MyPlotQuickPaintedItem::makePlot()
{
    QCustomPlot *customPlot = new QCustomPlot;

    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i = 0; i < 101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i]; // let's plot a quadratic function
    }

    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);

    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();

    customPlot->resize(s_size);
    customPlot->installEventFilter(this);
    return customPlot;
}
