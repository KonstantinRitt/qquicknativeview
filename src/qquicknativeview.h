#ifndef QQUICKNATIVEVIEW_H
#define QQUICKNATIVEVIEW_H

#include <QtQuick/qquickitem.h>

QT_BEGIN_NAMESPACE

typedef quintptr NativeViewHandle;

class QQuickNativeViewPrivate;
class QQuickNativeView : public QQuickItem
{
    Q_OBJECT

public:
    explicit QQuickNativeView(QQuickItem *parent = nullptr);
    ~QQuickNativeView() override;

protected:
    NativeViewHandle nativeView() const;
    virtual NativeViewHandle createNativeView() const = 0;
    virtual void afterNativeViewCreated();
    virtual void beforeNativeViewDestroyed();
    virtual void destroyNativeView(NativeViewHandle view) const = 0;

protected:
    void itemChange(ItemChange change, const ItemChangeData &changeData) override;

    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *) override;
    void releaseResources() override;

protected:
    QQuickNativeView(QQuickNativeViewPrivate &dd, QQuickItem *parent);

private:
    Q_DISABLE_COPY(QQuickNativeView)
    Q_DECLARE_PRIVATE(QQuickNativeView)

    void performGeometryUpdate();
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickNativeView)

#endif // QQUICKNATIVEVIEW_H
