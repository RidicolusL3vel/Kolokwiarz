#ifndef QUESTIONADDER_H
#define QUESTIONADDER_H

#include <QDialog>
#include "../core/admin.h"

namespace Ui {
class QuestionAdder;
}

class QuestionAdder : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionAdder(const Admin& admin, QWidget *parent = nullptr);
    ~QuestionAdder();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::QuestionAdder *ui;

    Admin m_admin;

    void fillTopics();
};

#endif // QUESTIONADDER_H
