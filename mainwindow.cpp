#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <windows.h>
#include <QTimer>
#include <QPoint>
#include <QMouseEvent>

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

// 显示物理坐标
void MainWindow::show_mouse_coordinates(){
    POINT p;
    GetPhysicalCursorPos(&p);
    ui->lineEdit_mouse_showx->setText(QString::number(p.x));
    ui->lineEdit_mouse_showy->setText(QString::number(p.y));
}


void MainWindow::on_comboBox_action_type_editTextChanged(const QString &arg1)
{
    ui->comboBox_action_parameters->clear();
    if(arg1=="鼠标操作"){
        ui->comboBox_action_parameters->addItems({"左键按下","右键按下","左键抬起","右键抬起","左键单击","右键单击","左键双击","右键双击","上滚滑轮","下滚滑轮"});
    }
    else if(arg1=="鼠标移动"){
        ui->comboBox_action_parameters->addItems({"x,y"});
    }
    else if(arg1=="键盘按下"){
        ui->comboBox_action_parameters->addItems({
            "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
            "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
            "u", "v", "w", "x", "y", "z"
        });
    }
    else if(arg1=="键盘抬起"){
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
    //获取选项内容
    QString qs_action_type=this->ui->comboBox_action_type->currentText();
    QString qs_action_parameters=this->ui->comboBox_action_parameters->currentText();
    long l_repeat_time=this->ui->spinBox_execute_time->value();
    long l_lastRow = ui->tableWidget_execut_table->rowCount();
    //插入内容
    ui->tableWidget_execut_table->insertRow(l_lastRow);
    ui->tableWidget_execut_table->setItem(l_lastRow, 0, new QTableWidgetItem(qs_action_type));
    ui->tableWidget_execut_table->setItem(l_lastRow, 1, new QTableWidgetItem(qs_action_parameters));
    ui->tableWidget_execut_table->setItem(l_lastRow, 2, new QTableWidgetItem(QString::number(l_repeat_time)));
}

void MainWindow::on_pushButton_run_clicked()
{
    QTableWidget *tableWidget_execut_table=this->ui->tableWidget_execut_table;  //指向表格
    int rowCount = tableWidget_execut_table->rowCount();    //行数
    int colCount = tableWidget_execut_table->columnCount(); //列数
    for(long i=0;i<rowCount;i++){
        QString qs_type=tableWidget_execut_table->item(i,0)->text();    //获取操作类型
        QString qs_parameters=tableWidget_execut_table->item(i,1)->text();  //具体操作数据
        long l_execute_time=tableWidget_execut_table->item(i,2)->text().toLong();
        //鼠标操作
        if(qs_type=="鼠标操作"){
            for(long j=0;j<l_execute_time;j++){
                if(qs_parameters == "左键按下") mouseLeftDown();
                else if(qs_parameters == "右键按下") mouseRightDown();
                else if(qs_parameters == "左键抬起") mouseLeftUp();
                else if(qs_parameters == "右键抬起") mouseRightUp();
                else if(qs_parameters == "左键单击") mouseLeftClick();
                else if(qs_parameters == "右键单击") mouseRightClick();
                else if(qs_parameters == "左键双击") mouseLeftDoubleClick();
                else if(qs_parameters == "右键双击") mouseRightDoubleClick();
            }
        }
        //鼠标移动
        else if(qs_type=="鼠标移动"){
            for(long j=0;j<l_execute_time;j++){
                mouseMove(qs_parameters);
            }
        }
        //键盘按下
        else if(qs_type=="键盘按下"){
            for(long j=0;j<l_execute_time;j++){
                qDebug()<<qs_parameters;
            }
        }
        //键盘抬起
        else if(qs_type=="键盘抬起"){
            for(long j=0;j<l_execute_time;j++){
                qDebug()<<qs_parameters;
            }
        }
        //延时操作
        else if(qs_type=="延时(毫秒)"){
            for(long j=0;j<l_execute_time;j++){
                _delay(qs_parameters.toInt());
            }
        }
    }
}

//局部事件非阻塞延时
void MainWindow::_delay(int ms)
{
    QEventLoop loop;
    QTimer::singleShot(ms, &loop, &QEventLoop::quit);
    loop.exec();
}

// 移动鼠标
void MainWindow::mouseMove(const QString &posStr)
{
    QStringList list = posStr.split(",");
    int x = list[0].toInt();
    int y = list[1].toInt();
    SetCursorPos(x, y);
}

// 左键按下
void MainWindow::mouseLeftDown()
{
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

// 左键抬起
void MainWindow::mouseLeftUp()
{
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

// 左键单击
void MainWindow::mouseLeftClick()
{
    mouseLeftDown();
    _delay(20);
    mouseLeftUp();
}

// 左键双击
void MainWindow::mouseLeftDoubleClick()
{
    mouseLeftClick();
    _delay(100);
    mouseLeftClick();
}

// 右键按下
void MainWindow::mouseRightDown()
{
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

// 右键抬起
void MainWindow::mouseRightUp()
{
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}

// 右键单击
void MainWindow::mouseRightClick()
{
    mouseRightDown();
    _delay(20);
    mouseRightUp();
}

// 右键双击
void MainWindow::mouseRightDoubleClick()
{
    mouseRightClick();
    _delay(100);
    mouseRightClick();
}
