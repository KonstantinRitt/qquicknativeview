#ifndef QQUICKIMPLICITSIZENATIVEVIEW_P_H
#define QQUICKIMPLICITSIZENATIVEVIEW_P_H

#include <qquicknativeview/qquickimplicitsizenativeview.h>

#include "qquicknativeview_p.h"

QT_BEGIN_NAMESPACE

class QQuickImplicitSizeNativeViewPrivate : public QQuickNativeViewPrivate
{
    Q_DECLARE_PUBLIC(QQuickImplicitSizeNativeView)

public:
    QQuickImplicitSizeNativeViewPrivate();
    ~QQuickImplicitSizeNativeViewPrivate() override;

    void implicitWidthChanged() override;
    void implicitHeightChanged() override;
};

QT_END_NAMESPACE

#endif // QQUICKIMPLICITSIZENATIVEVIEW_P_H
