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
  ///Calling this fuction to pause the  playback.
  void pause_playback(bool start1);
  ///Calling this function to pause the record.
  void pause_record(bool start2);
  ///Calling this function to add the record dialog box.
  void popp_record();
  ///Calling this function to add the playback dialog box.
  void popp_play();
private:
  Q_DISABLE_COPY(ctkQtTestingMainWindow)
  ctkQtTestingUtility *TestUtility;
  Ui::ctkQtTestingMainWindow Ui;
  pqEventRecorder* Recorder;
  
};

#endif

