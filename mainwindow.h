#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_pushButton_fixed_clicked();
    void show_mouse_coordinates();

    void on_comboBox_action_type_editTextChanged(const QString &arg1);

    void on_pushButton_insert_clicked();

private:
    Ui::MainWindow *ui;
    bool isStayOnTop = false;   //判断窗口是否置顶
};
#endif // MAINWINDOW_H
