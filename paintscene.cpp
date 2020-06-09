#include "paintscene.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{
}

paintScene::~paintScene()
{
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /**
     * @brief Обработчик нажатия на сцену
     */
    addEllipse(event->scenePos().x() - brushSize/2,
               event->scenePos().y() - brushSize/2,
               brushSize,
               brushSize,
               QPen(Qt::NoPen),
               QBrush(color));
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /**
     * @brief Обработчик движения курсора с нажатой кнопкой по сцене
     */
    mousePressEvent(event);
}
