#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <paintscene.h>
#include <colorpicker.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;

private:
    paintScene *scene;
    colorPicker *picker;
    int sceneWidth=500, sceneHeight=500;
    int brushSize = 10;
    QColor color;

private Q_SLOTS:
    void sizeLineEditTextChanged();
    void selectColorButtonClicked();
    void openFileButtonClicked();
    void saveFileButtonClicked();
    void widthLineEditTextChanged();
    void heightLineEditTextChanged();
    void changeColor(QColor color);
};
#endif // MAINWINDOW_H
