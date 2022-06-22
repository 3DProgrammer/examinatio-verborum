/*
 * Nox Style is based of the "Norwegian Wood" style, available at https://code.qt.io/cgit/qt/qtbase.git/tree/examples/widgets/widgets/styles?h=6.3
 */
#include "NoxStyle.h"
#include <QComboBox>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QStyleFactory>
#define NOX_MAX_RADIUS 12
NoxStyle::NoxStyle() : QProxyStyle(QStyleFactory::create("fusion")) {
    setObjectName("Nox");
}


QPalette NoxStyle::standardPalette() const {
    if (!m_standardPalette.isBrushSet(QPalette::Disabled, QPalette::Mid)) {
        QColor slightlyOpaqueBlack(0, 0, 0, 63);
        QColor textColor = Qt::white;
        QImage backgroundImage(":/res/noxbackground.png");
        QImage buttonImage(":/res/noxbutton.png");
        QImage midImage = buttonImage.convertToFormat(QImage::Format_RGB32);
        QPainter painter;
        painter.begin(&midImage);
        painter.setPen(Qt::NoPen);
        painter.fillRect(midImage.rect(), slightlyOpaqueBlack);
        painter.end();
        QPalette palette(Qt::black);
        palette.setBrush(QPalette::BrightText, textColor);
        palette.setBrush(QPalette::Base, QColor(30,30,30));
        palette.setBrush(QPalette::Text, textColor);
        palette.setBrush(QPalette::WindowText, textColor);
        palette.setBrush(QPalette::ButtonText, textColor);
        palette.setBrush(QPalette::Highlight, Qt::darkGray);
        setTexture(palette, QPalette::Button, buttonImage);
        setTexture(palette, QPalette::Mid, midImage);
        setTexture(palette, QPalette::Window, backgroundImage);

        QBrush brush = palette.window();
        brush.setColor(brush.color().darker());

        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush);

        m_standardPalette = palette;
    }

    return m_standardPalette;
}
void NoxStyle::polish(QWidget *widget) {
    if (qobject_cast<QPushButton *>(widget) || qobject_cast<QComboBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, true);
}


void NoxStyle::unpolish(QWidget *widget) {
    if (qobject_cast<QPushButton *>(widget) || qobject_cast<QComboBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, false);
}


int NoxStyle::pixelMetric(QStyle::PixelMetric metric,
                          const QStyleOption *option,
                          const QWidget *widget) const {
    switch (metric) {
        default:
            return QProxyStyle::pixelMetric(metric, option, widget);
    }
}


int NoxStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option,

                        const QWidget *widget,
                        QStyleHintReturn *returnData) const {
    switch (hint) {
        case SH_DitherDisabledText:
            return int(false);
        case SH_EtchDisabledText:
            return int(false);
        default:
            return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
}


void NoxStyle::drawPrimitive(QStyle::PrimitiveElement element,

                             const QStyleOption *option,
                             QPainter *painter,
                             const QWidget *widget) const {
    switch (element) {
        case PE_PanelButtonCommand: {
            int x, y, width, height;
            option->rect.getRect(&x, &y, &width, &height);
            QPainterPath roundRect = roundRectPath(option->rect);
            int radius = qMin(qMin(width, height) / 2,NOX_MAX_RADIUS);
            QBrush brush;
            bool pressed;
            pressed = (option->state & State_Sunken);

            painter->save();

            painter->setRenderHint(QPainter::Antialiasing, true);

            painter->fillPath(roundRect, brush);

            if (pressed) {
                painter->fillPath(roundRect, QColor(255, 255, 255, 50));
            }
            for (int i=10; i>0; i--) {
                QPen pen(QColor(255,255,255,26),i);
                painter->setClipPath(roundRect);
                painter->setPen(pen);
                painter->drawPath(roundRect);
            }
//            QConicalGradient gradient;
//            gradient.setCenter(x+width/2, y+height/2);
//            gradient.setColorAt(0, QColor(255,0,0));
//            gradient.setColorAt(1.0/3.0, QColor(0,255,0));
//            gradient.setColorAt(2.0/3.0,QColor(0,0,255));
//            gradient.setColorAt(1,QColor(255,0,0));
//            QPen pen(QBrush(gradient),10);
//            painter->setClipPath(roundRect);
//            painter->setPen(pen);
//            painter->drawPath(roundRect);

//            QPen pen(QColor(255,255,255,128), 10);
//            painter->setClipPath(roundRect);
//            painter->setPen(pen);
//            painter->drawPath(roundRect);
//            pen= QPen(QColor(255,255,255), 2);
//            painter->setClipPath(roundRect);
//            painter->setPen(pen);
//            painter->drawPath(roundRect);
            painter->setTransform(QTransform());
            painter->setPen(option->palette.windowText().color());
            painter->setClipping(false);
            painter->drawPath(roundRect);

            painter->restore();
        } break;

        default:

            QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
}


void NoxStyle::drawControl(QStyle::ControlElement element,

                           const QStyleOption *option,
                           QPainter *painter,
                           const QWidget *widget) const {
    switch (element) {
        default:
            QProxyStyle::drawControl(element, option, painter, widget);
    }
}


void NoxStyle::setTexture(QPalette &palette, QPalette::ColorRole role,

                          const QImage &image) {
    for (int i = 0; i < QPalette::NColorGroups; ++i) {
        QBrush brush(image);
        brush.setColor(palette.brush(QPalette::ColorGroup(i), role).color());
        palette.setBrush(QPalette::ColorGroup(i), role, brush);
    }
}


QPainterPath NoxStyle::roundRectPath(const QRect &rect)

{
    int radius = qMin(qMin(rect.width(), rect.height()) / 2,NOX_MAX_RADIUS);
    int diam = 2 * radius;

    int x1, y1, x2, y2;
    rect.getCoords(&x1, &y1, &x2, &y2);

    QPainterPath path;
    path.moveTo(x2, y1 + radius);
    path.arcTo(QRect(x2 - diam, y1, diam, diam), 0.0, +90.0);
    path.lineTo(x1 + radius, y1);
    path.arcTo(QRect(x1, y1, diam, diam), 90.0, +90.0);
    path.lineTo(x1, y2 - radius);
    path.arcTo(QRect(x1, y2 - diam, diam, diam), 180.0, +90.0);
    path.lineTo(x1 + radius, y2);
    path.arcTo(QRect(x2 - diam, y2 - diam, diam, diam), 270.0, +90.0);
    path.closeSubpath();
    return path;
}
