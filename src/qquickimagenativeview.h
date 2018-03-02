#ifndef QQUICKIMAGENATIVEVIEW_H
#define QQUICKIMAGENATIVEVIEW_H

#include <qquicknativeview/qquickimplicitsizenativeview.h>

QT_BEGIN_NAMESPACE

class QQuickImageNativeViewPrivate;
class QQuickImageNativeView : public QQuickImplicitSizeNativeView
{
    Q_OBJECT
    Q_PROPERTY(QSizeF paintedSize READ paintedSize NOTIFY paintedSizeChanged FINAL)
    Q_PROPERTY(QSizeF sourceSize READ sourceSize NOTIFY sourceSizeChanged FINAL)
    Q_PROPERTY(FillMode fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged FINAL)
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged FINAL)

public:
    explicit QQuickImageNativeView(QQuickItem *parent = nullptr);
    ~QQuickImageNativeView() override;

    QRectF boundingRect() const override;

    QSizeF paintedSize() const;
    QSizeF sourceSize() const;

    enum FillMode {
        Stretch = 0,
        PreserveAspectFit,
        PreserveAspectCrop,
        Pad
    };
    Q_ENUM(FillMode)

    FillMode fillMode() const;
    void setFillMode(FillMode fillMode);

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

Q_SIGNALS:
    void sourceSizeChanged();
    void paintedSizeChanged();
    void fillModeChanged();
    void alignmentChanged();

protected:
    void setSourceSize(const QSizeF &sourceSize);

    void updatePaintedGeometry();

    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

protected:
    QQuickImageNativeView(QQuickImageNativeViewPrivate &dd, QQuickItem *parent);

private:
    Q_DISABLE_COPY(QQuickImageNativeView)
    Q_DECLARE_PRIVATE(QQuickImageNativeView)
};

QT_END_NAMESPACE

#endif // QQUICKIMAGENATIVEVIEW_H
