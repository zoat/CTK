#ifndef CTKQTTESTINGMAINWINDOW_H
#define CTKQTTESTINGMAINWINDOW_H

#include <QMainWindow>
#include <ctkQtTestingUtility.h>
#include "ui_ctkQtTestingMainWindow.h"
class pqTestUtility;


class ctkQtTestingMainWindow : public QMainWindow
{
  Q_OBJECT
public:
  ctkQtTestingMainWindow();
  ~ctkQtTestingMainWindow();
protected slots:
  void record(bool start);
  void play();
  void pause_playback(bool start1);
  void pause_record(bool start2);
  void popp_record();
  void popp_play();
private:
  Q_DISABLE_COPY(ctkQtTestingMainWindow)
  
  ctkQtTestingUtility *TestUtility;
  Ui::ctkQtTestingMainWindow Ui;
  pqEventRecorder* Recorder;
  
};

#endif

