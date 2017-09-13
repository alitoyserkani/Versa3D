#include "layerdraw.h"
#include "qpainter.h"
//#include <QSvgRenderer>
//#include <QSvgWidget>
#include <QFile>
#include <QtXml>
#include <QBitmap>

LayerDraw::LayerDraw(QWidget *parent) :
    QWidget(parent)
{
//    QPalette pal = palette();
//    pal.setColor(QPalette::Background, Qt::blue);
    parent->setAutoFillBackground(true);
    parent->setPalette(QPalette(QColor(Qt::gray)));

    hasLayersLoaded = false;

}

LayerDraw::~LayerDraw() {

}

//TODO: Scaling layers based on their dimensions. Add scaling variable to be used in rendering equation.

void LayerDraw::paintEvent(QPaintEvent * e)
{

    //TODO: load svg's only after stl has been loaded, don't run this code otherwise
    //TODO: get correct tranformation based on size of part
    //TODO be able to translate part in build space machine
    if (hasLayersLoaded) {
        QPainter painter(this);
        painter.scale(10,10);
        painter.translate(7.5,7.5);

        QPen linePen;
        linePen.setWidthF(0.25);
        linePen.setColor(Qt::black);
        linePen.setJoinStyle(Qt::MiterJoin);
        painter.setPen(linePen);

        QBrush fillBrush;
        fillBrush.setColor(Qt::blue);
        fillBrush.setStyle(Qt::SolidPattern);
        QPainterPath path;
        //Make polygon


        for (int i = 0; i < layerInfoList.at(currLayer-1).size(); i++) {

            path.addPolygon(layerInfoList.at(currLayer-1).at(i));

            painter.fillPath(path,fillBrush);
            painter.drawPolygon(layerInfoList.at(currLayer-1).at(i));
        }

    } else {
        //TODO, add text saying nothing has been loaded
    }


}

bool LayerDraw::loadData(QString SVGfilePath)
{
    QFile file(SVGfilePath);

    QDomDocument document;

    //Check if file is valid
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File open failed";
        return false;;
    } else {
        //add file contents to QDomDocument
        if (!document.setContent(&file)) {
            qDebug() << "Document load failed";
            return false;
        }
        file.close();
    }

    QDomElement root = document.firstChildElement();
    QDomNodeList layerNodes = root.childNodes();
    //QVector<QVector<QList<QPointF>>> shapes;
    numLayers = layerNodes.count();
    for (int i = 0; i < layerNodes.count(); i++) {

        QDomNodeList shapesInLayer = layerNodes.at(i).childNodes();
        QVector<QPolygonF> layerShapes;
        for (int j = 0; j < shapesInLayer.count(); j++) {

            QString temp = shapesInLayer.at(j).toElement().attribute("points");
            QPolygonF pointsInShape;
            QStringList pointsString = temp.split(" ");
            for (int k = 0; k < pointsString.size(); k++) {
                QStringList coord = pointsString.at(k).split(",");
                pointsInShape << QPointF(coord.at(0).toFloat(),coord.at(1).toFloat());

            }
            layerShapes.push_back(pointsInShape);


        }
        //shapes.push_back(layerShapes);
        layerInfoList.push_back(layerShapes);


    }
    hasLayersLoaded = true;
    return true;
}

bool LayerDraw::saveBitmapImages()
{
    QString fileDef("exImg");

    for (int i = 0; i < layerInfoList.size(); i++) {
        //inefficent start test
        QPixmap pixmap(this->rect().size()); // this needs to be the appropritate size for machine
        QBitmap bitmap(this->rect().size());
        bitmap.clear();

        pixmap.fill(Qt::color0);
        QPainter painter(&pixmap);
        //BAD way, remove ASAPPPPPP

        painter.scale(10,10);
        painter.translate(7.5,7.5);

        QPen linePen;
        linePen.setWidthF(0.25);
        linePen.setColor(Qt::black);
        linePen.setJoinStyle(Qt::MiterJoin);
        painter.setPen(linePen);

        QRadialGradient radialGrad(QPointF(100, 100), 100);
        radialGrad.setColorAt(0, Qt::color0);
        radialGrad.setColorAt(0.5, Qt::blue);
        radialGrad.setColorAt(1, Qt::green);
        QBrush fillBrush(radialGrad);
        fillBrush.setColor(Qt::black);
        fillBrush.setStyle(Qt::RadialGradientPattern); //this changes this flood fill for now
        QPainterPath path;
        //Make polygon


        for (int j = 0; j < layerInfoList.at(i).size(); j++) {

            path.addPolygon(layerInfoList.at(i).at(j));

            painter.fillPath(path,fillBrush);
            painter.drawPolygon(layerInfoList.at(i).at(j));
        }

        painter.end();

//        std::stringstream ss;
//        ss << "touch ../../../../files/BMP_Out/" << fileDef.toUtf8().constData() << QString::number(i).toUtf8().constData() << ".png";
//        system(ss.str().c_str());
//        QFile image("../../../../files/BMP_Out/" + fileDef + QString::number(i));
//        image.open(QIODevice::ReadWrite);


        //qDebug() << pixmap.toImage().save(QString("../../../../files/BMP_Out/hello") + QString::number(i) + ".png","PNG",100); // add statment to return false from function if QPixmap::save doesnt work
        bitmap.convertFromImage(pixmap.toImage());
        qDebug() << bitmap.width() << bitmap.height() << bitmap.size();
        bitmap.save(QString("../../../../files/BMP_Out/hello") + QString::number(i) + ".bmp");
      //  image.close();
    }
    qDebug() << this->rect().size() << "Export Complete";

    return true;
}

int LayerDraw::getNumLayers()
{
    return layerInfoList.size();
}

void LayerDraw::segmentImages(QSize buildArea)
{
    //TO-DO: with given build size, slice images and add correct filename to be identified by the printhead buffer
    //Important: segmentImages should be called within the LayerDraw class (change to private/protected), for effieciecy




}


