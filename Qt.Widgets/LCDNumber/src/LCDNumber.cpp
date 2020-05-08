#include <QApplication>
#include <QFont>
#include <QFrame>
#include <QLabel>
#include <QLCDNumber>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>

class Window1 : public QMainWindow {
public:
  Window1() {
    label.setSegmentStyle(QLCDNumber::SegmentStyle::Flat);
    label.display(QString("%1").number(static_cast<double>(counter) / 10, 'f', 1));
    label.move(10, 10);
    label.resize(210, 70);
    label.setFont(QFont("Arial", 64, QFont::Normal, true));
    QPalette palette;
    palette.setColor(QPalette::WindowText, QColor::fromRgb(30, 144, 255));
    label.setPalette(palette);
    label.setFrameStyle(QFrame::NoFrame);

    button.setText("Start");
    button.move(10, 90);
    connect(&button, &QPushButton::clicked, [&]() {
      if (timer.isActive())
        timer.stop();
      else
        timer.start();
      button.setText(timer.isActive() ? "Stop" : "Start");
     });

    timer.setInterval(100);
    connect(&timer, &QTimer::timeout, [&]() {
      label.display(QString("%1").number(static_cast<double>(++counter) / 10, 'f', 1));
    });

    setCentralWidget(&panel);
    setWindowTitle("LCDNumber example");
    resize(230, 130);
  }

private:
  QFrame panel;
  QLCDNumber label {&panel};
  QPushButton button {&panel};
  QTimer timer {this};
  int counter = 0;
};

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  Window1 form;
  form.show();
  return application.exec();
}