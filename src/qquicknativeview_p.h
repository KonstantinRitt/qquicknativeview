#ifndef QQUICKNATIVEVIEW_P_H
#define QQUICKNATIVEVIEW_P_H

#include <qquicknativeview/qquicknativeview.h>

#include <QtQuick/private/qquickitem_p.h>

QT_BEGIN_NAMESPACE

class QQuickNativeViewPrivate : public QQuickItemPrivate
{
    Q_DECLARE_PUBLIC(QQuickNativeView)

public:
    ~QQuickNativeViewPrivate() override;

    void create();
    void destroy();

    void updateGeometry(const QRectF &geometry);
    void updateRotation(qreal angle);
    void updateVisibility(bool visible);
    void updateOpacity(qreal opacity);
    void updateEnabled(bool enabled);

private:
    QSGTransformNode *node = nullptr;

    NativeViewHandle handle = 0;
    quintptr nativeViewId = 0;
    QRectF lastGeometry;
};

QT_END_NAMESPACE

#endif // QQUICKNATIVEVIEW_P_H
