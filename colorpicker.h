#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

namespace Ui {
class colorPicker;
}

class colorPickScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QColor color;
private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
signals:
    void colorPicked();
};

class colorPicker : public QWidget
{
    Q_OBJECT

public:
    explicit colorPicker(QWidget *parent = nullptr);
    ~colorPicker();

private:
    Ui::colorPicker *ui;
    colorPickScene *scene;

private Q_SLOTS:
    void colorPicked();

signals:
    void closeForm(QColor color);
};
#endif // COLORPICKER_H
