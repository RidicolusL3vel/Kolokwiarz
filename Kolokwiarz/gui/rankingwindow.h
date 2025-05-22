#ifndef RANKINGWINDOW_H
#define RANKINGWINDOW_H

#include <QWidget>

namespace Ui {
class RankingWindow;
}

class RankingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RankingWindow(QWidget *parent = nullptr);
    ~RankingWindow();

private:
    Ui::RankingWindow *ui;
};

#endif // RANKINGWINDOW_H
