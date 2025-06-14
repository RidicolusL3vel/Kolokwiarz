#ifndef RANKINGWINDOW_H
#define RANKINGWINDOW_H

#include <QWidget>
#include "../core/usermanager.h"

namespace Ui {
class RankingWindow;
}

class RankingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RankingWindow(UserManager* userManager, QWidget *parent = nullptr);
    ~RankingWindow();

    void updateRanking();

    void setPodiumLabels();

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:
    void backToMainWindow();
private slots:
    void on_pushButton_clicked();

private:
    Ui::RankingWindow *ui;

    UserManager *userManager;
};

#endif // RANKINGWINDOW_H
