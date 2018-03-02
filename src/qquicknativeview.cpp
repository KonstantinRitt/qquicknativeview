#include "qquicknativeview.h"
#include "qquicknativeview_p.h"

QT_BEGIN_NAMESPACE


QQuickNativeViewPrivate::~QQuickNativeViewPrivate() = default;


QQuickNativeView::QQuickNativeView(QQuickItem *parent)
    : QQuickItem(*new QQuickNativeViewPrivate, parent)
{
    setFlag(QQuickItem::ItemHasContents);
}

QQuickNativeView::QQuickNativeView(QQuickNativeViewPrivate &dd, QQuickItem *parent)
    : QQuickItem(dd, parent)
{
    setFlag(QQuickItem::ItemHasContents);
}

QQuickNativeView::~QQuickNativeView()
{
    Q_ASSERT(d_func()->handle == 0);
}

void QQuickNativeView::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &changeData)
{
    Q_D(QQuickNativeView);

    QQuickItem::itemChange(change, changeData);

    switch (change) {
    case QQuickItem::ItemSceneChange:
        if (changeData.window != nullptr) {
            if (Q_LIKELY(d->handle == 0))
                d->create();
        } else {
            if (Q_LIKELY(d->handle != 0))
                d->destroy();
        }
        break;
    case QQuickItem::ItemRotationHasChanged:
        if (Q_LIKELY(d->handle != 0))
            d->updateRotation(changeData.realValue);
        break;
    case QQuickItem::ItemVisibleHasChanged:
        if (Q_LIKELY(d->handle != 0))
            d->updateVisibility(changeData.boolValue);
        break;
    case QQuickItem::ItemOpacityHasChanged:
        if (Q_LIKELY(d->handle != 0))
            d->updateOpacity(changeData.realValue);
        break;
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
    case QQuickItem::ItemEnabledHasChanged:
        if (Q_LIKELY(d->handle != 0))
            d->updateEnabled(changeData.boolValue);
        break;
#endif

    default:
        break;
    }
}

QSGNode *QQuickNativeView::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *)
{
    Q_D(QQuickNativeView);

    if (Q_UNLIKELY(d->node == nullptr)) {
        node = d->node = new QSGTransformNode;

        QObject::connect(window(), &QQuickWindow::afterRendering, this, &QQuickNativeView::performGeometryUpdate, Qt::DirectConnection);
    }

    return node;
}

void QQuickNativeView::releaseResources()
{
    Q_D(QQuickNativeView);

    // When release resources is called on the GUI thread, we only need to
    // forget about the node. Since it is the node we returned from updatePaintNode
    // it will be managed by the scene graph.
    d->node = nullptr;

    QObject::disconnect(window(), &QQuickWindow::afterRendering, this, &QQuickNativeView::performGeometryUpdate);
}

NativeViewHandle QQuickNativeView::nativeView() const
{
    return d_func()->handle;
}

void QQuickNativeView::afterNativeViewCreated()
{
    Q_D(QQuickNativeView);

    Q_ASSERT(d->handle != 0);

    d->updateVisibility(isVisible());
    if (Q_UNLIKELY(opacity() != qreal(1.0)))
        d->updateOpacity(opacity());
    d->updateEnabled(isEnabled());
}

void QQuickNativeView::beforeNativeViewDestroyed()
{
    Q_D(QQuickNativeView);

    Q_ASSERT(d->handle != 0);

    d->updateVisibility(false);
}

void QQuickNativeView::performGeometryUpdate()
{
    Q_D(QQuickNativeView);

    if (Q_UNLIKELY(d->handle == 0))
        return;

    Q_ASSERT(d->node != nullptr);

    const QRectF newGeometry = d->node->combinedMatrix().mapRect(boundingRect());
    if (d->lastGeometry == newGeometry)
        return;

    d->lastGeometry = newGeometry;
    QMetaObject::invokeMethod(this, [this]() {
        Q_D(QQuickNativeView);

        d->updateGeometry(d->lastGeometry);
    }, Qt::QueuedConnection);
}

QT_END_NAMESPACE
