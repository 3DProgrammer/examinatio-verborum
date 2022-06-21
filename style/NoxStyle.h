#ifndef EXAMINATIO_VERBORUM_NOXSTYLE_H
#define EXAMINATIO_VERBORUM_NOXSTYLE_H
#include <QProxyStyle>
class NoxStyle : public QProxyStyle {
    Q_OBJECT
public:
    NoxStyle();
    QPalette standardPalette() const override;
    void polish(QWidget *widget) override;
    void unpolish(QWidget *widget) override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option,
                    const QWidget *widget) const override;
    int styleHint(StyleHint hint, const QStyleOption *option,
                  const QWidget *widget, QStyleHintReturn *returnData) const override;
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
#endif//EXAMINATIO_VERBORUM_NOXSTYLE_H
