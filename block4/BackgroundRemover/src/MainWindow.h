//
// Created by moonlightnvkz on 09.04.17.
//

#pragma once
#include <opencv2/core/mat.hpp>
#include <QMainWindow>
#include <QLabel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool loadFile(const QString &);
    bool saveFile(const QString &);

private slots:
    void on_area_ignored_valueChanged();

    void on_sigma_valueChanged();

    void on_sensitivity_valueChanged();

    void on_kernel_size_valueChanged();
    
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    void setImage(const QImage &newImage);

    void remove_background();

    cv::Mat img;
    QImage image;
};


