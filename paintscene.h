#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class paintScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit paintScene(QObject *parent = 0);
    ~paintScene();
    int brushSize = 10;
    QColor color = Qt::red;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif // PAINTSCENE_H
