#ifndef LAYERDRAW_H
#define LAYERDRAW_H

#include <QWidget>
#include <QVector2D>

class LayerDraw : public QWidget
{
    Q_OBJECT
public:
    LayerDraw(QWidget * parent = 0);
    ~LayerDraw();
    void paintEvent(QPaintEvent * e);
    bool loadData(QString SVGfilePath);

    int currLayer;
    int numLayers;

    bool saveBitmapImages();
    int getNumLayers();

    QPointF currScale;
    QPointF currTranslation;

    //needs to be changed to private ASAP
    float meshXMin, meshXMax;
    float meshYMin, meshYMax;

private:
    QVector<QVector<QPolygonF>> layerInfoList;

    float zoom;
    QVector2D translation;

    bool hasLayersLoaded;

    void drawBackground(); // add build settings into parameters later

    // for now, segmentation will happen after the images have been saved
    // there is a list to be returned to saveBitmapImages function --> check soft. architechture later
    QList<QImage> segmentImage(QImage image, QSize printArea); //printArea: amount of area the printhead can cover at once

    QPoint mouse_pos;

    void findInitialZoom();


protected:
    //void paintEvent(QPaintEvent * e);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);


};


#endif // LAYERDRAW_H
