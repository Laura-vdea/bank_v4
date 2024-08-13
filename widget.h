#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <memory>
#include "bankingsystem.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void cancel();

private slots:

    void on_loginButton_clicked();

    void on_pushButton_makeAcc_clicked();

    void on_pushButton_deposit_clicked();

    void on_pushButton_withdraw_clicked();

    void on_button_mconfirm_clicked();

    void on_button_dconfirm_clicked();

    void on_button_wconfirm_clicked();

    void on_pushButton_allAcc_clicked();

    void on_button_show_clicked();


    void on_pushButton_exit_clicked();

    void on_pushButton_spAcc_clicked();


private:
    Ui::Widget *ui;
    std::shared_ptr<BankingSystem> bankingSystem;
};
#endif // WIDGET_H
