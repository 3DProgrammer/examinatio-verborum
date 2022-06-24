#include "NeonStyle.h"
#include <QComboBox>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QStyleFactory>
#include <QLineEdit>
#include <iostream>
NeonStyle::NeonStyle() : QProxyStyle(QStyleFactory::create("fusion")) {
    setObjectName("Neon");
}


QPalette NeonStyle::standardPalette() const {
    if (!m_standardPalette.isBrushSet(QPalette::Disabled, QPalette::Mid)) {
        QColor textColor = Qt::white;
        QPalette palette(Qt::black);
        palette.setBrush(QPalette::BrightText, textColor);
        palette.setBrush(QPalette::Base, QColor(30, 30, 30));
        palette.setBrush(QPalette::Text, textColor);
        palette.setBrush(QPalette::WindowText, textColor);
        palette.setBrush(QPalette::ButtonText, textColor);
        palette.setBrush(QPalette::Highlight, Qt::darkGray);
        palette.setBrush(QPalette::Button, Qt::black);
        palette.setBrush(QPalette::Mid, Qt::black);
        palette.setBrush(QPalette::Window, Qt::black);
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
void NeonStyle::polish(QWidget *widget) {
    if (qobject_cast<QPushButton *>(widget) || qobject_cast<QComboBox *>(widget) || qobject_cast<QLineEdit *>(widget)) {
        widget->setAttribute(Qt::WA_Hover, true);
    }
}


void NeonStyle::unpolish(QWidget *widget) {
    if (qobject_cast<QPushButton *>(widget) || qobject_cast<QComboBox *>(widget) || qobject_cast<QLineEdit *>(widget)) {
        widget->setAttribute(Qt::WA_Hover, false);
    }
}
void NeonStyle::drawPrimitive(QStyle::PrimitiveElement element,

                              const QStyleOption *option,
                              QPainter *painter,
                              const QWidget *widget) const {
    switch (element) {
        case PE_PanelButtonCommand: {
            int x, y, width, height;
            option->rect.getRect(&x, &y, &width, &height);
            QPainterPath roundRect = roundRectPath(option->rect);
            QBrush brush;
            bool pressed;
            pressed = (option->state & State_Sunken);
            bool hovered = (option->state & State_MouseOver);
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->fillPath(roundRect, brush);
            if (pressed) {
                painter->fillPath(roundRect, QColor(255, 255, 255, 50));
            }

            QLinearGradient gradient;
            //gradient.setCenter(x + width / 2.0, y + height / 2.0);
            gradient.setStart(x, 0);
            gradient.setFinalStop(x+width, 0);
            std::vector<QColor> colours = { //Colours taken from https://stackoverflow.com/questions/56418763/creating-the-perfect-rainbow-gradient-in-css
                    {255, 0, 0},
                    {255, 154, 0},
                    {208, 222, 33},
                    {79, 220, 74},
                    {63, 218, 216},
                    {47, 201, 226},
                    {28, 127, 238},
                    {95, 21, 242},
                    {186, 12, 248},
                    {251, 7, 217},
                    {255, 0, 0}};
            if (hovered) {
                for (int i = 0; i < colours.size(); ++i) {
                    gradient.setColorAt(float(i) / float(colours.size() - 1), colours[i]);
                }
                painter->fillPath(roundRect,QBrush(gradient));
            }
            else {
                for (int i = 0; i < colours.size(); ++i) {
                    QColor newColour(colours[i].red(), colours[i].green(), colours[i].blue(), 200);
                    gradient.setColorAt(float(i) / float(colours.size() - 1), newColour);
                }
            }
            QPen pen(QBrush(gradient), 4);
            painter->setPen(pen);
            painter->drawPath(roundRect);
            painter->restore();
        } break;
        case PE_FrameLineEdit: {
            int x, y, width, height;
            option->rect.getRect(&x, &y, &width, &height);
            QPainterPath roundRect = roundRectPath(option->rect);
            bool hovered = (option->state & State_MouseOver);
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing, true);

            QConicalGradient gradient;
            gradient.setCenter(x + width / 2.0, y + height / 2.0);
            std::vector<QColor> colours = { //Colours taken from https://stackoverflow.com/questions/56418763/creating-the-perfect-rainbow-gradient-in-css
                                           {255, 0, 0},
                                           {255, 154, 0},
                                           {208, 222, 33},
                                           {79, 220, 74},
                                           {63, 218, 216},
                                           {47, 201, 226},
                                           {28, 127, 238},
                                           {95, 21, 242},
                                           {186, 12, 248},
                                           {251, 7, 217},
                                           {255, 0, 0}};
            if (hovered) {
                for (int i = 0; i < colours.size(); ++i) {
                    gradient.setColorAt(float(i) / float(colours.size() - 1), colours[i]);
                }
            }
            else {
                for (int i = 0; i < colours.size(); ++i) {
                    QColor newColour(colours[i].red(), colours[i].green(), colours[i].blue(), 200);
                    gradient.setColorAt(float(i) / float(colours.size() - 1), newColour);
                }
            }
            QPen pen(QBrush(gradient), 4);
            painter->setPen(pen);
            painter->drawPath(roundRect);
            painter->restore();
        } break;
        case PE_PanelLineEdit: {
            int x, y, width, height;
            option->rect.getRect(&x, &y, &width, &height);
            QPainterPath roundRect = roundRectPath(option->rect);
            QBrush brush(QColor(255,255,255,20));
            bool pressed;
            pressed = (option->state & State_HasFocus);
            bool hovered = (option->state & State_MouseOver);
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->fillPath(roundRect, brush);
            if (pressed || hovered) {
                painter->fillPath(roundRect, QColor(255, 255, 255, 20));
            }
            painter->restore();
            drawPrimitive(PE_FrameLineEdit, option, painter, widget);
        } break;
        default:

            QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
}


void NeonStyle::drawControl(QStyle::ControlElement element,

                            const QStyleOption *option,
                            QPainter *painter,
                            const QWidget *widget) const {
    switch (element) {
        default:
            QProxyStyle::drawControl(element, option, painter, widget);
    }
}


void NeonStyle::setTexture(QPalette &palette, QPalette::ColorRole role,

                           const QImage &image) {
    for (int i = 0; i < QPalette::NColorGroups; ++i) {
        QBrush brush(image);
        brush.setColor(palette.brush(QPalette::ColorGroup(i), role).color());
        palette.setBrush(QPalette::ColorGroup(i), role, brush);
    }
}


QPainterPath NeonStyle::roundRectPath(const QRect &rect)

{
    int radius = qMin(rect.width(), rect.height()) / 2;
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
