#ifndef MYPLOTQUICKPAINTEDITEM_H
#define MYPLOTQUICKPAINTEDITEM_H

#include "qcustomplot.h"

#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QPainter>
#include <QEvent>
#include <QSize>

class MyPlotQuickPaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int plotWidth READ plotWidth)
    Q_PROPERTY(int plotHeight READ plotHeight)
public:
    MyPlotQuickPaintedItem(QQuickItem *parent = nullptr);
    virtual ~MyPlotQuickPaintedItem();

    int plotWidth() const
    {
        return s_size.width();
    }

    int plotHeight() const
    {
        return s_size.height();
    }
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void paint(QPainter *painter);
    bool event(QEvent *event);
private:
    QCustomPlot *makePlot();

    QCustomPlot *m_plot;
    static QSize s_size;
};

#endif // MYPLOTQUICKPAINTEDITEM_H
