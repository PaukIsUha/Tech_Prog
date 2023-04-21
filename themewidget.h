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

#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include "linear_space.hpp"
#include "charts_limits.hpp"

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_END_NAMESPACE

typedef std::vector<std::vector<linear_space::point>> pointTable;

QT_USE_NAMESPACE

class ThemeWidget: public QWidget
{
    Q_OBJECT
public:
    explicit ThemeWidget(QWidget *parent = 0);
    ~ThemeWidget();

private Q_SLOTS:
    void updateUI();

    void on_lineEditT1x1_textEdited(const QString &arg1);

    void on_lineEditT1y1_textEdited(const QString &arg1);

    void on_lineEditT1x2_textEdited(const QString &arg1);

    void on_lineEditT1y2_textEdited(const QString &arg1);

    void on_lineEditT1x3_textEdited(const QString &arg1);

    void on_lineEditT1y3_textEdited(const QString &arg1);

private:
    void connectSignals();
    QChart *createLineChart() const;
    pointTable setTrianglesPoints() const;
    void setLimits(const pointTable& all_points, limits& _limits) const;

private:

    QList<QChartView *> m_charts;
    Ui_ThemeWidgetForm *m_ui;
};

#endif /* THEMEWIDGET_H */
