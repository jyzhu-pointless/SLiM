//
//  QtSLiMGraphView_CustomPlot.h
//  SLiM
//
//  Created by Ben Haller on 1/19/2024.
//  Copyright (c) 2024 Philipp Messer.  All rights reserved.
//	A product of the Messer Lab, http://messerlab.org/slim/
//

//	This file is part of SLiM.
//
//	SLiM is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
//	SLiM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License along with SLiM.  If not, see <http://www.gnu.org/licenses/>.

#ifndef QTSLIMGRAPHVIEW_CUSTOMPLOT_H
#define QTSLIMGRAPHVIEW_CUSTOMPLOT_H

#include <QWidget>

#include <vector>

#include "QtSLiMGraphView.h"


enum class QtSLiM_CustomPlotType : int {
    kLines,
    kPoints,
    kText
};

class QtSLiMGraphView_CustomPlot : public QtSLiMGraphView
{
    Q_OBJECT
    
public:
    QtSLiMGraphView_CustomPlot(QWidget *p_parent, QtSLiMWindow *controller);
    virtual ~QtSLiMGraphView_CustomPlot() override;
    
    void freeData(void);
    
    void setTitle(QString title);
    void setXLabel(QString x_label);
    void setYLabel(QString y_label);
    void setAxisRanges(double *x_range, double *y_range);
    
    void addLineData(double *x_values, double *y_values, int data_count,
                     std::vector<QColor> *color, std::vector<double> *lwd);
    void addPointData(double *x_values, double *y_values, int data_count,
                      std::vector<int> *symbol, std::vector<QColor> *color, std::vector<QColor> *border,
                      std::vector<double> *lwd, std::vector<double> *size);
    void addTextData(double *x_values, double *y_values, std::vector<QString> *labels, int data_count,
                     std::vector<QColor> *color, std::vector<double> *size, double *adj);
    
    virtual QString graphTitle(void) override;
    virtual QString aboutString(void) override;
    virtual QString disableMessage(void) override;
    virtual void drawGraph(QPainter &painter, QRect interiorRect) override;
    virtual void appendStringForData(QString &string) override;
    
public slots:
    virtual void controllerRecycled(void) override;
    
private:
    QString title_;
    
    // we can keep any number of sets of lines and points; they get plotted in the order supplied to us
    // some parameters don't apply to a given plot type; placeholder values are inserted for those
    bool has_finite_data_;
    
    std::vector<QtSLiM_CustomPlotType> plot_type_;
    std::vector<double *> xdata_;
    std::vector<double *> ydata_;
    std::vector<int> data_count_;                       // the count for the xdata / ydata buffers
    std::vector<std::vector<QString> *> labels_;        // one label per point
    std::vector<std::vector<int> *> symbol_;            // one symbol per point, OR one symbol for all points
    std::vector<std::vector<QColor> *> color_;          // one color per point, OR one color for all points
    std::vector<std::vector<QColor> *> border_;         // one border color per point, OR one for all points
    std::vector<std::vector<double> *> line_width_;     // one lwd per point, OR one lwd for all points
    std::vector<std::vector<double> *> size_;           // one size per point, OR one size for all points
    std::vector<double> xadj_;                          // one xadj for all points
    std::vector<double> yadj_;                          // one yadj for all points
    
    void dataRange(std::vector<double *> &data, double *p_min, double *p_max);
    void rescaleAxesForDataRange(void);
    void drawLines(QPainter &painter, QRect interiorRect, int dataIndex);
    void drawPoints(QPainter &painter, QRect interiorRect, int dataIndex);
    void drawText(QPainter &painter, QRect interiorRect, int dataIndex);
};


#endif // QTSLIMGRAPHVIEW_CUSTOMPLOT_H














































