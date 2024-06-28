#ifndef THIRDCHANGE_H
#define THIRDCHANGE_H

#include <QWidget>

namespace Ui {
class thirdchange;
}

class thirdchange : public QWidget
{
    Q_OBJECT

public:
    explicit thirdchange(QWidget *parent = nullptr);
    ~thirdchange();

private slots:

    void on_pushButton_2_clicked();

private:
    Ui::thirdchange *ui;
};

#endif // THIRDCHANGE_H
