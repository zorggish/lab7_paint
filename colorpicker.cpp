#include "colorpicker.h"
#include "ui_colorpicker.h"
#include <QGraphicsView>

colorPicker::colorPicker(QWidget *parent) :QWidget(parent),ui(new Ui::colorPicker)
{
    ui->setupUi(this);
    scene = new colorPickScene();
    scene->addPixmap(QPixmap(":/images/palette.png"));
    ui->graphicsView->setScene(scene);
    connect(scene, SIGNAL(colorPicked()), this, SLOT(colorPicked()));
}

colorPicker::~colorPicker()
{
    delete ui;
}

void colorPickScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /**
     * @brief Обработчик нажатия на сцену выбора цвета
     */

    this->setSceneRect(event->scenePos().x(), event->scenePos().y(), 1, 1);
    QImage image(1, 1, QImage::Format_ARGB32);
    QPainter painter(&image);
    this->render(&painter);
    color = image.pixel(0, 0);
    emit colorPicked();
}

void colorPicker::colorPicked()
{
    /**
     * @brief Обработчик сигнала о том, что цвет выбран
     */
    emit closeForm(scene->color);
}
