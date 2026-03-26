#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>  // 必须加，否则鼠标事件报错

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void mouseMove(const QString &posStr);       // 移动
    void mouseLeftDown();               // 左键按下
    void mouseLeftUp();                 // 抬起
    void mouseLeftClick();              // 单击
    void mouseLeftDoubleClick();        // 双击
    void mouseRightDown();              // 右键按下
    void mouseRightUp();                // 抬起
    void mouseRightClick();             // 单击
    void mouseRightDoubleClick();       // 双击

private slots:
    void on_pushButton_fixed_clicked();//固定页面
    void show_mouse_coordinates();//显示鼠标坐标
    void on_comboBox_action_type_editTextChanged(const QString &arg1);//根据不同类型显示不同操作
    void on_pushButton_insert_clicked();//插入数据
    void on_pushButton_run_clicked();//开始运行
    void _delay(int ms);//局部事件循环延时函数
    void onTableMenu(const QPoint &pos);//表格右键菜单实现

private:
    Ui::MainWindow *ui;
    bool isStayOnTop = false;   //判断窗口是否置顶
};

#endif // MAINWINDOW_H
