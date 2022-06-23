//
// Created by miles on 23/6/22.
//

#ifndef EXAMINATIO_VERBORUM_NEONSTYLE_H
#define EXAMINATIO_VERBORUM_NEONSTYLE_H
#include <QProxyStyle>
class NeonStyle : public QProxyStyle {
    Q_OBJECT
public:
    NeonStyle();
    QPalette standardPalette() const override;
    void polish(QWidget *widget) override;
    void unpolish(QWidget *widget) override;
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                       QPainter *painter, const QWidget *widget) const override;
    void drawControl(ControlElement control, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget) const override;

private:
    static void setTexture(QPalette &palette, QPalette::ColorRole role,
                           const QImage &image);
    static QPainterPath roundRectPath(const QRect &rect);
    mutable QPalette m_standardPalette;
};
#endif//EXAMINATIO_VERBORUM_NEONSTYLE_H
