#include "layerdraw.h"
#include "qpainter.h"
//#include <QSvgRenderer>
//#include <QSvgWidget>
#include <QFile>
#include <QtXml>
#include <QBitmap>
#include <QMouseEvent>

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
    drawBackground();

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
        fillBrush.setStyle(Qt::SolidPattern); //once scaling is fixed, the fillBrush Styles can be changed for different infill properties

        QPainterPath path;
        //Make polygon


        for (int i = 0; i < layerInfoList.at(currLayer-1).size(); i++) {

            //why is this step even here
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
    // delete previous data if new SVG is being loaded
    hasLayersLoaded = false;


    // if there is a second loading of data, remove all polygon data from previous SVG
    if (layerInfoList.size() > 0)
        layerInfoList.remove(0,layerInfoList.size()-1);


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

    float maxX = std::numeric_limits<float>::min(), minX = std::numeric_limits<float>::max(),
          maxY = std::numeric_limits<float>::min(), minY = std::numeric_limits<float>::max();

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

                if (coord.at(0).toFloat() > maxX) maxX = coord.at(0).toFloat();
                if (coord.at(0).toFloat() < minX) minX = coord.at(0).toFloat();
                if (coord.at(1).toFloat() > maxY) maxY = coord.at(1).toFloat();
                if (coord.at(1).toFloat() < minY) minY = coord.at(1).toFloat();

            }
            layerShapes.push_back(pointsInShape);


        }
        //shapes.push_back(layerShapes);
        layerInfoList.push_back(layerShapes);


    }
    meshXMax = maxX; meshXMin = minX;
    meshYMax = maxY; meshYMin = minY;

    hasLayersLoaded = true;
    return true;
}

bool LayerDraw::saveBitmapImages()
{
    QString fileDef("exImg");

    for (int i = 1; i < layerInfoList.size(); i++) {
        //inefficent start test
        QPixmap pixmap(QSize(615,600)); // this needs to be the appropritate size for machine
        QBitmap bitmap(QSize(615,600));
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

        QList<QImage> splitImages = segmentImage(pixmap.toImage(),QSize(615,300));

        qDebug() << splitImages.size();
        for (int j = 0; j < splitImages.size(); j++) {
            QBitmap segBitmap(QSize(615,300));
            segBitmap.clear();
            segBitmap.convertFromImage(splitImages.at(j));
            qDebug() << segBitmap.size() << segBitmap.height() << segBitmap.size() << "Layer" << i << "Seg" << j;
            segBitmap.save(QString("../../../../files/BMP_Out/helloLayer") + QString::number(i) + QString("Seg") + QString::number(j) + ".bmp");

        }

//        QFile templateFile("../../../../files/Templates/templateHyrbrid.xml");
//        templateFile.open(QIODevice::ReadOnly);
//        QString contents;
//        QTextStream s1(&file,QIODevice::ReadOnly);
//        contents.append(s1.readAll());

//        contents.indexOf

//        bitmap.convertFromImage(pixmap.toImage());
//        qDebug() << bitmap.width() << bitmap.height() << bitmap.size();
//        bitmap.save(QString("../../../../files/BMP_Out/hello") + QString::number(i) + ".bmp");
      //  image.close();
    }
    qDebug() << "Export Complete";

    return true;
}

int LayerDraw::getNumLayers()
{
    return layerInfoList.size();
}



QList<QImage> LayerDraw::segmentImage(QImage image, QSize printArea)
{
    //TO-DO: with given build size, slice images and add correct filename to be identified by the printhead buffer
    //Important: segmentImages should be called within the LayerDraw class (change to private/protected), for effieciecy
    //TODO: there may be a scenario where a printhead swath will only be a part of the image that is less than the printHeight. In this case, make an image of same size, but put correct part of image

    int numSplits = image.height() / printArea.height();
    QImage seg = image.copy(QRect(0,0,615,300));
    QImage seg2 = image.copy(QRect(0,300,615,300));

    QList<QImage> listSplitImages;
    listSplitImages.append(seg);
    listSplitImages.append(seg2);

    return listSplitImages;



}

void LayerDraw::drawBackground()
{
    //Draws build area from top view

    QPainter backgroundPainter(this);
    // add scale and translation but must be saved in a variable for ease of use
    backgroundPainter.scale(0.5,0.5);
    backgroundPainter.translate(5,10);

    QPen backgroundLinePen;
    backgroundLinePen.setWidth(2);
    backgroundLinePen.setColor(Qt::green);
    backgroundLinePen.setJoinStyle(Qt::MiterJoin);
    backgroundPainter.setPen(backgroundLinePen);

    //QPainterPath backgroundPath;
    //backgroundPath.addRect(30,30,100,100);
    backgroundPainter.drawRect(0,0,600,600);

    //change this to another qpainter object
    backgroundPainter.drawText(30,20, "Size: 600px X 600px");

    QPainter infoPainter(this);
    QPen infoPen;
    infoPen.setWidth(1);
    infoPen.setColor(Qt::black);
    infoPen.setJoinStyle(Qt::MiterJoin);
    infoPainter.setPen(infoPen);
    infoPainter.drawText(10,335, QString("XMin:") + QString::number(meshXMin) + "  " + QString("XMax:") + QString::number(meshXMax));
    infoPainter.drawText(10,350, QString("YMin:") + QString::number(meshYMin) + "  " + QString("YMax:") + QString::number(meshYMax));
}

void LayerDraw::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton ||
        event->button() == Qt::RightButton)
    {
        mouse_pos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
}

void LayerDraw::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton ||
        event->button() == Qt::RightButton)
    {
        unsetCursor();
    }
}


