#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

