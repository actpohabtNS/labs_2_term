#ifndef GRAPHSWINDOW_H
#define GRAPHSWINDOW_H

#include <QWidget>

namespace Ui {
class GraphsWindow;
}

class GraphsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GraphsWindow(QWidget *parent = nullptr);
    ~GraphsWindow();

signals:
    void backButtonClicked();

private slots:
    void on_backButton_clicked();

private:
    Ui::GraphsWindow *ui;
};

#endif // GRAPHSWINDOW_H
