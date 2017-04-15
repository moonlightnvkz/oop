//
// Created by moonlightnvkz on 09.04.17.
//

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv/cv.hpp>
#include <QDebug>
#include <QGridLayout>
#include <QFileDialog>
#include "MainWindow.h"
#include "BackgroundRemover.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->kernel_size->setRange(1, 6);
    connect(ui->sensitivity, SIGNAL(valueChanged(int)), this, SLOT(on_sensitivity_valueChanged()));
    connect(ui->sigma, SIGNAL(valueChanged(int)), this, SLOT(on_sigma_valueChanged()));
    connect(ui->area_ignored, SIGNAL(valueChanged(int)), this, SLOT(on_area_ignored_valueChanged()));
    connect(ui->kernel_size, SIGNAL(valueChanged(int)), this, SLOT(on_kernel_size_valueChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loadFile(const QString &fileName)
{
    img = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);
    if (img.empty()) {
        qDebug() << "Failed to open the image";
        return false;
    }
    remove_background();
    return true;
}

bool MainWindow::saveFile(const QString &fileName) {
    if (img.empty()) {
        return false;
    }
    double s = ui->sigma->value() / 100.0;
    size_t t = static_cast<size_t>(ui->sensitivity->value());
    int a = ui->area_ignored->value();
    int k = ui->kernel_size->value() * 2 - 1;
    BackRem::BackgroundRemover remover(t, s, k, a);
    cv::Mat output = remover.remove_background(img);
    cv::imwrite(fileName.toStdString(), output);
    return true;
}

void MainWindow::on_area_ignored_valueChanged(){
    remove_background();
}

void MainWindow::on_sensitivity_valueChanged(){
    remove_background();
}

void MainWindow::on_sigma_valueChanged(){
    remove_background();
}

void MainWindow::on_kernel_size_valueChanged() {
    remove_background();
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;
    dialog.setAcceptMode(acceptMode);
    if (acceptMode == QFileDialog::AcceptSave) {
        dialog.setDefaultSuffix(".png");
    }
    if (firstDialog) {
        firstDialog = false;
        dialog.setDirectory(QDir::currentPath());
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void MainWindow::on_actionSave_triggered()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

    while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
}

void MainWindow::setImage(const QImage &newImage)
{
    image = newImage;
    ui->image_label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::remove_background()
{
    if (img.empty()) {
        return;
    }
    double s = ui->sigma->value() / 100.0;
    size_t t = static_cast<size_t>(ui->sensitivity->value());
    int a = ui->area_ignored->value();
    int k = ui->kernel_size->value() * 2 - 1;

    BackRem::BackgroundRemover remover(t, s, a, k);
    cv::Mat output = remover.remove_background(img);

    cv::cvtColor(output, output, CV_BGRA2RGBA);
    QImage im(output.data, output.cols, output.rows, static_cast<int>(output.step),
              QImage::Format_RGBA8888);
    setImage(im);
}
