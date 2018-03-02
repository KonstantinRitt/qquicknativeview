#include "qquicknativeview_p.h"

#include <QtCore/qbasicatomic.h>
#include <QtCore/qmath.h>

#import <UIKit/UIKit.h>

QT_BEGIN_NAMESPACE

static QBasicAtomicInteger<uint> s_id = Q_BASIC_ATOMIC_INITIALIZER(10000);

void QQuickNativeViewPrivate::create()
{
    Q_Q(QQuickNativeView);

    handle = q->createNativeView();

    Q_ASSERT(handle != 0);

    Q_ASSERT([(__bridge id)(void *)handle isKindOfClass:[UIView class]]);

    UIView *view = (__bridge UIView *)(void *)handle;
    Q_ASSERT(view != nil);

    nativeViewId = view.tag;
    if (nativeViewId == 0)
        view.tag = nativeViewId = s_id.fetchAndAddOrdered(1);
    Q_ASSERT(nativeViewId != 0);

    UIView *window = (__bridge UIView *)(void *)q->window()->winId();
    Q_ASSERT(window != nil);

    [window addSubview:view];

    q->afterNativeViewCreated();
}

void QQuickNativeViewPrivate::destroy()
{
    Q_Q(QQuickNativeView);

    UIView *view = (__bridge UIView *)(void *)handle;
    Q_ASSERT(view != nil);

    q->beforeNativeViewDestroyed();

    [view removeFromSuperview];

    q->destroyNativeView(handle);

    handle = 0;
    nativeViewId = 0;
}

void QQuickNativeViewPrivate::updateGeometry(const QRectF &geometry)
{
    UIView *view = (__bridge UIView *)(void *)handle;
    Q_ASSERT(view != nil);

    view.frame = geometry.toCGRect();

    [view.superview setNeedsLayout];
}

void QQuickNativeViewPrivate::updateRotation(qreal angle)
{
    UIView *view = (__bridge UIView *)(void *)handle;
    Q_ASSERT(view != nil);

    view.transform = CGAffineTransformRotate(view.transform, qDegreesToRadians(angle));
}

void QQuickNativeViewPrivate::updateVisibility(bool visible)
{
    UIView *view = (__bridge UIView *)(void *)handle;
    Q_ASSERT(view != nil);

    view.hidden = !visible;
}

void QQuickNativeViewPrivate::updateOpacity(qreal opacity)
{
    UIView *view = (__bridge UIView *)(void *)handle;
    Q_ASSERT(view != nil);

    view.alpha = opacity;
}

void QQuickNativeViewPrivate::updateEnabled(bool enabled)
{
    UIView *view = (__bridge UIView *)(void *)handle;
    Q_ASSERT(view != nil);

    view.userInteractionEnabled = enabled;
}

QT_END_NAMESPACE
