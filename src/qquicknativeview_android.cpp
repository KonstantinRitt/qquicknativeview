#include "qquicknativeview_p.h"

#include <QtCore/qbasicatomic.h>

#include <QtGui/private/qhighdpiscaling_p.h>

#include <QtAndroidExtras/qandroidfunctions.h>
#include <QtAndroidExtras/qandroidjnienvironment.h>
#include <QtAndroidExtras/qandroidjniobject.h>

QT_BEGIN_NAMESPACE

static QBasicAtomicInteger<uint> s_id = Q_BASIC_ATOMIC_INITIALIZER(10000);

void QQuickNativeViewPrivate::create()
{
    Q_Q(QQuickNativeView);

    QtAndroid::runOnAndroidThreadSync([this]() {
        handle = q_func()->createNativeView();
        Q_ASSERT(handle != 0);

        QAndroidJniObject *view = reinterpret_cast<QAndroidJniObject *>(handle);
        Q_ASSERT(view != nullptr && view->isValid());

        nativeViewId = s_id.fetchAndAddOrdered(1);
        Q_ASSERT(nativeViewId != 0);

        QAndroidJniObject::callStaticMethod<void>("org/qtproject/qt5/android/QtNative",
                                                  "insertNativeView", "(ILandroid/view/View;IIII)V",
                                                  jint(nativeViewId),
                                                  view->object(),
                                                  0,
                                                  0,
                                                  0,
                                                  0);
    });

    q->afterNativeViewCreated();
}

void QQuickNativeViewPrivate::destroy()
{
    Q_Q(QQuickNativeView);

    q->beforeNativeViewDestroyed();

    QtAndroid::runOnAndroidThreadSync([this]() {
        Q_ASSERT(nativeViewId != 0);

        // if it was the last view, it won't be released until replaced with another view
        // see QtNative.destroySurface for details
        QAndroidJniObject::callStaticMethod<void>("org/qtproject/qt5/android/QtNative",
                                                  "destroySurface", "(I)V",
                                                  jint(nativeViewId));

        nativeViewId = 0;

        q_func()->destroyNativeView(handle);
        handle = 0;
    });
}

void QQuickNativeViewPrivate::updateGeometry(const QRectF &geometry)
{
    Q_Q(QQuickNativeView);

    if (Q_UNLIKELY(q->window() == nullptr))
        return;

    const QRect screenRect = QHighDpi::toNativePixels(geometry, q->window()).toRect();

    int viewId = nativeViewId;
    Q_ASSERT(viewId != 0);

    QtAndroid::runOnAndroidThread([viewId, screenRect]() {
        QAndroidJniObject::callStaticMethod<void>("org/qtproject/qt5/android/QtNative",
                                                  "setSurfaceGeometry", "(IIIII)V",
                                                  jint(viewId),
                                                  jint(screenRect.x()),
                                                  jint(screenRect.y()),
                                                  jint(screenRect.width()),
                                                  jint(screenRect.height()));
    });
}

void QQuickNativeViewPrivate::updateRotation(qreal angle)
{
    const QAndroidJniObject view = *reinterpret_cast<QAndroidJniObject *>(handle);
    Q_ASSERT(view.isValid());

    QtAndroid::runOnAndroidThread([view, angle]() {
        view.callMethod<void>("setRotation", "(F)V",
                              jfloat(angle));
    });
}

void QQuickNativeViewPrivate::updateVisibility(bool visible)
{
    const QAndroidJniObject view = *reinterpret_cast<QAndroidJniObject *>(handle);
    Q_ASSERT(view.isValid());

    QtAndroid::runOnAndroidThread([view, visible]() {
        QAndroidJniObject::callStaticMethod<void>("org/qtproject/qt5/android/QtNative",
                                                  "setViewVisibility", "(Landroid/view/View;Z)V",
                                                  view.object(),
                                                  jboolean(visible));
    });
}

void QQuickNativeViewPrivate::updateOpacity(qreal opacity)
{
    const QAndroidJniObject view = *reinterpret_cast<QAndroidJniObject *>(handle);
    Q_ASSERT(view.isValid());

    QtAndroid::runOnAndroidThread([view, opacity]() {
        view.callMethod<void>("setAlpha", "(F)V",
                              jfloat(opacity));
    });
}

void QQuickNativeViewPrivate::updateEnabled(bool enabled)
{
    const QAndroidJniObject view = *reinterpret_cast<QAndroidJniObject *>(handle);
    Q_ASSERT(view.isValid());

    QtAndroid::runOnAndroidThread([view, enabled]() {
        view.callMethod<void>("setEnabled", "(Z)V",
                              jboolean(enabled));
    });
}

QT_END_NAMESPACE
