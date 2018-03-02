#include "qquickimplicitsizenativeview.h"
#include "qquickimplicitsizenativeview_p.h"

QT_BEGIN_NAMESPACE

/*!
    \internal

    The purpose of QQuickImplicitSizeNativeView is not immediately clear, as both
    the implicit size properties and signals exist on QQuickItem. However,
    for some items - where the implicit size has an underlying meaning (such as
    Image, where the implicit size represents the real size of the image)
    having implicit size writable is an undesirable thing.

    QQuickImplicitSizeNativeView redefines the properties as being readonly.
    Unfortunately, this also means they need to redefine the change signals.
*/

QQuickImplicitSizeNativeViewPrivate::QQuickImplicitSizeNativeViewPrivate()
    : QQuickNativeViewPrivate()
{
}

QQuickImplicitSizeNativeViewPrivate::~QQuickImplicitSizeNativeViewPrivate()
{
}

void QQuickImplicitSizeNativeViewPrivate::implicitWidthChanged()
{
    QQuickNativeViewPrivate::implicitWidthChanged();

    emit q_func()->implicitWidthChanged2();
}

void QQuickImplicitSizeNativeViewPrivate::implicitHeightChanged()
{
    QQuickNativeViewPrivate::implicitHeightChanged();

    emit q_func()->implicitHeightChanged2();
}


QQuickImplicitSizeNativeView::QQuickImplicitSizeNativeView(QQuickItem *parent)
    : QQuickNativeView(*new QQuickImplicitSizeNativeViewPrivate, parent)
{
}

QQuickImplicitSizeNativeView::QQuickImplicitSizeNativeView(QQuickImplicitSizeNativeViewPrivate &dd, QQuickItem *parent)
    : QQuickNativeView(dd, parent)
{
}

QQuickImplicitSizeNativeView::~QQuickImplicitSizeNativeView()
{
}

QT_END_NAMESPACE
