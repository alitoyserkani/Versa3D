#ifndef LAYERDRAW_H
#define LAYERDRAW_H

#include <QWidget>

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

protected:
    //void paintEvent(QPaintEvent * e);

private:
    QVector<QVector<QPolygonF>> layerInfoList;
    bool hasLayersLoaded;

};


#endif // LAYERDRAW_H
