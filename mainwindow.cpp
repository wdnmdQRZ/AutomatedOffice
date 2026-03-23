#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <windows.h>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //计时器实现实时显示鼠标坐标
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::show_mouse_coordinates);
    timer->start(80);  // 每80ms触发一次
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_fixed_clicked()
{
    isStayOnTop = !isStayOnTop;
    //获取窗口句柄
    HWND hwnd = (HWND)this->winId();
    if (isStayOnTop) {
        //Windows API置顶窗口
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        // 改变样式
        ui->pushButton_fixed->setStyleSheet(R"(
            QPushButton {
                background-color: #ff9800;
                color: white;
            }
        )");

    } else {
        //取消置顶
        SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        // 恢复样式
        ui->pushButton_fixed->setStyleSheet("");
    }
}

void MainWindow::show_mouse_coordinates(){
    //显示坐标
    this->ui->lineEdit_mouse_showx->setText(QString::number(QCursor().pos().x()));
    this->ui->lineEdit_mouse_showy->setText(QString::number(QCursor().pos().y()));
}
