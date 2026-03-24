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


void MainWindow::on_comboBox_action_type_editTextChanged(const QString &arg1)
{
    ui->comboBox_action_parameters->clear();
    if(arg1=="鼠标操作"){
        ui->comboBox_action_parameters->addItems({"左键单击","右键单击","左键双击","右键双击","上滚滑轮","下滚滑轮"});
    }
    else if(arg1=="键盘操作"){
        ui->comboBox_action_parameters->addItems({
            "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
            "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
            "u", "v", "w", "x", "y", "z"
        });
    }
    else if(arg1=="延时(毫秒)"){
        ui->comboBox_action_parameters->addItems({});
    }
}


void MainWindow::on_pushButton_insert_clicked()
{
    QString qs_action_type=this->ui->comboBox_action_type->currentText();
    QString qs_action_parameters=this->ui->comboBox_action_parameters->currentText();
    long l_repeat_time=this->ui->spinBox_repeat_time->value();
    long l_lastRow = ui->tableWidget_execut_table->rowCount();
    ui->tableWidget_execut_table->insertRow(l_lastRow);
    ui->tableWidget_execut_table->setItem(l_lastRow, 0, new QTableWidgetItem(qs_action_type));
    ui->tableWidget_execut_table->setItem(l_lastRow, 1, new QTableWidgetItem(qs_action_parameters));
    ui->tableWidget_execut_table->setItem(l_lastRow, 2, new QTableWidgetItem(QString::number(l_repeat_time)));
}
