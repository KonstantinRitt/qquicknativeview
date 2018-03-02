#ifndef QQUICKIMPLICITSIZENATIVEVIEW_H
#define QQUICKIMPLICITSIZENATIVEVIEW_H

#include <qquicknativeview/qquicknativeview.h>

QT_BEGIN_NAMESPACE

class QQuickImplicitSizeNativeViewPrivate;
class QQuickImplicitSizeNativeView : public QQuickNativeView
{
    Q_OBJECT
    Q_PROPERTY(qreal implicitWidth READ implicitWidth NOTIFY implicitWidthChanged2)
    Q_PROPERTY(qreal implicitHeight READ implicitHeight NOTIFY implicitHeightChanged2)

public:
    explicit QQuickImplicitSizeNativeView(QQuickItem *parent = nullptr);
    ~QQuickImplicitSizeNativeView() override;

Q_SIGNALS:
    Q_REVISION(1) void implicitWidthChanged2();
    Q_REVISION(1) void implicitHeightChanged2();

protected:
    QQuickImplicitSizeNativeView(QQuickImplicitSizeNativeViewPrivate &dd, QQuickItem *parent);

private:
    Q_DISABLE_COPY(QQuickImplicitSizeNativeView)
    Q_DECLARE_PRIVATE(QQuickImplicitSizeNativeView)
};

QT_END_NAMESPACE

#endif // QQUICKIMPLICITSIZENATIVEVIEW_H
