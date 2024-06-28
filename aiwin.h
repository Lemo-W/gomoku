#ifndef AIWIN_H
#define AIWIN_H

#include <QDialog>

namespace Ui {
class aiwin;
}

class aiwin : public QDialog
{
    Q_OBJECT

public:
    explicit aiwin(QWidget *parent = nullptr);
    ~aiwin();

private:
    Ui::aiwin *ui;
};

#endif // AIWIN_H
