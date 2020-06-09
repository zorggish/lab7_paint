#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <colorpicker.h>

#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new paintScene();
    ui->graphicsView->setScene(scene);

    connect(ui->sizeLineEdit, &QLineEdit::textChanged, this, &MainWindow::sizeLineEditTextChanged);
    connect(ui->selectColorButton, &QPushButton::clicked, this, &MainWindow::selectColorButtonClicked);
    connect(ui->widthLineEdit, &QLineEdit::textChanged, this, &MainWindow::widthLineEditTextChanged);
    connect(ui->heightLineEdit, &QLineEdit::textChanged, this, &MainWindow::heightLineEditTextChanged);
    connect(ui->openFileButton, &QPushButton::clicked, this, &MainWindow::openFileButtonClicked);
    connect(ui->saveFileButton, &QPushButton::clicked, this, &MainWindow::saveFileButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sizeLineEditTextChanged()
{
    /**
     * @brief Обработчик изменения поля размера кисти
     */
    int newBrushSize = ui->sizeLineEdit->text().toInt();
    if(newBrushSize!=0)
    {
        brushSize=newBrushSize;
        scene->brushSize=newBrushSize;
    }
    else ui->sizeLineEdit->setText(QString::number(brushSize));
}

void MainWindow::selectColorButtonClicked()
{
    /**
     * @brief Обработчик нажатия кнопки выбора цвета
     */
    /*QColorDialog colorDialog;
    color=colorDialog.getColor();*/
    picker = new colorPicker();
    connect(picker, SIGNAL(closeForm(QColor)), this, SLOT(changeColor(QColor)));
    picker->show();
}

void MainWindow::widthLineEditTextChanged()
{
    /**
     * @brief Обработчик изменения поля ширины сцены
     */
    int newWidth = ui->widthLineEdit->text().toInt();
    if(newWidth > 0)
    {
        sceneWidth=newWidth;
        ui->graphicsView->resize(newWidth, sceneHeight);
    }
    else ui->sizeLineEdit->setText(QString::number(sceneWidth));
}

void MainWindow::heightLineEditTextChanged()
{
    /**
     * @brief Обработчик изменения поля высоты сцены
     */
    int newHeight = ui->heightLineEdit->text().toInt();
    if(newHeight > 0)
    {
        sceneHeight=newHeight;
        ui->graphicsView->resize(sceneWidth, newHeight);
    }
    else ui->sizeLineEdit->setText(QString::number(scene->brushSize));
}

void MainWindow::openFileButtonClicked()
{
    /**
     * @brief Обработчик нажатия кнопки открытия файла
     */
    QFileDialog fileDialog;
    QPixmap pixmap(fileDialog.getOpenFileName());

    delete scene;
    scene = new paintScene();
    scene->color=color;
    scene->brushSize=brushSize;
    QGraphicsPixmapItem *item = scene->addPixmap(pixmap);
    sceneWidth=pixmap.width();
    sceneHeight=pixmap.height();
    ui->widthLineEdit->setText(QString::number(sceneWidth));
    ui->heightLineEdit->setText(QString::number(sceneHeight));
    ui->graphicsView->resize(pixmap.width(), pixmap.height());
    scene->setSceneRect(0, 0, pixmap.width(), pixmap.height());
    if(sceneWidth > 350)
        item->setPos(175-sceneWidth/2, item->pos().y());
    if(sceneHeight > 350)
        item->setPos(item->pos().x(), 175-sceneHeight/2);
    ui->graphicsView->setScene(scene);
}

void MainWindow::saveFileButtonClicked()
{
    /**
     * @brief Обработчик нажатия кнопки сохранения файла
     */
    QFileDialog fileDialog;
    QRect rect = ui->graphicsView->viewport()->rect();
    QPixmap pixmap(rect.size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    ui->graphicsView->render(&painter, pixmap.rect(), rect);
    pixmap.save(fileDialog.getSaveFileName());
}

void MainWindow::changeColor(QColor color)
{
    /**
     * @brief Изменения цвета кисти
     * @param color Новый цвет
     */
    picker->close();
    int r, g, b;
    color.getRgb(&r, &g, &b);
    this->color = color;
    scene->color=color;
    ui->selectColorButton->setStyleSheet("background-color: rgba(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + "); border: none;");
    delete picker;
}
