#ifndef PLAYERWIN_H
#define PLAYERWIN_H

#include <QDialog>

namespace Ui {
class playerwin;
}

class playerwin : public QDialog
{
    Q_OBJECT

public:
    explicit playerwin(QWidget *parent = nullptr);
    ~playerwin();

private:
    Ui::playerwin *ui;
};

#endif // PLAYERWIN_H
