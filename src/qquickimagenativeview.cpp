#include "qquickimagenativeview.h"
#include "qquickimagenativeview_p.h"

QT_BEGIN_NAMESPACE

QQuickImageNativeViewPrivate::QQuickImageNativeViewPrivate()
    : QQuickImplicitSizeNativeViewPrivate(),
      paintedSize(0, 0),
      sourceSize(0, 0),
      fillMode(QQuickImageNativeView::Stretch),
      align(Qt::AlignCenter)
{
}

QQuickImageNativeViewPrivate::~QQuickImageNativeViewPrivate()
{
}


QQuickImageNativeView::QQuickImageNativeView(QQuickItem *parent)
    : QQuickImplicitSizeNativeView(*new QQuickImageNativeViewPrivate, parent)
{
}

QQuickImageNativeView::QQuickImageNativeView(QQuickImageNativeViewPrivate &dd, QQuickItem *parent)
    : QQuickImplicitSizeNativeView(dd, parent)
{
}

QQuickImageNativeView::~QQuickImageNativeView()
{
}

QRectF QQuickImageNativeView::boundingRect() const
{
    Q_D(const QQuickImageNativeView);

    switch (d->fillMode) {
    case PreserveAspectFit:
    case Pad:
        if (!d->sourceSize.isNull()) {
            qreal paintedWidth = d->fillMode == PreserveAspectFit ? d->paintedSize.width() : d->sourceSize.width();
            qreal paintedHeight = d->fillMode == PreserveAspectFit ? d->paintedSize.height() : d->sourceSize.height();

            qreal xOffset = 0;
            if ((d->align & Qt::AlignHorizontal_Mask) == Qt::AlignHCenter)
                xOffset = (width() - paintedWidth) * 0.5;
            else if ((d->align & Qt::AlignHorizontal_Mask) == Qt::AlignRight)
                xOffset = width() - paintedWidth;

            qreal yOffset = 0;
            if ((d->align & Qt::AlignVertical_Mask) == Qt::AlignVCenter)
                yOffset = (height() - paintedHeight) * 0.5;
            else if ((d->align & Qt::AlignVertical_Mask) == Qt::AlignBottom)
                yOffset = height() - paintedHeight;

            if (d->fillMode == PreserveAspectFit)
                return QRectF(xOffset, yOffset, d->paintedSize.width(), d->paintedSize.height());

            qreal w = qMin(paintedWidth, width());
            qreal h = qMin(paintedHeight, height());
            qreal x = paintedWidth > width() ? -xOffset : 0;
            qreal y = paintedHeight > height() ? -yOffset : 0;
            return QRectF(x + xOffset, y + yOffset, w, h);
        }
        break;

    default:
        break;
    }

    return QRectF(0, 0, qMax(width(), d->paintedSize.width()), qMax(height(), d->paintedSize.height()));
}

void QQuickImageNativeView::updatePaintedGeometry()
{
    Q_D(QQuickImageNativeView);

    if (d->sourceSize.isEmpty()) {
        d->paintedSize = QSizeF(0, 0);
        setImplicitSize(0, 0);
    }

    switch (d->fillMode) {
    case PreserveAspectFit: {
        if (d->sourceSize.isEmpty())
            return;

        qreal w = widthValid() ? width() : d->sourceSize.width();
        qreal widthScale = w / d->sourceSize.width();
        qreal h = heightValid() ? height() : d->sourceSize.height();
        qreal heightScale = h / d->sourceSize.height();
        if (widthScale <= heightScale) {
            d->paintedSize.setWidth(w);
            d->paintedSize.setHeight(widthScale * d->sourceSize.height());
        } else {
            d->paintedSize.setWidth(heightScale * d->sourceSize.width());
            d->paintedSize.setHeight(h);
        }
        qreal iWidth = heightValid() && !widthValid() ? d->paintedSize.width() : d->sourceSize.width();
        qreal iHeight = widthValid() && !heightValid() ? d->paintedSize.height() : d->sourceSize.height();
        setImplicitSize(iWidth, iHeight);
        break;
    }

    case PreserveAspectCrop: {
        if (d->sourceSize.isEmpty())
            return;

        qreal widthScale = width() / d->sourceSize.width();
        qreal heightScale = height() / d->sourceSize.height();
        if (widthScale < heightScale)
            widthScale = heightScale;
        else if (heightScale < widthScale)
            heightScale = widthScale;
        d->paintedSize.setWidth(widthScale * d->sourceSize.width());
        d->paintedSize.setHeight(heightScale * d->sourceSize.height());
        break;
    }

    case Pad:
        d->paintedSize = d->sourceSize;
        break;

    default:
        d->paintedSize.setWidth(width());
        d->paintedSize.setHeight(height());
    }

    emit paintedSizeChanged();
}

void QQuickImageNativeView::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickImplicitSizeNativeView::geometryChanged(newGeometry, oldGeometry);

    updatePaintedGeometry();
}

QSizeF QQuickImageNativeView::paintedSize() const
{
    return d_func()->paintedSize;
}

QSizeF QQuickImageNativeView::sourceSize() const
{
    return d_func()->sourceSize;
}

void QQuickImageNativeView::setSourceSize(const QSizeF &sourceSize)
{
    Q_D(QQuickImageNativeView);

    if (Q_UNLIKELY(d->sourceSize == sourceSize))
        return;

    d->sourceSize = sourceSize;
    setImplicitSize(d->sourceSize.width(), d->sourceSize.height());
    updatePaintedGeometry();
    emit sourceSizeChanged();
}

QQuickImageNativeView::FillMode QQuickImageNativeView::fillMode() const
{
    return d_func()->fillMode;
}

void QQuickImageNativeView::setFillMode(QQuickImageNativeView::FillMode fillMode)
{
    Q_D(QQuickImageNativeView);

    if (Q_UNLIKELY(d->fillMode == fillMode))
        return;

    d->fillMode = fillMode;
    updatePaintedGeometry();
    emit fillModeChanged();
}

Qt::Alignment QQuickImageNativeView::alignment() const
{
    return d_func()->align;
}

void QQuickImageNativeView::setAlignment(Qt::Alignment align)
{
    Q_D(QQuickImageNativeView);

    if (Q_UNLIKELY(d->align == align))
        return;

    d->align = align;
    updatePaintedGeometry();
    emit alignmentChanged();
}

QT_END_NAMESPACE
