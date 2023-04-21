/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "themewidget.h"
#include "ui_themewidget.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>

#define TO_PLUS_0 0.000001

ThemeWidget::ThemeWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui_ThemeWidgetForm)
{
    m_ui->setupUi(this);

    QString lineEditStyle = "color: white;  background-color: rgba(64, 67, 74, 255)";
    m_ui->lineEditT1x1->setStyleSheet(lineEditStyle);
    m_ui->lineEditT1y1->setStyleSheet(lineEditStyle);
    m_ui->lineEditT1x2->setStyleSheet(lineEditStyle);
    m_ui->lineEditT1y2->setStyleSheet(lineEditStyle);
    m_ui->lineEditT1x3->setStyleSheet(lineEditStyle);
    m_ui->lineEditT1y3->setStyleSheet(lineEditStyle);

    m_ui->lineEditT1x1->setValidator( new QDoubleValidator(0, 100, 2, this) );
    m_ui->lineEditT1y1->setValidator( new QDoubleValidator(0, 100, 2, this) );
    m_ui->lineEditT1x2->setValidator( new QDoubleValidator(0, 100, 2, this) );
    m_ui->lineEditT1y2->setValidator( new QDoubleValidator(0, 100, 2, this) );
    m_ui->lineEditT1x3->setValidator( new QDoubleValidator(0, 100, 2, this) );
    m_ui->lineEditT1y3->setValidator( new QDoubleValidator(0, 100, 2, this) );

    m_ui->lineEditT1x1->setText(QString("1.0"));
    m_ui->lineEditT1y1->setText(QString("1.0"));
    m_ui->lineEditT1x2->setText(QString("3.0"));
    m_ui->lineEditT1y2->setText(QString("6.0"));
    m_ui->lineEditT1x3->setText(QString("7.0"));
    m_ui->lineEditT1y3->setText(QString("2.0"));

    //create charts

    QChartView *chartView;

    chartView = new QChartView(createLineChart());
    m_ui->gridLayout->addWidget(chartView, 1, 2);
    m_charts << chartView;

    updateUI();
}

ThemeWidget::~ThemeWidget()
{
    delete m_ui;
}

QChart *ThemeWidget::createLineChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Line chart");

//    QString name("Triangle ");
//    int nameIndex = 0;
//    for (const DataList &list : m_dataTable) {
//        QLineSeries *series = new QLineSeries(chart);
//        for (const Data &data : list)
//            series->append(data.first);
//        series->setName(name + QString::number(nameIndex));
//        nameIndex++;
//        chart->addSeries(series);
//    }

    std::vector<std::vector<linear_space::point>> triangles = setTrianglesPoints();

    for (const auto& triangle: triangles)
    {
        QLineSeries *series_triangle = new QLineSeries(chart);
        for (const auto& points: triangle)
        {
            series_triangle->append(QPointF(points.x, points.y));
        }
        series_triangle->append(QPointF(triangle.front().x, triangle.front().y));
        chart->addSeries(series_triangle);
    }

    limits _limits;

    setLimits(triangles, _limits);

    linear_space::area2d triangle_cross(std::make_tuple(triangles[0][0], triangles[0][1], triangles[0][2]));
    triangle_cross &= linear_space::area2d(std::make_tuple(triangles[1][0], triangles[1][1], triangles[1][2]));

    long double x_diff = (long double)(_limits.x_up_limit - _limits.x_down_limit) / 500;
    long double y_diff = (long double)(_limits.y_up_limit - _limits.y_down_limit) / 500;
    for (long double x_iter = _limits.x_down_limit; x_iter < _limits.x_up_limit; x_iter += x_diff)
    {
        for (long double y_iter = _limits.y_down_limit; y_iter < _limits.y_up_limit; y_iter += y_diff)
        {
            linear_space::point p = {x_iter, y_iter};
            if (triangle_cross.in_area(p))
            {
                QLineSeries *upper_series = new QLineSeries(chart);
                upper_series->append(QPointF(x_iter, y_iter + TO_PLUS_0));
                upper_series->append(QPointF(x_iter + TO_PLUS_0, y_iter + TO_PLUS_0));

                QLineSeries *lower_series = new QLineSeries(chart);
                lower_series->append(QPointF(x_iter, y_iter));
                lower_series->append(QPointF(x_iter + TO_PLUS_0, y_iter));

                QAreaSeries *area = new QAreaSeries(upper_series, lower_series);
                chart->addSeries(area);
            }
        }
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(_limits.x_down_limit, _limits.x_up_limit);
    chart->axes(Qt::Vertical).first()->setRange(_limits.y_down_limit, _limits.y_up_limit);

    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");

    return chart;
}


void ThemeWidget::updateUI()
{
    QChart::ChartTheme theme = QChart::ChartThemeBlueCerulean;
    const auto charts = m_charts;
    for (QChartView *chartView : charts) {
        chartView->chart()->setTheme(theme);
    }
    for (QChartView *chartView : charts)
        chartView->chart()->legend()->hide();
//    Qt::Alignment alignment(Qt::AlignBottom);

//    for (QChartView *chartView : charts) {
//        chartView->chart()->legend()->setAlignment(alignment);
//        chartView->chart()->legend()->show();
//    }
}

std::vector<std::vector<linear_space::point>> ThemeWidget::setTrianglesPoints() const
{
    pointTable triangles;

    linear_space::point T1p1 = {m_ui->lineEditT1x1->text().toDouble(), m_ui->lineEditT1y1->text().toDouble()};
    linear_space::point T1p2 = {m_ui->lineEditT1x2->text().toDouble(), m_ui->lineEditT1y2->text().toDouble()};
    linear_space::point T1p3 = {m_ui->lineEditT1x3->text().toDouble(), m_ui->lineEditT1y3->text().toDouble()};

    std::vector<linear_space::point> triangle1;
    triangle1.push_back(T1p1);
    triangle1.push_back(T1p2);
    triangle1.push_back(T1p3);
    triangles.push_back(triangle1);

    linear_space::point T2p1 = {4.0, 1.0};
    linear_space::point T2p2 = {10.0, 1.0};
    linear_space::point T2p3 = {10.0, 7.0};

    std::vector<linear_space::point> triangle2;
    triangle2.push_back(T2p1);
    triangle2.push_back(T2p2);
    triangle2.push_back(T2p3);
    triangles.push_back(triangle2);

    return triangles;
}

void ThemeWidget::setLimits(const pointTable& all_points, limits& _limits) const
{
    linear_space::point min_point = {INT_MAX, INT_MAX};
    linear_space::point max_point = {INT_MIN, INT_MIN};

    for (const auto& classter_points: all_points)
    {
        for (const auto& points: classter_points)
        {
            min_point.x = std::min(min_point.x, points.x);
            min_point.y = std::min(min_point.y, points.y);
            max_point.x = std::max(max_point.x, points.x);
            max_point.y = std::max(max_point.y, points.y);
        }
    }
    long double x_size = max_point.x - min_point.x;
    long double y_size = max_point.y - min_point.y;

    _limits.x_down_limit = int(min_point.x - 0.1 * x_size);
    _limits.x_up_limit = std::ceil(max_point.x + 0.1 * x_size);
    _limits.y_down_limit = int(min_point.y - 0.1 * y_size);
    _limits.y_up_limit = std::ceil(max_point.y + 0.1 * y_size);
}

