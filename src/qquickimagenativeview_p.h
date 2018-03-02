#ifndef QQUICKIMAGENATIVEVIEW_P_H
#define QQUICKIMAGENATIVEVIEW_P_H

#include <qquicknativeview/qquickimagenativeview.h>

#include "qquickimplicitsizenativeview_p.h"

QT_BEGIN_NAMESPACE

class QQuickImageNativeViewPrivate : public QQuickImplicitSizeNativeViewPrivate
{
    Q_DECLARE_PUBLIC(QQuickImageNativeView)

public:
    QQuickImageNativeViewPrivate();
    ~QQuickImageNativeViewPrivate() override;

    QSizeF paintedSize;
    QSizeF sourceSize;

    QQuickImageNativeView::FillMode fillMode;
    Qt::Alignment align;
};

QT_END_NAMESPACE

#endif // QQUICKIMAGENATIVEVIEW_P_H
